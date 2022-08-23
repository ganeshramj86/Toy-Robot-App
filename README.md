# Toy Robot App
This is a simple app built in C++ 11 to simulate a toy robot on a square table top. The toy robot can take the following commands:
PLACE, MOVE, LEFT, RIGHT and REPORT. The project structure is below:
- .vscode
- simulation
    - inputs
    - CMakeLists.txt
    - simulation.cpp
- test
    - inputs
    - catch.hpp
    - CMakeLists.txt
    - integration_test.cpp
    - test_command_handler.cpp
    - test_toyrobot.cpp
- toyrobotlib
    - include
        - commandhandler.hpp
        - config.hpp
        - toyrobot.hpp
    - src
        - commandhandler.cpp
        - config.cpp
        - toyrobot.cpp
    - CMakeLists.txt
- CMakeLists.txt

### Brief Description about project folders
.vscode:

This folder contains settings.json for use with Visual Studio Code IDE. This is used to specify CMAKE parameters like source directory and 
configuration settings such as CMAKE_AR and CMAKE_MAKE_PROGRAM.

simulation:

The main program to exercise the application. This is used to create a toy robot object, read an input file name from CLI and executes commands.
The inputs folder contains all the input test data to test the app. The CMakeLists is used to create an executable to run the simulation application.

test:

