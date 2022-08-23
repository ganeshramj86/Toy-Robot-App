#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <string>
#include <map>

namespace config {
    extern const int kNumPlaceCommandArgs;
    extern const int kXWestLimit;
    extern const int kXEastLimit;
    extern const int kYSouthLimit;
    extern const int kYNorthLimit;
    extern const int kLeftRotate;
    extern const int kRightRotate;
    extern const int kFullRotation;

    enum PlaceCommandArgs {
        kPositionX = 0,
        kPositionY,
        kDirection
    };

    enum ValidCommands {
        kPlace = 0,
        kMove,
        kLeft,
        kRight,
        kReport
    };

    enum ValidDirections {
        kNorth = 0,
        kEast,
        kSouth,
        kWest
    };

    extern const std::map<std::string, ValidCommands> kValidCommandsEnumMap;

    extern const std::map<std::string, ValidDirections> kValidDirectionsEnumMap;

    extern const std::map<std::string, int> kDirectionToDegree;

    extern const std::map<int, std::string> kDegreeToDirection;

    /* Error Messages */
    extern const std::string kInvalidCommandNameErrorMsg;
    extern const std::string kInvalidPlaceCommandErrorMsg;
    extern const std::string kInvalidMoveCommandErrorMsg;
    extern const std::string kInvalidLeftCommandErrorMsg;
    extern const std::string kInvalidRightCommandErrorMsg;
    extern const std::string kInvalidReportCommandErrorMsg;
    extern const std::string kUnsafeMoveCommandErrorMsg;
    extern const std::string kInvalidFileNameErrorMsg;
    extern const std::string kEmptyCommandErrorMsg;
    extern const std::string kEmptyFileErrorMsg;

}

#endif