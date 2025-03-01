// -*- C++ -*-
//
// Package:     <Interpreter>
// Module:      TclInterpreter
// 
// Description: <one line class summary>
//
// Implementation:
//              (based on BaBar/CDF Framework, Liz Sexton-Kennedy)
//
// Author:      Martin Lohner
// Created:     Thu Mar  5 19:11:35 GMT 1998
// $Id: TclInterpreter.cc,v 1.47 2004/03/06 21:32:14 cdj Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>
#include "C++Std/iostream.h"
#include "C++Std/fstream.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
//for isatty
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// user include files
#include "Interpreter/Tcl_c++_wrapper.h"

#include "Experiment/report.h"
#include "Interpreter/TclInterpreter.h"
#include "CommandPattern/Command.h"
#include "Interpreter/Readline.h"
#include "Utility/StringTokenizer.h"
#include "Utility/FileNameUtils.h"

// STL classes
#include <string>
#include <vector>
#include <deque>


//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Interpreter.TclInterpreter" ;

int 
Tcl_AppInit( Tcl_Interp* interp )
{
   int status = TCL_OK;

   // tcl initialization
   if( TCL_ERROR == ( status = Tcl_Init(interp) ) ) 
   {
      report( SYSTEM, kFacilityString )
	 << "unsuccessful Tcl initialization" << endl;
      return status;
   }

   // implement the "unknown" command
   Tcl_GlobalEval( 
      interp,
      "proc unknown {args} { error \"invalid command: '$args'; "
      "type 'help' for available commands\" }" 
      );

   return status;
}

//
// static data member definitions
//

// local statics
const char* const TclInterpreter::s_sourceCommandString       = "tcl_source";
const char* const TclInterpreter::s_fileCommandString         = "tcl_file";
const char* const TclInterpreter::s_procCommandString         = "tcl_proc";

static string s_announcement =
string( "//  For a list of available commands, type \"help\".              \n" )+
string( "//                                                                \n" )+
string( "//  Since the command interpreter is based on a Tcl interpreter,  \n" )+
string( "//  all Tcl commands are available.                               \n" )+
string( "//  For info on tcl: \"http://www.scriptics.com/resource/doc\"    \n" );


//
// constructors and destructor
//
TclInterpreter::TclInterpreter()
   : m_tclInterpreter( Tcl_CreateInterp() ),
     m_tclCommandNames( *new STL_VECTOR( CommandName ) ),
     m_historyFile( "" ),
     m_historyLength( 200 ),
     m_sizeOfStackForExit(0),
     m_exitRequested(false),
     m_sizeOfStackForCatchExit(0)
{

   // print out announcement
   report( SYSTEM, kFacilityString )
      << "\n" << s_announcement << endl;

   // ---------- initialize gnu readline -----------------
   Readline::init();
   
   // history mechanism
   readHistory();

   // initialize
   Tcl_AppInit( m_tclInterpreter );

   // register all tcl commands with gnu readline
   Tcl_GlobalEval( m_tclInterpreter, "info commands" );
   StringTokenizer commands( Tcl_GetStringResult(m_tclInterpreter) );

   while( commands.hasMoreElements() ) {

      string command = commands.nextElement();

      // hold onto for later deregistration
      m_tclCommandNames.push_back( command );

      // register with gnu readline
      Readline::registerCommand( command.c_str() );
   }

   // create any other commands we might need

   // Rename some tcl commands
   report( SYSTEM, kFacilityString ) 
      << "\n"
      << "// Renaming the following Tcl commands:\n"
      << "//  (because they collide with Suez commands!)\n"
      << "// -------------------------------------------\n"
      << "//  source --> tcl_source\n"
      << "//  proc   --> tcl_proc\n"
      << "//  file   --> tcl_file\n"
      << endl;

   //Tcl_GlobalEval( "rename source tcl_source" );
   Tcl_CreateCommand( m_tclInterpreter, 
		      (char*)s_sourceCommandString,
		      (Tcl_CmdProc*)&TclInterpreter::sourceCommandHandler,
		      (ClientData)0,
		      (Tcl_CmdDeleteProc*) NULL );  
   Readline::registerCommand( s_sourceCommandString );
   
   string procCommand = string( "rename proc ") + s_procCommandString;
   Tcl_GlobalEval( m_tclInterpreter, (char*)procCommand.c_str() );
   Readline::registerCommand( (char*)s_procCommandString );
   
   string fileCommand = string( "rename file ") + s_fileCommandString;
   Tcl_GlobalEval( m_tclInterpreter, (char*)fileCommand.c_str() );
   Readline::registerCommand( (char*)s_fileCommandString );

}

