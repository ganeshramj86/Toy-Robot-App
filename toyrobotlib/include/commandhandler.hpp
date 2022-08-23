#ifndef COMMANDHANDLER_HPP_INCLUDED
#define COMMANDHANDLER_HPP_INCLUDED

#include <iostream>

namespace commandhandler {
    auto stringTrim(std::string const&) -> std::string;
    auto isValidCommandName(std::string const&) -> bool;
    auto getCommandName(std::string const&) -> std::string;
    auto isValidPositionArgument(std::string const&, const int&, const int&) -> bool;
    auto isValidPlaceCommandArgument(std::string) -> bool;
    auto isMoveSafe(const int&, const int&) -> bool;
}

#endif