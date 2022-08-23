#include "../toyrobotlib/include/toyrobot.hpp"
#include "../toyrobotlib/include/commandhandler.hpp"
#include "../toyrobotlib/include/config.hpp"

#define CATCH_CONFIG_MAIN
//#include <catch2/catch.hpp>
#include "catch.hpp"
#include <sstream>

TEST_CASE("Test stringTrim Function") {

	auto command_string = std::string{""};
	auto trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "");

	command_string = std::string{"  "};
	trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "");
	
	command_string = std::string{"PLACE 0,0,NORTH"};
	trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "PLACE 0,0,NORTH");

	command_string = std::string{"   PLACE 0,0,NORTH"};
	trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "PLACE 0,0,NORTH");

	command_string = std::string{"PLACE 0,0,NORTH   "};
	trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "PLACE 0,0,NORTH");

	command_string = std::string{"   PLACE 0,0,NORTH   "};
	trimmed_string = commandhandler::stringTrim(command_string);
	CHECK(trimmed_string == "PLACE 0,0,NORTH");
}

TEST_CASE("Test getCommandName Function") {

	auto command_string = std::string{""};
	auto command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "");

	command_string = std::string{"PLACE 0,0,NORTH"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "PLACE");

	command_string = std::string{"PLACE0,0,NORTH"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "PLACE0,0,NORTH");

	command_string = std::string{"PLACE0, 0,NORTH"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "PLACE0,");

	command_string = std::string{"PLACE0,0, NORTH"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "PLACE0,0,");

	command_string = std::string{"PLACE    0,0, NORTH"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "PLACE");

	command_string = std::string{"MOVE"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "MOVE");

	command_string = std::string{"LEFT"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "LEFT");

	command_string = std::string{"RIGHT"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "RIGHT");

	command_string = std::string{"REPORT"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "REPORT");

	command_string = std::string{"JUMP"};
	command_name = commandhandler::getCommandName(command_string);
	CHECK(command_name == "JUMP");
}

TEST_CASE("Test isValidCommandName Function") {

	auto command_name = std::string{""};
	CHECK(commandhandler::isValidCommandName(command_name) == false);

	command_name = std::string{"JUMP"};
	CHECK(commandhandler::isValidCommandName(command_name) == false);

	command_name = std::string{"1234"};
	CHECK(commandhandler::isValidCommandName(command_name) == false);

	command_name = std::string{"PLACE 0,0,NORTH"};
	CHECK(commandhandler::isValidCommandName(command_name) == false);

	command_name = std::string{"PLACE"};
	CHECK(commandhandler::isValidCommandName(command_name) == true);

	command_name = std::string{"MOVE"};
	CHECK(commandhandler::isValidCommandName(command_name) == true);

	command_name = std::string{"LEFT"};
	CHECK(commandhandler::isValidCommandName(command_name) == true);

	command_name = std::string{"RIGHT"};
	CHECK(commandhandler::isValidCommandName(command_name) == true);

	command_name = std::string{"REPORT"};
	CHECK(commandhandler::isValidCommandName(command_name) == true);
}

TEST_CASE("Test isValidPositionArgument Function") {

	CHECK(commandhandler::isValidPositionArgument("", 0, 5) == false);
	CHECK(commandhandler::isValidPositionArgument("ABC", 0, 5) == false);
	CHECK(commandhandler::isValidPositionArgument("-1", 0, 5) == false);
	CHECK(commandhandler::isValidPositionArgument("6", 0, 5) == false);
	CHECK(commandhandler::isValidPositionArgument("0", 0, 5) == true);
	CHECK(commandhandler::isValidPositionArgument("5", 0, 5) == true);
	CHECK(commandhandler::isValidPositionArgument("3", 0, 5) == true);
}

TEST_CASE("Test isValidPlaceCommandArgument Function") {
	REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

	CHECK(commandhandler::isValidPlaceCommandArgument("") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("MOVE") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("LEFT") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("RIGHT") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("REPORT") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("place") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("place 0,0,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE -1,0,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 6,0,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,-1,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,6,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE -1,-1,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 6,6,NORTH") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,NORTHWEST") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE   0,0,NORTHWEST") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,  0,NORTHWEST") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,  NORTHWEST") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,NORTHWEST,0") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE $,#,NORTHWEST") == false);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,$$$####,$%") == false);

	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,NORTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 2,3,NORTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 5,0,NORTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,5,NORTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 5,5,NORTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,EAST") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,SOUTH") == true);
	CHECK(commandhandler::isValidPlaceCommandArgument("PLACE 0,0,WEST") == true);

}

TEST_CASE("Test isMoveSafe Function") {
	REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

	CHECK(commandhandler::isMoveSafe(-1, 0) == false);
	CHECK(commandhandler::isMoveSafe(0, -1) == false);
	CHECK(commandhandler::isMoveSafe(-1, -1) == false);
	CHECK(commandhandler::isMoveSafe(6, 0) == false);
	CHECK(commandhandler::isMoveSafe(0, 6) == false);
	CHECK(commandhandler::isMoveSafe(6, 6) == false);

	CHECK(commandhandler::isMoveSafe(0, 0) == true);
	CHECK(commandhandler::isMoveSafe(5, 0) == true);
	CHECK(commandhandler::isMoveSafe(0, 5) == true);
	CHECK(commandhandler::isMoveSafe(5, 5) == true);
	CHECK(commandhandler::isMoveSafe(2, 3) == true);

}