// TclInterpreter::TclInterpreter( const TclInterpreter& iTclInterpreter )
// {
//    *this = iTclInterpreter;
// }

TclInterpreter::~TclInterpreter()
{
   saveHistory();

   delete &m_tclCommandNames;

   Tcl_DeleteInterp( m_tclInterpreter );
}

//
// assignment operators
//
// const TclInterpreter& TclInterpreter::operator=( const TclInterpreter& iTclInterpreter )
// {
//   if( this != &iTclInterpreter ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iTclInterpreter );
//   }
//
//   return *this;
// }

//
// member functions
//
void
TclInterpreter::initialize( DABoolean gui, int argc, char* argv[] )
{
   if( true == gui ) {
     //Tk_Main( argc, argv, Tk_AppInit);
   }
   else {

      // now done in ctor
      //Tcl_AppInit( m_tclInterpreter );
      //can't work: Tcl_Main( argc, argv, Tcl_AppInit ); 
      // because can't get ahold of interpreter, and Tcl_Main does too much!

      // different approach: set argc/v ourselves
      char buffer[1000], *args;
      Tcl_DString argString;
      
      args = Tcl_Merge(argc-1, argv+1);
      Tcl_ExternalToUtfDString(NULL, args, -1, &argString);
      Tcl_SetVar(m_tclInterpreter, "argv", Tcl_DStringValue(&argString), TCL_GLOBAL_ONLY);
      Tcl_DStringFree(&argString);
      ckfree(args);
      
#if 0
      if (fileName == NULL) {
	 Tcl_ExternalToUtfDString(NULL, argv[0], -1, &argString);
      } else {
	 fileName = Tcl_ExternalToUtfDString(NULL, fileName, -1, &argString);
      }
#endif
 
      //Tcl_FormatInt(buffer, argc-1);
      sprintf( buffer, "%d", argc-1 );
      Tcl_SetVar(m_tclInterpreter, "argc", buffer, TCL_GLOBAL_ONLY);
      Tcl_SetVar(m_tclInterpreter, "argv0", Tcl_DStringValue(&argString), TCL_GLOBAL_ONLY);
      
      Tcl_DStringFree(&argString);
   }
}

extern "C" {
static
int
exit_catcher(ClientData clientData, Tcl_Interp* interp,
	     int objc,
	     Tcl_Obj *const argv[]) {
  return reinterpret_cast<TclInterpreter*>(clientData)->catchExit();
}
}

int
TclInterpreter::catchExit()
{
   //if multiple calls to processCommandLine are done recursively,
   // pass the COMMAND_EXIT return value up until you get to the
   // very first call to catchExit
  ++m_sizeOfStackForCatchExit;
  int returnValue = Tcl_Eval( m_tclInterpreter,
			  Tcl_DStringValue( m_requestedCommands ) );
  if( 1 == m_sizeOfStackForCatchExit ) {
     m_exitRequested = false;
     if (Command::COMMAND_EXIT == returnValue ) {
	m_exitRequested = true;
	returnValue = TCL_OK;
     }
  }
  --m_sizeOfStackForCatchExit;
  return returnValue;
}

