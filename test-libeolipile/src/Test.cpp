
#include "Test.h"
#include "Engine.h"
#include "EngineWorld.h"

int main() {
	Engine engineTest = Engine(640, 480, 60, new std::string("Engine test"));

	engineTest.loadWindow();
	engineTest.startLoop();

	return 0;
}