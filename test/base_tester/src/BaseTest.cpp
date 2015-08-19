#include "BaseTest.h"
#include <stdio.h>

BaseTest::BaseTest(){

}

BaseTest::~BaseTest(){

}

void BaseTest::runTests(){
	displayResults();
}

void BaseTest::displayResults(){
	int fails = testsRun - passes;
	printf("Passed %i/%i tests!\n", passes, testsRun);
	if (fails)
		printf("Failed %i %s!\n", fails, (fails == 1) ? "test" : "tests");
}

void BaseTest::registerTest(std::string _testName){
	testsRun++; //increase tests amount by one
	//Print out the name of the test
	printf("-----------------------\n");
	printf("Test: %s\n", _testName.c_str());
	printf("-----------------------\n");
}

void BaseTest::registerPass(){
	passes++; //increment passes count
	printf("Test passed!\n");
}

void BaseTest::registerFailure(){
	printf("Test failed!\n");
}

void BaseTest::registerError(){
	printf("An error occurred!\n");
}