This folder contains all the unit and integration test for the app. The tests are run using CATCH2 (https://github.com/catchorg/Catch2) framework.
The catch2 is a header only framework and the header catch.hpp is included in this folder. Three test executables are created: to test command handling,
command execution and integration. The inputs folder contain all the test input data for integration tests. The CMakeLists file link the tests to CTest.

toyrobotlib:

The project source files has a class for ToyRobot for the toy robot to maintain and update its status by using member functions
to execute the commands. The command handling functions are put in a separate file commandhandler as they are not dependent on
toy robot states. Finally, a config file is used to declare and define all the global constants and containers.

## Setup and Running App
The app utilizes CMake software for compiling, building and testing the app. The app has been successfully tested across different operating systems 
(Windows and Linux), across different compilers (GCC and Clang compilers) and across IDE (Integrated Developent Environment) and CLI (Command Line Interface).

### Windows Setup and Run
In order to setup, first a suitable GCC compiler has to be installed in the system. For Windows MinGW, MSYS and Clang are available compilers to build this app.
For reference on installing and setting environment path for MinGW and MSYS, the following links are useful:
https://www.geeksforgeeks.org/installing-mingw-tools-for-c-c-and-changing-environment-variable/
https://docs.epics-controls.org/projects/how-tos/en/latest/getting-started/installation-windows-msys2.html

Further instructions assume that a suitable GCC compiler like MinGW or MSYS is installed in a Windows 10 based computer and corresponding system environment variables
are set. The app was tested on Windows 10 under MinGW (GCC 9.2.0 mingw32) and under MSYS2.0(GCC 11.2.0 x86_64-w64-mingw32).

#### Steps for Command Line (Windows):
1. Open a command prompt or windows terminal and cd to toyrobotapp folder
2. Create build folder: 

    mkdir build
3. Change to build directory:

    cd build
4. Configure:

    cmake ..
    
    This should work if the C and CXX compiler had been set sytem wide, else it will throw an error.
    
    If an error occurs then try the following command format:

    cmake -G preferredGenerator -D CMAKE_C_COMPILER="full/path/to/gcc" -D CMAKE_CXX_COMPILER="full/path/to/g++" ..
    
    For MinGW:
    
    cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER="C:/MinGW/bin/gcc.exe" -D CMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe" ..
    
    For MSYS2:
    
    cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" -D CMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" ..

5. Build:

    mingw32-make

6. Run All Tests:

    ctest

7. Run Individual Tests:

    cd test
    
    .\test_command_handler.exe
    
    .\test_toyrobot.exe
    
    .\integration_test.exe
    
8. Run Individual Tests with Options:

    For listing elaborate each and every assertions in test cases:
    
    .\test_command_handler.exe -s
    
    For listing only the test names
    
    .\test_command_handler.exe --list-test-names-only
    
    For listing test names and execution times
    
    .\test_command_handler.exe -d yes

    Similar commands for test_toyrobot.exe and integration_test.exe
    
9. Run Simulation application:

    cd ..
    
    cd simulation
    
    .\simulation.exe

    The app will run and ask for the input file name. Provide any of the files names found in build/simulation/inputs or simulation/inputs.
    Actually the input files are copied to build folder during building process.

#### Steps for Visual Studio (VS) Code IDE (Windows):
1. Open VS code IDE and open app folder or open windows terminal, cd to app folder and then enter 
        code .
2. Press Ctrl + Shift + P to open command pallete and enter "CMake: Select a Kit" and choose appropriate GCC compiler from drop down menu
3. Press Ctrl + Shift + P to open command pallete and enter "CMake: Configure" to configure the project
    If the compiler is good, then configure will be successful and build folder will created and configured
    If this step throws error, then may need to edit settings.json in .vscode folder to set the cmake.generator, CMAKE_AR and CMAKE_MAKE_PROGRAM
4. If the configure is success, then the blue status bar at the bottom of IDE will show the chosen GCC.
5. In the blue status bar at the bottom of IDE, click on the Build button to build the app.
6. Then, click on Run CTest on the blue status bar at the bottom of IDE which will run all tests and report status
7. To run indivdual test or simulation app, follow the same procedure described in Command Line above but using the terminal provided inside VS Code IDE.

### Linux Setup and Run
In order to install a compiler such as GCC or Clang on Linux, the following links will be useful.
https://www.geeksforgeeks.org/how-to-install-gcc-compiler-on-linux/
https://clang.llvm.org/get_started.html

Also, Ninja, a small build system with a focus on speed, was used to build the project on Linux. The pre built Ninja packages can be installed using systems's
package manager as shwon in the link below:
https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages

Further instructions assume that a suitable compiler like GCC or Clang and Ninja build system is installed in a Unix/ Linux based computer and corresponding system environment variables
are set. The app was tested on Xcef desktop under GNU GCC (GCC 10.2.1 x86_64-linux-gnu) and under Clang (Clang 11.0.1 x86_64-pc-linux-gnu).

#### Steps for Command Line (Linux):
1. Open a terminal and cd to toyrobotapp folder
2. Create build folder:

    mkdir build
3. Change to build directory:

    cd build
4. Configure:

    cmake ..
    
    This should work if the C and CXX compiler had been set sytem wide, else it will throw an error.
    
    If an error occurs then try the following command format:
    
    For GCC:
    
    cmake -G "Ninja" -D CMAKE_C_COMPILER="/usr/bin/gcc" -D CMAKE_CXX_COMPILER="/usr/bin/g++" ..
    
    For Clang:
    
    cmake -G "Ninja" -D CMAKE_C_COMPILER="/usr/bin/clang-11" -D CMAKE_CXX_COMPILER="/usr/bin/clang++-11" ..

5. Build:

    cmake --build .

6. Run All Tests:

    ctest
    
7. Run Individual Tests:

    cd test
    
    ./test_command_handler
    
    ./test_toyrobot
    
    ./integration_test
    
8. Run Individual Tests with Options:

    For listing elaborate each and every assertions in test cases:
    
    ./test_command_handler -s
    
    For listing only the test names
    
    ./test_command_handler --list-test-names-only
    
    For listing test names and execution times
    
    ./test_command_handler -d yes

    Similar commands for test_toyrobot and integration_test./test
9. Run Simulation application:

    cd ..
    
    cd simulation
    
    ./simulation

    The app will run and ask for the input file name. Provide any of the files names found in build/simulation/inputs or simulation/inputs.
    Actually the input files are copied to build folder during building process.

#### Steps for Visual Studio (VS) Code IDE (Linux):
1. Open VS code IDE and open app folder or open windows terminal, cd to app folder and then enter 
        code .
2. Press Ctrl + Shift + P to open command pallete and enter "CMake: Select" a Kit and choose appropriate GCC compiler from drop down menu
3. Press Ctrl + Shift + P to open command pallete and enter "CMake: Configure" to configure the project
    If the compiler is good, then configure will be successful and build folder will created and configured
    If this step throws error, then may need to edit settings.json in .vscode folder to set the cmake.generator, CMAKE_AR and CMAKE_MAKE_PROGRAM
4. If the configure is success, then the blue status bar at the bottom of IDE will show the chosen GCC.
5. In the blue status bar at the bottom of IDE, click on the Build button to build the app.
6. Then, click on Run CTest on the blue status bar at the bottom of IDE which will run all tests and report status
7. To run indivdual test or simulation app, follow the same procedure described in Command Line above but using the terminal provided inside VS Code IDE.