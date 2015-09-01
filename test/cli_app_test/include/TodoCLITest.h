#pragma once
#include "BaseTest.h"

class TodoCLITestWrapper;

class TodoCLITest : public BaseTest {
public:
	TodoCLITest();
	~TodoCLITest();

	virtual void runTests();
private:
	TodoCLITestWrapper* m_toDoTestEngine;

	void refreshEngine();

	void testAddingItem();
	void testAddingCategory();
	void testAddingLabel();
	void testRemovingItemByIndex();
	void testRemovingItemByPop();
	void testRemovingAllItems();
	void testRemovingAllCompletedItems();
	void testRemovingCategoryByID();
	void testRemovingLabelByID();

	void testSettingItemCategory();
	void testMarkingItemAsCompleted();
	void testAppendingLabelToItem();
	void testRemovingLabelFromItem();
};