void
TclInterpreter::loop( )
{
   if ( 0 == activeModuleStackSize() ) {
      //no commands have been registered
      // this means that an exit has been processed
      // before we entered this loop
      //This can occur if one issues other Tcl commands
      // before entering this loop
      return;
   }
   unsigned int oldSizeOfStackForExit = m_sizeOfStackForExit;
   int result;

   //  need this to determine when we should abort the loop
   m_sizeOfStackForExit = activeModuleStackSize();

   --m_sizeOfStackForExit;
   
   
   string moduleCommandPrompt = commandPrompt();

   Tcl_DString presentCommand;
   Tcl_DStringInit( &presentCommand );

   //keep looping until user issues an 'exit' command
   m_exitRequested = false;
   while( ! m_exitRequested )
   {
      DABoolean complete = false;
      while( ! complete ) {
	 const string kIncompleteCommandPrompt =  moduleCommandPrompt.substr(0, moduleCommandPrompt.size() -2) + "...> ";

         complete = true;
         // A static variable for holding the line.
         static char *line_read = (char *)NULL;

	 //get a line from the user.

	 line_read = Readline::readline( commandPrompt() );

	 // stop when null line read
	 if( 0 == line_read ) {
	    static const char* exitCommand="quit";
	    static Count stringLength = strlen( exitCommand );
	    char* temp = static_cast<char*>( 
	       malloc( sizeof(char)*(stringLength+1) ) );
	    strncpy( temp, exitCommand, stringLength );
	    temp[stringLength]='\0';
	    line_read = temp;
	 }
	 else {   
	    // try to expand
	    char* expansion = Readline::history_expand( line_read );
	    if( 0 != expansion && expansion != line_read ) {
	       Readline::deleteLine( line_read );
	       line_read = expansion;
	       cout << line_read << endl;  // print expanded line 
	    }
	    
	    // If the line has any text in it, save it on the history.
	    Readline::addHistory( line_read );
	 }
	 //the command may change the prompt
         setCommandPrompt(moduleCommandPrompt.c_str());
	 result = processCommandLine( line_read, presentCommand);
	 if ( incompleteCommand(presentCommand) ) {
	    complete = false;
	    setCommandPrompt( kIncompleteCommandPrompt.c_str() );
	 } else {
	    //just incase the command we ran changed the prompt
	    moduleCommandPrompt = string(commandPrompt());
	 }
         // clean up
         Readline::deleteLine( line_read );
         line_read = (char *)NULL;
      }
   
      // now we do our own history mechanism; don't bother using tcl way
      // result = Tcl_RecordAndEval( m_tclInterpreter,
      //                             Tcl_DStringValue( &cmd ), 0 );
      if( TCL_ERROR == result ) {
         if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter) ) ) {
   	    report( ::SYSTEM, kFacilityString )
   	       << "Tcl_Eval error: " << Tcl_GetStringResult(m_tclInterpreter) << endl;
         }
      }
      else {
	if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter) ) ) {
	  cout << Tcl_GetStringResult(m_tclInterpreter) << endl;
	}
      }
   }
   //reset the variable
   m_sizeOfStackForExit = oldSizeOfStackForExit;
}

int
TclInterpreter::processCommandLine(const char* iCommandLine,
				   Tcl_DString& ioCommands)
{
   int returnValue = TCL_OK;
   if( 0 != iCommandLine ) {
      DABoolean lineContinues = false;
      int lineLength = strlen(iCommandLine);
      if( 0 < lineLength ) {
	 //see if we have a line continuation at the end of the line
	 if( iCommandLine[lineLength-1] == '\\' ) {
	    lineContinues = true;
	    lineLength -= 1;
	 }
	 Tcl_DStringAppend( &ioCommands, iCommandLine, lineLength );

	 if ( lineContinues ||  
	      ! Tcl_CommandComplete( Tcl_DStringValue( &ioCommands ) ) ) {
	    if(!lineContinues ) {
	       Tcl_DStringAppend( &ioCommands, "\n", 1 ); // separate commands
	    } else {
	       Tcl_DStringAppend( &ioCommands, " ", 1 ); // separate commands
	    }
	 } else {
	    //Since it is an error for 'top level' applications to see
	    // any return from Tcl_Eval other than TCL_OK and TCL_ERROR
	    // I need to 'trap' the exit return code just before reaching
	    // the 'top' level.  I do this by injecting a 'exit_catcher' command
	    // which actually will execute the command in ioCommands AND 
	    // it will look at the return code to see if an 'exit' was requested
	    
	    m_requestedCommands = &ioCommands;
	    
	    Tcl_CreateObjCommand(m_tclInterpreter,
				 "exit_catcher",
				 exit_catcher,
				 this,
				 NULL);
	    returnValue = Tcl_Eval( m_tclInterpreter,
				    "exit_catcher" );
	    Tcl_DeleteCommand(m_tclInterpreter, "exit_catcher");
	    Tcl_DStringFree( &ioCommands );
	    if (m_exitRequested ) {
	       //Only report the exit if the exit command was for the
	       //  module we had when we started the loop call.
	       if (m_sizeOfStackForExit != activeModuleStackSize() ) {
		  m_exitRequested = false;
		  returnValue = TCL_OK;
	       }
	    }
	 }
      }
   }
   return returnValue;
}

