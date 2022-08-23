#include "../include/config.hpp"

namespace config {
    // The total number of place command arguments that we extract from input file
    extern const int kNumPlaceCommandArgs = 3;
    // The minimum X position limit that we allow for safe move
    extern const int kXWestLimit = 0;
    // The maximum X position limit that we allow for safe move
    extern const int kXEastLimit = 5;
    // The minimum Y position limit that we allow for safe move
    extern const int kYSouthLimit = 0;
    // The maximum Y position limit that we allow for safe move
    extern const int kYNorthLimit = 5;
    // The amount of degree that we allow robot to rotate left
    extern const int kLeftRotate = -90;
    // The amount of degree that we allow robot to rotate right
    extern const int kRightRotate = 90;
    // The maximum amount of degree for one complete rotation that we use to limit rotations beyond it
    extern const int kFullRotation = 360;

    // The map to search for valid commands in input file and for enumeration in switch statement
    extern const std::map<std::string, ValidCommands> kValidCommandsEnumMap = {
        {"PLACE", ValidCommands::kPlace},
        {"MOVE", ValidCommands::kMove},
        {"LEFT", ValidCommands::kLeft},
        {"RIGHT", ValidCommands::kRight},
        {"REPORT", ValidCommands::kReport},
    };

    // The map to search for valid directions in commands, to set direction after rotation 
    // and for enumeration in switch statement
    extern const std::map<std::string, ValidDirections> kValidDirectionsEnumMap = {
        {"NORTH", ValidDirections::kNorth},
        {"EAST", ValidDirections::kEast},
        {"SOUTH", ValidDirections::kSouth},
        {"WEST", ValidDirections::kWest},
    };

    // The map to convert direction to degrees that we use to compute new degrees for rotation
    extern const std::map<std::string, int> kDirectionToDegree = {
        {"NORTH", 0},
        {"EAST", 90},
        {"SOUTH", 180},
        {"WEST", 270},
    };

    // The map to convert degrees to direction that we use to set new direction for a LEFT or RIGHT command
    extern const std::map<int, std::string> kDegreeToDirection = {
        {0, "NORTH"},
        {90, "EAST"},
        {180, "SOUTH"},
        {270, "WEST"},
    };

    /* Error Messages */
    // The error message to be displayed when an invalid command name is given
    extern const std::string kInvalidCommandNameErrorMsg = "Invalid Command Name. Valid Commands: PLACE, MOVE, LEFT, RIGHT, REPORT!";
    // The error message to be displayed when a PLACE command is given with incorrect arguments
    extern const std::string kInvalidPlaceCommandErrorMsg = "Place Command Rejected due to arguments mismatch or off-table position given!";
    // The error message to be displayed when a MOVE command is given before a first PLACE command
    extern const std::string kInvalidMoveCommandErrorMsg = "Move Command Rejected due to first Place command not executed!";
    // The error message to be displayed when a LEFT command is given before a first PLACE command
    extern const std::string kInvalidLeftCommandErrorMsg = "Left Command Rejected due to first Place command not executed!";
    // The error message to be displayed when a RIGHT command is given before a first PLACE command
    extern const std::string kInvalidRightCommandErrorMsg = "Right Command Rejected due to first Place command not executed!";
    // The error message to be displayed when a REPORT command is given before a first PLACE command
    extern const std::string kInvalidReportCommandErrorMsg = "Report Command Rejected due to first Place command not executed!";
    // The error message to be displayed when a MOVE command leads to robot falling off the table
    extern const std::string kUnsafeMoveCommandErrorMsg = "Move Command Rejected as it will cause robot to fall off table!";
    // The error message to be displayed when the input file name is unable to be opened
    extern const std::string kInvalidFileNameErrorMsg = "Error opening the file! Check the file or file name!";
    // The error message to be displayed when a command name is empty
    extern const std::string kEmptyCommandErrorMsg = "Empty Command Provided. Valid Commands: PLACE, MOVE, LEFT, RIGHT, REPORT!";
    // The error message to be displayed when an input file is empty
    extern const std::string kEmptyFileErrorMsg = "Empty File! Nothing to do!";
}