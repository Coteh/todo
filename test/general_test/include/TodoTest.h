#pragma once

class TodoTest {
public:
	TodoTest();
	~TodoTest();

	void runTests();
	void displayResults();
private:
	int testsRun, passes;
};