DABoolean
TclInterpreter::incompleteCommand(Tcl_DString& iCommands) const
{
   return Tcl_DStringLength(&iCommands) > 0;
}

void
TclInterpreter::createCommand( const Command* command )
{
   Tcl_CreateCommand( m_tclInterpreter, (char*)command->name().c_str(),
		      (Tcl_CmdProc*) commandHandler, (ClientData)command, 
		      (Tcl_CmdDeleteProc*) NULL );  
   Readline::registerCommand( (const char*)command->name().c_str() );
}

void
TclInterpreter::deleteCommand( const char* command )
{
   Tcl_DeleteCommand( m_tclInterpreter, (char *)command );
   Readline::deregisterCommand( command );
}

int
TclInterpreter::runCommandFile( const char* filename )
{
   string command = s_sourceCommandString + string( " " ) + string( filename );
   int result = Tcl_Eval( m_tclInterpreter, 
			  (char*)command.c_str() );
   if( TCL_ERROR == result ) {
      if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter) ) ) {
	 report( ::SYSTEM, kFacilityString )
	    << "Tcl_Eval error: " << Tcl_GetStringResult(m_tclInterpreter) << endl;
      }
   }

   return result;
}

int 
TclInterpreter::runCommand( char* command )
{
   // evaluate command
   int result = Tcl_Eval( m_tclInterpreter,
			  command );
   if( TCL_ERROR == result ) {
      if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter) ) ) {
	 report( ::SYSTEM, kFacilityString )
	    << "Tcl_Eval error: " << Tcl_GetStringResult(m_tclInterpreter) << endl;
      }
   }

   return result;
}

int
TclInterpreter::runCommand( int argc, char* argv[] )
{
   int index=0;
   string command;
   while( index < argc )
   {
      command += string(" ") + argv[index];
      ++index;
   }

   int length = command.size();
   char* c_command = new char[ length+1 ];
   strcpy( c_command, command.c_str() );
   c_command[ length ] = '\0';

   // evaluate composite command
   int result = Tcl_Eval( m_tclInterpreter,
			  c_command );
   delete [] c_command;

   if( TCL_ERROR == result ) {
      if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter) ) ) {
	 report( ::SYSTEM, kFacilityString )
	    << "Tcl_Eval error: " << Tcl_GetStringResult(m_tclInterpreter) << endl;
      }
   }

   return result;
}

void
TclInterpreter::setResult( const char* result )
{
   Tcl_SetResult( m_tclInterpreter, (char*)result, TCL_VOLATILE );
}

// history stuff
void
TclInterpreter::readHistory()
{
   // enable history mechanism
   Readline::using_history();

   assembleHistoryFile();

   Readline::read_history( m_historyFile.c_str() );
}

void
TclInterpreter::saveHistory()
{
   //Only save history if
   // 1) we are not in a batch job (i.e. we have a terminal connected
   //    which is determined by seeing if stdout is connected to a tty device)
   // 2) we actually have some history to save
   if( isatty(STDIN_FILENO) && ( 0 != Readline::history_length() ) ) {
      assembleHistoryFile();

      //create a temporary file which we will use while writing the history
      const char* kTempExtension = "_please_delete_XXXXXX";
      char* pTempFileName = new char[1+ strlen(kTempExtension)+ m_historyFile.size()];
      strcpy(pTempFileName, m_historyFile.c_str());
      strcpy(pTempFileName+m_historyFile.size(), kTempExtension);
      //now change the XXXXXX in the name to a pseudo-random number
      if( 0 != mktemp(pTempFileName) ) {	 
	 Readline::write_history( pTempFileName );
	 Readline::history_truncate_file( pTempFileName, m_historyLength );
	 //now move our temporary file to its proper name
	 rename(pTempFileName, m_historyFile.c_str());
      }
      delete [] pTempFileName;
   }
}

