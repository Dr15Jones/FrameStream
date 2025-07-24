#include <iostream>

#include <string>

#include "Experiment/Experiment.h"
#include "CommandPattern/StringUtilities.h"

int main()
{
   cout << "Please input path+name (e.g. \"/home/mkl/file.txt\")" << std::endl;

   std::string fullThing;
   cin >> fullThing;

   // path
   std::string path = StringUtil::path( fullThing );
   cout << "Path = " << path << std::endl;

   // filename
   std::string filename = StringUtil::filename( fullThing );
   cout << "Filename = " << filename << std::endl;

   // basename
   std::string basename = StringUtil::basename( fullThing );
   cout << "Basename = " << basename << std::endl;

   // extension
   std::string extension = StringUtil::extension( fullThing );
   cout << "Extension = " << extension << std::endl;
   
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
   cout << "Path = " << StringUtil::vecToString( path, output ) << std::endl;

   std::string spath;
   spath = StringUtil::path( fullThing, spath );
   cout << "SPath = " << spath << std::endl;

   // filename
   vector<char> filename;
   filename = StringUtil::filename( fullThing, filename );
   cout << "Filename = " << StringUtil::vecToString( filename, output ) << std::endl;

   std::string sfilename;
   sfilename = StringUtil::filename( fullThing, sfilename );
   cout << "SFilename = " << sfilename << std::endl;

   // basename
   vector<char> basename;
   basename = StringUtil::basename( fullThing, basename );
   cout << "Basename = " << StringUtil::vecToString( basename, output ) << std::endl;

   std::string sbasename;
   sbasename = StringUtil::basename( fullThing, sbasename );
   cout << "SBasename = " << sbasename << std::endl;

   // extension
   vector<char> extension;
   extension = StringUtil::extension( fullThing, extension );
   cout << "Extension = " << StringUtil::vecToString( extension, output ) << std::endl;
   
   std::string sextension;
   sextension = StringUtil::extension( fullThing, sextension );
   cout << "SExtension = " << sextension << std::endl;
#endif
