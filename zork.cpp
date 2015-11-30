#ifndef TINYXML2_H
#define TINYXML2_H
#include "tinyxml2/tinyxml2.h"
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

//using namespace std;
int main(int argc, char* argv[]) {
   tinyxml2::XMLDocument map;
   std::string filename;
   // load XML file
   if (argc !=2) {
      std::cout << "Loading default file: sample.txt.xml" << std::endl;
      filename = "sample.txt.xml";
   } else {
      std::cout << "Loading file: " << argv[1] << std::endl;
      filename = argv[1];
   }
   tinyxml2::XMLError errType = map.LoadFile(filename.c_str());
   if (errType != 0) {
      std::cerr << "ERROR:\tFailed to parse " << filename << "; error " << errType << ": ";
      std::cerr << map.ErrorName() << std::endl;
      //std::cerr << map.GetErrorStr2() << std::endl;
      return 1;
   } else {
      std::cout << "Successfully loaded " << filename << std::endl;
   }
   
   // Check if root node is map
   tinyxml2::XMLElement * root = map.RootElement();
   if (strcmp(root->Name(),"map") != 0) {
      std::cerr << "ERROR:\tUnexpected first node; expected 'map' got '" << root->Name() << "'." << std::endl;
      return 1;
   }
   
   // Parse all objects in map
   return 0;
}