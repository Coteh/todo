#ifndef BASE_TEST_H
#define BASE_TEST_H

#include <string>

class BaseTest {
public:
	BaseTest();
	~BaseTest();

	virtual void runTests();
	void displayResults();
	void registerTest(std::string _testName);
	void registerPass();
	void registerFailure();
	void registerError();
	void registerError(std::string _cusErrMsg);
	void sayMessage(std::string _message);
protected:
	int testsRun, passes; //failures will be calculated as testsRun - passes
};

#endif /* end of include guard: BASE_TEST_H */