void
TclInterpreter::assembleHistoryFile()
{
   // have to assemble history file
   if( m_historyFile == string( "" ) )
   {
      if( 0 == getenv( "HOME" ) )
      {   
	 report( SYSTEM, kFacilityString )
	    << "HOME environment variable not valid;\n"
	    << "will save history in current directory!"
	    << endl;
	 m_historyFile = string( ".suez_history" );
      }
      else
      {
	 m_historyFile = getenv( "HOME" ) + string( "/.suez_history" );
      }
   }
}

void 
TclInterpreter::setHistoryLength( Count iLength )
{
   m_historyLength = iLength;
}

void 
TclInterpreter::setHistoryFile( const string& iFile )
{
   m_historyFile = iFile;
}

void 
TclInterpreter::printHistoryInfo() const
{
   report( SYSTEM, kFacilityString )
      << "History Status:\n"
      << "  File  : " << m_historyFile << "\n"
      << "  Length: " << m_historyLength 
      << endl;
}

void
TclInterpreter::printHistory() const
{
   Readline::print_history_list();
}

Tcl_Interp*
TclInterpreter::tclInterpreter()
{
   return m_tclInterpreter;
}

//
// const member functions
//
Interpreter::StatusCode
TclInterpreter::parseArgs( const string, int, char*[] ) const
//                         const string formalCmd, 
//			   int argc, char *argv[] ) const
{
   report( ::SYSTEM, kFacilityString )
      << "parseArgs: not implemented yet!" << endl;

   return Interpreter::OK;
}                 

const Tcl_Interp* 
TclInterpreter::tclInterpreter() const
{
   return m_tclInterpreter;
}

//
// static member functions
//
int
TclInterpreter::commandHandler( ClientData clientData, 
				Tcl_Interp*,
				int argc, char* argv[] )
{
    assert( NULL != clientData );
    
    Command* command = command = (Command*)clientData;
    return command->execute( argc, argv );
}

static 
istream& 
eatwhite( istream& is )
{
   // kill white space until hit actual command
   char c;
   while( is.get( c ) ) {
      if( isspace( c ) ) { continue; } else { is.putback( c ); break; }
   }

   return is;
}

class TclRefCountHolder {
   public:
      TclRefCountHolder(Tcl_Obj* iObj) :
	 m_obj(iObj) {
	    Tcl_IncrRefCount(iObj);
      }
      ~TclRefCountHolder() {
	 Tcl_DecrRefCount(m_obj);
      }
      Tcl_Obj* get() {
	 return m_obj;
      }
   private:
      Tcl_Obj* m_obj;
};

