# ImarisReaderTest

Test project for ImarisReader library.

### Dependencies

1. ImarisReader: https://github.com/imaris/ImarisReader
2. For use with Java, Java Native Access library, version >= 5.14.0: https://github.com/java-native-access/jna

### Build and Run

- C++ test program

  To build with CMake, copy the ImarisReader library and ImarisReader/interface to the ImarisReaderTest folder then run the following commands:
  ```bash
  cd ImarisReaderTest
  cmake .
  ```
  On Windows, the generated solution files can be opened and compiled with Visual Studio, while on Mac the generated Makefile can be compiled with ```make```. The Visual Studio version should be specified according to the setup of the other libraries, e.g. adding ```-G "Visual Studio 14 Win64"```.
  
  Alternatively, build and run using g++/clang++. For example, on macOS:
  ```bash
  clang++ -arch arm64 -std=c++11 -o cppTest cppReaderTest.cpp -I<parent_dir_of_ImarisReader> -L<dir_of_ImarisReader_dylib> -lbpImarisReader
  ./cppTest
  ```
- C test program
  
  To build with CMake, copy the ImarisReader library and ImarisReader/interfaceC to the ImarisReaderTest folder. Modify the CMakeLists.txt file: change ```add_executable(ImarisReaderTest cppReaderTest.cpp)``` to ```add_executable(ImarisReaderTest cReaderTest.c)``` and uncomment ```set_source_files_properties(cReaderTest.c PROPERTIES LANGUAGE CXX)```. Then run the following commands:
  ```bash
  cd ImarisReaderTest
  cmake .
  ```
  On Windows, the generated solution files can be opened and compiled with Visual Studio, while on Mac the generated Makefile can be compiled with ```make```. The Visual Studio version should be specified according to the setup of the other libraries, e.g. adding ```-G "Visual Studio 14 Win64"```.
  
  Alternatively, build and run using g++/clang++. For example, on macOS:
  ```bash
  clang++ -arch arm64 -std=c++11 -o cTest cReaderTest.c -I<parent_dir_of_ImarisReader> -L<dir_of_ImarisReader_dylib> -lbpImarisReader
  ./cTest
  ```
- Java test program
  
  Move the ImarisReader executable and the Java interface (ImarisReader/java/JavaImarisReader/jImarisReader.java) to the folder containing javaReaderTest.java, then run:
  ```bash
  export CLASSPATH=${CLASSPATH}:/path/to/jna-5.14.0.jar
  javac javaReaderTest.java
  java javaReaderTest
  ```
- Python test program
  
  Move the ImarisReader executable and the Python interface (ImarisReader/python/PyImarisReader/PyImarisReader.py) to the folder containing pythonReaderTest.py, then run:
  ```bash
  python3 pythonReaderTest.py
  ```
