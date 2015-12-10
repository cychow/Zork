#ifndef TINYXML2_H
#define TINYXML2_H
#include "tinyxml2/tinyxml2.h"
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#include "zorkMap.h"
#include "zorkObj.h"

//using namespace std;
int main(int argc, char* argv[]) {
   tinyxml2::XMLDocument * mapDoc = new tinyxml2::XMLDocument();
   std::string filename;
   // load XML file
   if (argc !=2) {
      std::cout << "Loading default file: sample.txt.xml" << std::endl;
      filename = "./maps/sample.txt.xml";
   } else {
      std::cout << "Loading file: " << argv[1] << std::endl;
      filename = argv[1];
   }
   tinyxml2::XMLError errType = mapDoc->LoadFile(filename.c_str());
   if (errType != 0) {
      std::cerr << "ERROR:\tFailed to parse " << filename << "; error " << errType << ": ";
      std::cerr << mapDoc->ErrorName() << std::endl;
      //std::cerr << map.GetErrorStr2() << std::endl;
      return 1;
   } else {
      std::cout << "Successfully loaded " << filename << std::endl;
   }
   
   // Check if root node is map
   
   zorkMap::zorkMap * map = new zorkMap::zorkMap(mapDoc);

   return 0;
}
