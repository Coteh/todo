#include "TodoPrinter.h"
#include "Todo.h"
#include "DataTypes.h"

#ifdef _WIN32
const WORD TodoPrinter::colors[] = {
	0x0F, 0x02, 0x0D, 0x0E, 0x0C
};
#endif

TodoPrinter::TodoPrinter(Todo* _todoEngine) {
	m_toDoEngine = _todoEngine;

#ifdef _WIN32
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &csbi);
#endif
}

TodoPrinter::TodoPrinter(){

}

TodoPrinter::~TodoPrinter() {
}

void TodoPrinter::printToDos(){
	printToDos(-1, PrintShowType::ALL, false);
}

void TodoPrinter::printToDos(bool _verbose){
	printToDos(-1, PrintShowType::ALL, _verbose);
}

void TodoPrinter::printToDos(int _categoryID){
	printToDos(_categoryID, PrintShowType::ALL, false);
}

void TodoPrinter::printToDos(int _categoryID, bool _verbose){
	printToDos(_categoryID, PrintShowType::ALL, _verbose);
}

void TodoPrinter::printToDos(PrintShowType _showType, bool _verbose){
	printToDos(-1, _showType, _verbose);
}

void TodoPrinter::printToDos(int _categoryID, PrintShowType _showType, bool _verbose){
	//size_t todoSize = m_toDoEngine->getTodoCount();
	ToDoCategory category;
	if (_categoryID >= 0){
		try{
			category = m_toDoEngine->getCategory(_categoryID);
		} catch (int e) {
			if (e == -1){
				printf("ERROR: Could not get category of id %i\n", _categoryID);
			} else{
				printf("ERROR: Unknown error getting category.\n");
			}
			return;
		}
	}
	std::pair<std::vector<ToDoItem>::iterator, std::vector<ToDoItem>::iterator> toDoItrPair = m_toDoEngine->getItemIterator();
	std::vector<ToDoItem>::iterator beginItr = toDoItrPair.first;
	std::vector<ToDoItem>::iterator endItr = toDoItrPair.second;
	if (_categoryID >= 0){
		printf("========== Things to Do in Category: %s ==========\n", category.name.c_str());
	} else{
		printf("======= Things to Do ==========\n");
	}
	int i = 0, shownAmt = 0;
	for (std::vector<ToDoItem>::iterator toDoItr = beginItr; toDoItr != endItr; toDoItr++){
		i++;
		if ((_categoryID >= 0 && toDoItr->categoryID != category.id) || 
			(_showType == PrintShowType::NONE || ((_showType != PrintShowType::ALL)
				&& ((toDoItr->completed && _showType != PrintShowType::COMPLETE) || 
				(!toDoItr->completed && _showType != PrintShowType::INCOMPLETE))))) continue;
		if (shownAmt > 0 && toDoItr != endItr) printf("---------------------------\n");
		printf("%i. ", i);
		printToDoItem(*toDoItr, _verbose);
		shownAmt++;
	}
	if (_categoryID >= 0){
		printf("==================================================\n");
	} else{
		printf("===============================\n");
	}
}

void TodoPrinter::printToDoItem(const ToDoItem& _toDoItem){
	printToDoItem(_toDoItem, false);
}

void TodoPrinter::printToDoItem(const ToDoItem& _toDoItem, bool _verbose){
	ToDoLabel label;
	bool hasLabel = true;
	try{
		label = m_toDoEngine->getLabel(_toDoItem.labelID);
	} catch (int e){
		label.color = -1; //give it fallback color value of -1
		hasLabel = false;
	}
	char *nameTag = "", *descriptionTag = "";
	if (_verbose){
		nameTag = "Name: ";
		descriptionTag = "Description: ";
	}
	printf("[%s] %s%s\n", (_toDoItem.completed) ? "X" : " ", nameTag, _toDoItem.name.c_str());
	printf("%s%s\n", descriptionTag, _toDoItem.description.c_str());
	if (_verbose){
		printf("Category ID: %i\n", _toDoItem.categoryID);
	}
	if (hasLabel){
		printf("Label: ");
#ifdef _WIN32
		beginPrintPaint(label.color);
#endif
		printf("%s\n", label.name.c_str());
#ifdef _WIN32
		endPrintPaint();
#endif
	}
}

void TodoPrinter::printCategories(){
	std::pair<std::vector<ToDoCategory>::iterator, std::vector<ToDoCategory>::iterator> cateItrPair = m_toDoEngine->getCategoryIterator();
	std::vector<ToDoCategory>::iterator beginItr = cateItrPair.first;
	std::vector<ToDoCategory>::iterator endItr = cateItrPair.second;
	printf("======== Categories ===========\n");
	for (std::vector<ToDoCategory>::iterator cateItr = beginItr; cateItr != endItr; cateItr++){
		printf("[ID: %i] %s\n", cateItr->id, cateItr->name.c_str());
	}
	printf("===============================\n");
}

void TodoPrinter::printLabels(){
	std::pair<std::vector<ToDoLabel>::iterator, std::vector<ToDoLabel>::iterator> labelItrPair = m_toDoEngine->getLabelIterator();
	std::vector<ToDoLabel>::iterator beginItr = labelItrPair.first;
	std::vector<ToDoLabel>::iterator endItr = labelItrPair.second;
	printf("======== Labels ===========\n");
	for (std::vector<ToDoLabel>::iterator labelItr = beginItr; labelItr != endItr; labelItr++){
#ifdef _WIN32
		beginPrintPaint(labelItr->color);
#endif
		printf("[ID: %i] %s\n", labelItr->id, labelItr->name.c_str());
#ifdef _WIN32
		endPrintPaint();
#endif
	}
	printf("===========================\n");
}

void TodoPrinter::printLabelColor(int _colorIndex, const char* _text){
#ifdef _WIN32
	beginPrintPaint(_colorIndex);
#endif
	printf("%s", _text);
#ifdef _WIN32
	endPrintPaint();
#endif
}

#ifdef _WIN32
void TodoPrinter::beginPrintPaint(int _colorIndex){
	if (_colorIndex >= 0)	SetConsoleTextAttribute(hstdout, colors[_colorIndex]);
}

void TodoPrinter::endPrintPaint(){
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}
#endif