#include "TodoTest.h"
#include "DataTypes.h"

TodoTest::TodoTest(){
	
}

TodoTest::~TodoTest(){

}

void TodoTest::runTests(){
	displayResults();
}

void TodoTest::displayResults(){
	printf("Passed %i/%i tests!\n", passes, testsRun);
}
