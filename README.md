# ImarisReaderTest

Test project for ImarisReader library.

### Dependencies

1. ImarisReader: https://github.com/imaris/ImarisReader
2. For use with Java only, Java Native Access library, version >= 5.14.0: https://github.com/java-native-access/jna

### Build and Run

- C++ test program
  
  On macOS:
  ```bash
  clang++ -arch arm64 -std=c++11 -o cppTest cppReaderTest.cpp -I<parent_dir_of_ImarisReader> -L<dir_of_ImarisReader_dylib> -lbpImarisReader
  ./cppTest
  ```
- C test program
  
  On macOS:
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
