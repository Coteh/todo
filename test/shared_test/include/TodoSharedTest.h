#pragma once
#include "BaseTest.h"
#include "Todo.h"

class TodoSharedTest : public BaseTest {
public:
	TodoSharedTest();
	~TodoSharedTest();

	virtual void runTests();
private:
	Todo m_testTodo;

	void refreshTodo();

	void todoReadTest();
	void todoWriteTest();

	void addItemTest();
	void addItemAtIndexTest();
	void addCategoryTest();
	void addLabelTest();

	void itemModificationTest();
	void testGetters();

	void removeItemTest();
	void removeCategoryTest();
	void removeLabelTest();
};
