#include "../include/toyrobot.hpp"
#include "../include/commandhandler.hpp"
#include "../include/config.hpp"

#include <sstream>
#include <fstream>
#include <string.h>

namespace iress {

    //default Constructor
    iress::ToyRobot::ToyRobot() noexcept {
        X_ = 0;
        Y_ = 0;
        F_ = "NORTH";
        Placed_ = false;
    }

    // This function is used to execute PLACE command
    auto iress::ToyRobot::executePlaceCommand(std::string place_command) -> void {
        char* place_command_str = &place_command[0];
        std::string place_command_params[config::kNumPlaceCommandArgs];
        int index = 0;
        // First split and remove the command name
        char *token = strtok(place_command_str, " ");
        // split the place command arguments by comma
        token = strtok(NULL, ",");
        while (token != NULL)
        {
            std::string param(token);
            place_command_params[index++] = param;
            token = strtok(NULL, ",");
        }
        // set the private data using the vector
        X_ = std::stoi(place_command_params[0]);
        Y_ = std::stoi(place_command_params[1]);
        F_ = place_command_params[2];

        if (Placed_ == false) {
            Placed_ = true;
        }
    }

    // This function is used to execute LEFT and RIGHT command based on rotation_type
    auto iress::ToyRobot::executeRotation(const std::string& rotation_type) -> void {
        auto current_degree = config::kDirectionToDegree.at(F_);
        int rotation_angle;
        if (rotation_type == "LEFT") {
            rotation_angle = config::kLeftRotate;
        }
        else if (rotation_type == "RIGHT") {
            rotation_angle = config::kRightRotate;
        }

        auto new_degree = current_degree + rotation_angle;
        if (new_degree < 0) {
            new_degree += config::kFullRotation;
        }
        new_degree %= config::kFullRotation;
        F_ = config::kDegreeToDirection.at(new_degree);
    }

    // This function is used to execute REPORT command
    auto iress::ToyRobot::executeReportCommand(std::ostream& os) -> void {
        os << "Output: " << X_ << ", " << Y_ << ", " << F_;
        std::cout << std::endl;
    }

    // This function is used to execute MOVE command
    auto iress::ToyRobot::executeMoveCommand() -> bool {
        auto current_direction_enum = config::kValidDirectionsEnumMap.at(F_);
        auto current_x_pos = X_;
        auto current_y_pos = Y_;

        switch (current_direction_enum)
        {
        case config::kNorth:
            current_y_pos += 1;
            break;
        case config::kEast:
            current_x_pos += 1;
            break;
        case config::kSouth:
            current_y_pos -= 1;
            break;
        case config::kWest:
            current_x_pos -= 1;
            break;
        default:
            break;
        }

        // check X position
        if (commandhandler::isMoveSafe(current_x_pos, current_y_pos)) {
            X_ = current_x_pos;
            Y_ = current_y_pos;

            return true;
        }
        else {
            return false;
        }

    }

    // This function reads the input line by line and execute all the commands found
    auto iress::ToyRobot::runCommands(std::string const& input, std::ostream& outputStream) -> void {
        std::fstream newFile;
        newFile.open(input);

         if (newFile.is_open()) {
            // check if file is empty
            if (newFile.peek() == std::fstream::traits_type::eof()) {
                outputStream << config::kEmptyFileErrorMsg;
                std::cout << std::endl;
            }
            std::string command;
            while(getline(newFile, command)) {
                
                // checking if given command in a line is empty
                if ((command.empty()) || (command == "\r")) {
                    outputStream << config::kEmptyCommandErrorMsg;
                    std::cout << std::endl;
                    continue;
                }

                auto command_trim = commandhandler::stringTrim(command);
                auto command_name = commandhandler::getCommandName(command_trim);

                if (commandhandler::isValidCommandName(command_name)) {
                    switch (config::kValidCommandsEnumMap.at(command_name))
                    {
                    case config::kPlace:
                        if (commandhandler::isValidPlaceCommandArgument(command_trim)) {
                            executePlaceCommand(command_trim);
                        }
                        else {
                            outputStream << config::kInvalidPlaceCommandErrorMsg;
                            std::cout << std::endl;
                        }
                        break;
                    case config::kMove:
                        if (Placed_) {
                            if (!executeMoveCommand()) {
                                outputStream << config::kUnsafeMoveCommandErrorMsg;
                                std::cout << std::endl;
                            }
                        }
                        else {
                            outputStream << config::kInvalidMoveCommandErrorMsg;
                            std::cout << std::endl;
                        }
                        break;
                    case config::kLeft:
                        if (Placed_) {
                            executeRotation("LEFT");
                        }
                        else {
                            outputStream << config::kInvalidLeftCommandErrorMsg;
                            std::cout << std::endl;
                        }
                        break;
                    case config::kRight:
                        if (Placed_) {
                            executeRotation("RIGHT");
                        }
                        else {
                            outputStream << config::kInvalidRightCommandErrorMsg;
                            std::cout << std::endl;
                        }
                        break;
                    case config::kReport:
                        if (Placed_) {
                            executeReportCommand(outputStream);
                        }
                        else {
                            outputStream << config::kInvalidReportCommandErrorMsg;
                            std::cout << std::endl;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else {
                    outputStream << config::kInvalidCommandNameErrorMsg;
                    std::cout << std::endl;
                }
            }
        }
        else {
            outputStream << config::kInvalidFileNameErrorMsg;
            std::cout << std::endl;
        }
    }
}