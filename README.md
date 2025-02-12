# sbe-cpp
sbe encoding testing with cpp

First, let's check the prerequisites:

C++ compiler (GCC 4.x+ or Clang)
CMake (3.x+)
Python (for code generation)
Java Runtime Environment (JRE)

To install SBE, you'll need to:
bashCopygit clone https://github.com/real-logic/simple-binary-encoding.git
cd simple-binary-encoding
mkdir build && cd build
cmake ..
make
make install

java -cp ~/repo/cpp/simple-binary-encoding/sbe-all/build/libs/sbe-all-1.35.0-SNAPSHOT.jar   -Dsbe.output.dir=trading   -Dsbe.target.language=Cpp   uk.co.real_logic.sbe.SbeTool   sbe_schema_order_messages.xml

g++ -std=c++11 -I. main.cpp -o order_example

 ./order_example

