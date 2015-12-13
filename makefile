debug: src/zork.cpp
	g++ src/tinyxml2/tinyxml2.cpp src/*.cpp -o ./Debug/Zork -std=c++0x

release: src/zork.cpp
	g++ src/tinyxml2/*.cpp src/*.cpp -o ./Release/Zork -std=c++0x
