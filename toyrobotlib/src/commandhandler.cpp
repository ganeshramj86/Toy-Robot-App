#include "../include/commandhandler.hpp"
#include "../include/config.hpp"
#include<iostream>
#include <unordered_map>
#include <string.h>

namespace commandhandler {

    // This function is used to trim the whitespace (both front and back) in command string
    auto stringTrim(std::string str) -> std::string {
        auto str_begin = str.find_first_not_of(" ");
        if (str_begin == std::string::npos) {
            return "";
        }
        auto str_end = str.find_last_not_of(" \r\n");
        auto str_len = str_end - str_begin + 1;

        return (str.substr(str_begin, str_len));
    }

    // This functions is used to retieve the command name from command string
    auto getCommandName(std::string const& command_str) -> std::string {
        auto find_space = command_str.find(" ");
        std::string command_name;
        if (find_space != std::string::npos) {
            command_name = command_str.substr(0, find_space);
        }
        else {
            command_name = command_str;
        }

        return command_name;
    }

    // This function is used to check if command name is a valid command
    auto isValidCommandName(std::string const& command_str) -> bool {
        if (config::kValidCommandsEnumMap.find(command_str) != config::kValidCommandsEnumMap.end()) {
            return true;
        }
        return false;
    }

    // This function is used to check if the place command has valid X and Y positional arguments provided
    auto isValidPositionArgument(std::string const& args, const int &lower_limit, const int &upper_limit) -> bool {
        try {
            auto pos = std::stoi(args);
            if ((pos >= lower_limit) && (pos <= upper_limit)) {
                return true;
            }
            else {
                return false;
            }
        }
        catch(std::invalid_argument const& ex ) {
            return false;
        }
        catch(std::out_of_range const& ex) {
            return false;
        }
    }

    // This function is used to check if the place command has valid arguments provided
    auto isValidPlaceCommandArgument(std::string place_command_str) -> bool {

        if (place_command_str.empty()) {
            return false;
        }
        
        char* place_cmd_str = &place_command_str[0];
        char *token = strtok(place_cmd_str, " ");

        std::string command_name(token);
        if (command_name != "PLACE") {
            return false;
        }

        for (int args_parsed = 0; args_parsed < config::kNumPlaceCommandArgs; args_parsed++) {
            token = strtok(NULL, ",");
            std::string argument{""};

            if (token != NULL) {
                argument = token;
            }

            switch (args_parsed)
            {
            case config::kPositionX:
                if (!isValidPositionArgument(argument, config::kXWestLimit, config::kXEastLimit)) {
                    return false;
                }
                break;
            case config::kPositionY:
                if (!isValidPositionArgument(argument, config::kYSouthLimit, config::kYNorthLimit)) {
                    return false;
                }
                break;
            case config::kDirection:
                if (config::kValidDirectionsEnumMap.find(argument) == config::kValidDirectionsEnumMap.cend()) {
                    return false;
                }
                break;
            default:
                break;
            }
        }

        token = strtok(NULL, ",");

        if (token != NULL) {
            return false;
        }

        return true;
    }

    // This function is used to check if the position resulting from move command is safe to allow
    auto isMoveSafe(const int& x_pos, const int& y_pos) -> bool {
        if ((x_pos >= config::kXWestLimit) && 
            (x_pos <= config::kXEastLimit) &&
            (y_pos >= config::kYSouthLimit) &&
            (y_pos <= config::kYNorthLimit)) {
                return true;
        }
        return false;
    }
}