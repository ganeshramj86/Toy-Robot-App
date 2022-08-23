#ifndef TOYROBOT_HPP_INCLUDED
#define TOYROBOT_HPP_INCLUDED

#include<ostream>
#include <iostream>
#include <stdexcept>

namespace iress {

    class ToyRobot
    {
    private:
        /* data */
        int X_;
        int Y_;
        std::string F_;
        bool Placed_;
    public:
        ToyRobot() noexcept;
        ~ToyRobot() = default;
        auto runCommands(std::string, std::ostream& outputStream = std::cout) -> void;
        auto executePlaceCommand(std::string) -> void;
        auto executeMoveCommand() -> bool;
        auto executeRotation(const std::string&) -> void;
        auto executeReportCommand(std::ostream& os = std::cout) -> void;
    };
    
}

#endif