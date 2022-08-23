#include "../toyrobotlib/include/toyrobot.hpp"
#include "../toyrobotlib/include/commandhandler.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    //auto robot1 = iress::ToyRobot();
    
    std::string input;
    std::cout << "Enter the Input File to Start Simulation. Enter q to quit." << "\n";
    std::cin >> input;

    while (input != "q") {
        auto robot1 = iress::ToyRobot();
        std::string path = "./inputs/" + input + ".txt";
        robot1.runCommands(path);
        std::cout << "Enter the Input File to Start Simulation. Enter q to exit." << "\n";
        std::cin >> input;
    }

    return 0;
}