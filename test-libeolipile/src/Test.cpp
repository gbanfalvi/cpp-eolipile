
#include <string>
#include "Test.h"
#include "GameEngine.hpp"
#include "EngineWorld.hpp"

int main() {
	GameEngine engineTest = GameEngine(640, 480, 60, new std::string("Engine test"));

	engineTest.loadWindow();
	engineTest.startLoop();

	return 0;
}