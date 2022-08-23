#include "../toyrobotlib/include/toyrobot.hpp"
#include "../toyrobotlib/include/commandhandler.hpp"
#include "../toyrobotlib/include/config.hpp"

#define CATCH_CONFIG_MAIN
//#include <catch2/catch.hpp>
#include "catch.hpp"
#include <sstream>

TEST_CASE("Test executeReportCommand Function") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");
}

TEST_CASE("Test executePlaceCommand Function") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 0,0,NORTH");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 0,5,EAST");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 5, EAST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,0,SOUTH");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 0, SOUTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,5,WEST");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 5, WEST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 2,4,NORTH");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 2, 4, NORTH");
}

TEST_CASE("Test executeRotation Function - Left Rotation") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");

	oss = std::ostringstream{};
	robot1.executeRotation("LEFT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, WEST");

	oss = std::ostringstream{};
	robot1.executeRotation("LEFT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, SOUTH");

	oss = std::ostringstream{};
	robot1.executeRotation("LEFT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, EAST");

	oss = std::ostringstream{};
	robot1.executeRotation("LEFT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");
}

TEST_CASE("Test executeRotation Function - Right Rotation") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");

	oss = std::ostringstream{};
	robot1.executeRotation("RIGHT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, EAST");

	oss = std::ostringstream{};
	robot1.executeRotation("RIGHT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, SOUTH");

	oss = std::ostringstream{};
	robot1.executeRotation("RIGHT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, WEST");

	oss = std::ostringstream{};
	robot1.executeRotation("RIGHT");
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, NORTH");
}

TEST_CASE("Test executeMoveCommand Function - Placed at South-West Corner Unsuccessful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

	robot1.executePlaceCommand("PLACE 0,0,SOUTH");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, SOUTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 0,0,WEST");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 0, WEST");
}

TEST_CASE("Test executeMoveCommand Function - Placed at South-West Corner Successful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	REQUIRE(config::kXWestLimit == 0);
	REQUIRE(config::kXEastLimit == 5);
	REQUIRE(config::kYSouthLimit == 0);
	REQUIRE(config::kYNorthLimit == 5);

	robot1.executePlaceCommand("PLACE 0,0,SOUTH");
	robot1.executeRotation("LEFT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 1, 0, EAST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 0,0,WEST");
	robot1.executeRotation("RIGHT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 1, NORTH");
}

TEST_CASE("Test executeMoveCommand Function - Placed at South-East Corner Unsuccessful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 5,0,SOUTH");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 0, SOUTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,0,EAST");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 0, EAST");
}

TEST_CASE("Test executeMoveCommand Function - Placed at South-East Corner Successful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 5,0,SOUTH");
	robot1.executeRotation("RIGHT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 4, 0, WEST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,0,EAST");
	robot1.executeRotation("LEFT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 1, NORTH");
}

TEST_CASE("Test executeMoveCommand Function - Placed at North-East Corner Unsuccessful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 5,5,NORTH");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 5, NORTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,5,EAST");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 5, EAST");
}

TEST_CASE("Test executeMoveCommand Function - Placed at North-East Corner Successful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 5,5,NORTH");
	robot1.executeRotation("LEFT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 4, 5, WEST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 5,5,EAST");
	robot1.executeRotation("RIGHT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 5, 4, SOUTH");
}

TEST_CASE("Test executeMoveCommand Function - Placed at North-West Corner Unsuccessful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 0,5,NORTH");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 5, NORTH");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 0,5,WEST");
	CHECK(robot1.executeMoveCommand() == false);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 5, WEST");
}

TEST_CASE("Test executeMoveCommand Function - Placed at North-West Corner Successful Moves") {
	auto robot1 = iress::ToyRobot();
	auto oss = std::ostringstream{};

	robot1.executePlaceCommand("PLACE 0,5,NORTH");
	robot1.executeRotation("RIGHT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 1, 5, EAST");

	oss = std::ostringstream{};
	robot1.executePlaceCommand("PLACE 0,5,WEST");
	robot1.executeRotation("LEFT");
	CHECK(robot1.executeMoveCommand() == true);
	robot1.executeReportCommand(oss);
	CHECK(oss.str() == "Output: 0, 4, SOUTH");
}