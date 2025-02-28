#include "C++Std/iostream.h"

#include <string>

#include "Experiment/Experiment.h"
#include "CommandPattern/StringUtilities.h"

int main()
{
   cout << "Please input path+name (e.g. \"/home/mkl/file.txt\")" << endl;

   string fullThing;
   cin >> fullThing;

   // path
   string path = StringUtil::path( fullThing );
   cout << "Path = " << path << endl;

   // filename
   string filename = StringUtil::filename( fullThing );
   cout << "Filename = " << filename << endl;

   // basename
   string basename = StringUtil::basename( fullThing );
   cout << "Basename = " << basename << endl;

   // extension
   string extension = StringUtil::extension( fullThing );
   cout << "Extension = " << extension << endl;
   
   return 0;
}


#if 0 /* old */
typedef char* _vector_contents_;
#include "STLUtility/instantiate_vector.h"

//typedef char* _argument_;
//#include "STLUtility/instantiate_algorithm.h"

typedef char*                    _for_each_element_type_ ;
typedef _for_each_element_type_* _for_each_iterator_     ;
typedef void                     _for_each_function_type ;
#include "STLUtility/instantiate_for_each.h"

   // path
   vector<char> path;
   path = StringUtil::path( fullThing, path );
   cout << "Path = " << StringUtil::vecToString( path, output ) << endl;

   string spath;
   spath = StringUtil::path( fullThing, spath );
   cout << "SPath = " << spath << endl;

   // filename
   vector<char> filename;
   filename = StringUtil::filename( fullThing, filename );
   cout << "Filename = " << StringUtil::vecToString( filename, output ) << endl;

   string sfilename;
   sfilename = StringUtil::filename( fullThing, sfilename );
   cout << "SFilename = " << sfilename << endl;

   // basename
   vector<char> basename;
   basename = StringUtil::basename( fullThing, basename );
   cout << "Basename = " << StringUtil::vecToString( basename, output ) << endl;

   string sbasename;
   sbasename = StringUtil::basename( fullThing, sbasename );
   cout << "SBasename = " << sbasename << endl;

   // extension
   vector<char> extension;
   extension = StringUtil::extension( fullThing, extension );
   cout << "Extension = " << StringUtil::vecToString( extension, output ) << endl;
   
   string sextension;
   sextension = StringUtil::extension( fullThing, sextension );
   cout << "SExtension = " << sextension << endl;
#endif
