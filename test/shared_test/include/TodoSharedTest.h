#pragma once
#include "BaseTest.h"
#include "Todo.h"

class TodoSharedTest : public BaseTest {
public:
	TodoSharedTest();
	~TodoSharedTest();

	virtual void runTests();

	void todoReadTest();
	void todoWriteTest();
private:
	Todo testTodo;
};
