#include "TodoSharedTest.h"
#include "DataTypes.h"

TodoSharedTest::TodoSharedTest(){

}

TodoSharedTest::~TodoSharedTest(){

}

void TodoSharedTest::runTests(){
	todoReadTest();
	todoWriteTest();
	displayResults();
}

void TodoSharedTest::todoReadTest(){
	registerTest("Reading todo items from JSON");
	try {
		testTodo.parseItems("\{\"todo\":\{\"id\":0,\"category_id\":0,\"name\":\"Test Item\",\"description\":\"This is a test item to see if reading is okay.\",\"completed\":false\}\}");
	} catch (int e) {
		registerFailure();
		return;
	}
	registerPass();
}

void TodoSharedTest::todoWriteTest(){
	registerTest("Writing todo items to JSON");
	try {
		std::string todoResult = testTodo.writeItems();
		printf("%s\n", todoResult.c_str());
	} catch (int e) {
		registerFailure();
		return;
	}
	registerPass();
}
