#include "TodoCLITest.h"
#include "TodoPrinterTest.h"
#include <stdio.h>

TodoCLITest cliTest;
TodoPrinterTest printerTest;

int main(int argc, char const *argv[]){
	cliTest.runTests();
	printerTest.runTests();
	getchar();
}
