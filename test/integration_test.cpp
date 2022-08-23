#include "../toyrobotlib/include/toyrobot.hpp"
#include "../toyrobotlib/include/commandhandler.hpp"
#include "../toyrobotlib/include/config.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream>


TEST_CASE("Test place command with leading and trailing spaces to check string trim") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test1";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Output: 0, 0, EAST");
}

TEST_CASE("Test invalid command name") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test2";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Invalid Command Name. Valid Commands: PLACE, MOVE, LEFT, RIGHT, REPORT!");
}

TEST_CASE("Test invalid place command with argument mismatch") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test3";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Place Command Rejected due to arguments mismatch or off-table position given!");
}

TEST_CASE("Test invalid place command with off-table location") {

    REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test4";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Place Command Rejected due to arguments mismatch or off-table position given!");
}

TEST_CASE("Test Move command without place command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test5";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Move Command Rejected due to first Place command not executed!");
}

TEST_CASE("Test Left command without place command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test6";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Left Command Rejected due to first Place command not executed!");
}

TEST_CASE("Test Right command without place command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test7";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Right Command Rejected due to first Place command not executed!");
}

TEST_CASE("Test Report command without place command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test8";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Report Command Rejected due to first Place command not executed!");
}

TEST_CASE("Test with unsafe Move command") {

    REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test9";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Move Command Rejected as it will cause robot to fall off table!");
}

TEST_CASE("Test with invalide file name") {

    REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

    auto robot1 = iress::ToyRobot();
    std::string input = "my_input_file";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Error opening the file! Check the file or file name!");
}

TEST_CASE("Test with place, move, report command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test10";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Output: 0, 1, NORTH");
}

TEST_CASE("Test with place, left, report command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test11";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Output: 0, 0, WEST");
}

TEST_CASE("Test with place, right, report command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test12";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Output: 0, 0, EAST");
}

TEST_CASE("Test with multiple place command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test13";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Output: 2, 3, SOUTH");
}

TEST_CASE("Test with empty file") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test14";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Empty File! Nothing to do!");
}

TEST_CASE("Test file with an empty command") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test15";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Empty Command Provided. Valid Commands: PLACE, MOVE, LEFT, RIGHT, REPORT!");
}

TEST_CASE("Test file with an empty command in the middle") {
    auto robot1 = iress::ToyRobot();
    std::string input = "input_integration_test16";
    std::string path = "./inputs/" + input + ".txt";
    auto oss = std::ostringstream{};
    oss << "";

    robot1.runCommands(path, oss);
    CHECK(oss.str() == "Empty Command Provided. Valid Commands: PLACE, MOVE, LEFT, RIGHT, REPORT!Output: 0, 0, NORTH");
}