int
TclInterpreter::sourceCommand( const char* iFileName)
{
#if defined(OLD_WAY)
   // old way
   int result = Tcl_EvalFile( interp, (char*)iFileName );
   return result;

#else
   // new way
   ifstream ifs( iFileName );
   if( !ifs ) {
      report( ::SYSTEM, kFacilityString )
	 << "Error opening file " << iFileName << endl;
      return TCL_ERROR;
   }


   //The command prompt will include the module we are in
   // and the file we are reading, along with whether or not
   // this command is complete
   string moduleCommandPrompt = commandPrompt();
   const string kBaseName = FileNameUtils::basename(iFileName);
   string prompt = moduleCommandPrompt.substr(0, moduleCommandPrompt.size() -2) + "." + kBaseName +"> ";
   string incompletePrompt = prompt.substr(0,prompt.size()-2) +"...> ";
   int result = TCL_OK;

   Tcl_DString presentCommand;
   Tcl_DStringInit( &presentCommand );

   //Need to set the value returned from 'info script' to point
   // to our new script
   // We do this by calling 'info script <iFileName>'
   // We must also be sure to restore the old value once we 
   //  are done with this script since scripts can call scripts
   TclRefCountHolder fileNameHolder ( Tcl_NewStringObj(iFileName,-1) );
   TclRefCountHolder infoHolder( Tcl_NewStringObj("info",-1) );
   TclRefCountHolder scriptHolder( Tcl_NewStringObj("script",-1) );

   Tcl_Obj* commandArray[3];
   commandArray[0] = infoHolder.get();
   commandArray[1] = scriptHolder.get();
   commandArray[2] = fileNameHolder.get();

   //get old value by doing 'info script'
   Tcl_EvalObjv(m_tclInterpreter, 2,commandArray,TCL_EVAL_GLOBAL);
   TclRefCountHolder oldFileNameHolder (Tcl_GetObjResult(m_tclInterpreter));

   //now set new value
   Tcl_EvalObjv(m_tclInterpreter, 3, commandArray,TCL_EVAL_GLOBAL);

   const string* pPrompt = &prompt;
#if defined(NO_GETLINE_ISTREAM_STRING_BUG)
   const int kLineLength = 500;
   char line[ kLineLength ];
   while( eatwhite( ifs ).getline( line, kLineLength ) )
   {
      //don't print echo lines
      if( strncmp( line, "echo",4) != 0 ) {
	 cout << *pPrompt << line <<endl;
      }
      result = processCommandLine( line, presentCommand );
#else
   string line;
   while( getline( eatwhite( ifs ), line ) )
   {
      //don't print echo lines
      if( strncmp( line.c_str(), "echo",4) != 0 ) {
	 cout << *pPrompt << line <<endl;
      }
      result = processCommandLine( line.c_str(), presentCommand );
#endif
      if (result != TCL_OK) {
	 break;
      }
      if ( !incompleteCommand(presentCommand) ) {
	 //the command prompt may have changed
	 moduleCommandPrompt = commandPrompt();
	 prompt = moduleCommandPrompt.substr(0, moduleCommandPrompt.size() -2) + "." + kBaseName +"> ";

	 pPrompt = &prompt;

	 if( 0 != strlen( Tcl_GetStringResult(m_tclInterpreter)) ) {
	    cout << Tcl_GetStringResult(m_tclInterpreter) << endl;
	 }
      } else {
	 //the command prompt can not change while the command is
	 // incomplete
	 incompletePrompt = prompt.substr(0,prompt.size()-2) +"...> ";
	 pPrompt = &incompletePrompt;
      }
   }

   //restore the old value of 'info script'
   commandArray[2] = oldFileNameHolder.get();
   Tcl_EvalObjv(m_tclInterpreter, 3, commandArray,TCL_EVAL_GLOBAL);
   
   ifs.close();
#endif
   return result;
}

int
TclInterpreter::sourceCommandHandler( ClientData clientData, 
				      Tcl_Interp* interp,
				      int argc, char* argv[] )
{
   if( argc < 2 ) {
      report( ::SYSTEM, kFacilityString )
	 << "no arguments for " << argv[0] << " command" << endl;
      return TCL_ERROR;
   }

   const char*const filename = argv[1];

   return static_cast<TclInterpreter*>(Interpreter::interpreter())->sourceCommand(filename);
}


// -------------------------------------------------------------------
// Revision history
//
// $Log: TclInterpreter.cc,v $
// Revision 1.47  2004/03/06 21:32:14  cdj
// Made behavior closer to tclsh
//    -backslash at end of line is now a continuation
//    -'info script' now returns the file name of the script being processed
//
// Revision 1.46  2004/02/26 02:22:20  cdj
// changed sourceCommand to sourceCommandHandler to avoid name confusion when using Tcl 8.4
//
// Revision 1.45  2004/02/18 20:25:11  cdj
// can once again use exit in a run_file command
//
// Revision 1.44  2004/02/16 15:10:22  cdj
// added code to trap exit Tcl return code before it gets to the 'top' application layer (needed for Tcl8.4)
//
// Revision 1.43  2003/03/31 21:15:42  cdj
// made files names more unique to avoid problems on OS X (Darwin)
//
// Revision 1.42  2002/12/10 18:20:55  cdj
// bug fix: no longer get erroneous xalloc out of memory error on OSF when multiple suez jobs trying to use .suez_history file.  No longer write history if this is a batch job OR there is no history to write.
//
// Revision 1.41  2002/11/21 21:10:58  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.40  2002/08/16 15:04:43  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.39  2002/08/09 22:38:19  cdj
// replaced C style cast with static_cast
//
// Revision 1.38  2002/08/08 13:46:07  cleo3
// removed invalid use of reinterpret_cast
//
// Revision 1.37  2002/02/20 16:47:11  cdj
// fixed problem that occurred if exit issued before entering Interpreter::loop()
//
// Revision 1.36  2002/02/19 19:02:31  cdj
// Made the run_file command do immediate execution and added more state info on command prompt
//
// Revision 1.35  2002/01/03 20:59:47  cdj
// fixed minor typo in a comment
//
// Revision 1.34  2002/01/03 20:20:20  cdj
// Now properly handle case where Suez commands are imbedded within other Tcl commands.
//
// Revision 1.33  2001/02/23 01:40:37  cleo3
// fixed memory ownership problems
//
// Revision 1.32  2000/06/01 17:50:28  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.31  2000/05/18 22:58:12  mkl
// invalid command now raises tcl error
//
// Revision 1.30  2000/05/17 16:58:08  mkl
// quite suez when null-line read (e.g. end-of-file
//
// Revision 1.29  2000/05/15 20:35:06  mkl
// ignore rest of command stack when error is encountered: this way an error will stop script execution
//
// Revision 1.28  2000/04/19 15:49:37  mkl
// eat white space properly when parsing tcl commands (tabs)
//
// Revision 1.27  2000/04/06 19:31:45  mkl
// report tcl errors in runCommand method explicitly; people forget to check returnvalue
//
// Revision 1.26  2000/04/03 19:27:47  mkl
// now pass on argc and argv to Tcl Interpreter properly
//
// Revision 1.25  2000/03/16 22:51:35  mkl
// fix memory mismatch (malloc and free)
//
// Revision 1.24  1999/10/05 20:23:12  mkl
// kludge run_file to work properly in nested calls
//
// Revision 1.23  1999/09/14 18:35:29  mkl
// new run_file command wants to replace tcl_source
//
// Revision 1.22  1999/09/10 01:24:43  mkl
// new history command
//
// Revision 1.21  1999/07/05 20:58:25  mkl
// history length=200 (was 50); increase length of lines for tcl_source command to 500 (was 120); new bug flag NO_GETLINE_ISTREAM_STRING_BUG
//
// Revision 1.20  1999/04/19 18:02:18  mkl
// added info on tcl via web pages
//
// Revision 1.19  1999/04/08 16:14:18  mkl
// dont source init.tcl, more trouble than help
//
// Revision 1.18  1999/02/22 23:38:46  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.17  1998/09/23 18:20:46  mkl
// handle nested calls in runCommandFile
//
// Revision 1.16  1998/09/08 19:18:43  mkl
// removed superfluous const qualifiers
//
// Revision 1.15  1998/08/22 21:58:41  mkl
// use new StringTokenizer to parse strings into substrings based on a delimiter
//
// Revision 1.14  1998/08/20 19:48:32  mkl
// allow nested tcl_source calls
//
// Revision 1.13  1998/07/30 21:16:50  mkl
// increase number of saved history entries to 50
//
// Revision 1.12  1998/06/30 19:54:22  mkl
// fixed bug when using Ctrl-d at command-prompt
//
// Revision 1.11  1998/06/12 22:20:28  mkl
// only print Tcl_Eval error, if error string non-null
//
// Revision 1.10  1998/06/12 18:24:02  mkl
// fix bugs introduced by recent history mechanism
//
// Revision 1.9  1998/05/20 01:59:08  mkl
// fixed memory leak in history expansion
//
// Revision 1.8  1998/05/11 19:33:14  mkl
// make history-file mechanism more fool-proof
//
// Revision 1.7  1998/05/09 20:33:46  mkl
// make g++ happy: ambiguous string operator
//
// Revision 1.6  1998/05/07 21:42:24  mkl
// clean up of code changes for history mechism
//
// Revision 1.5  1998/05/07 15:34:06  mkl
// implement history mechanism; implement proper tcl_source command
//
// Revision 1.4  1998/03/28 17:44:29  mkl
// get rid of g++ warnings (comp. signed/unsigned etc.
//
// Revision 1.3  1998/03/26 20:01:10  mkl
// added gnu readline support
//
// Revision 1.2  1998/03/23 23:29:40  mkl
// added gnu readline support to TclInterpreter; added runCommand method
//
// Revision 1.1.1.1  1998/03/11 18:52:18  mkl
// imported Interpreter sources
//
