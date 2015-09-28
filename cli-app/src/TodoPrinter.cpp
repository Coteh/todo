#include "TodoPrinter.h"
#include "Todo.h"
#include "DataTypes.h"

#ifdef _WIN32
const WORD TodoPrinter::colors[] = {
	0x0F, 0x02, 0x0D, 0x0E, 0x0C, 0x09, 0x0B, 0x03, 0x04
};
#else
const int TodoPrinter::colors[] = {
	39, 32, 35, 33, 31, 34, 36, 44, 41
};
#endif

TodoPrinter::TodoPrinter(Todo* _todo) {
	m_todo = _todo;

#ifdef _WIN32
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &csbi);
#endif

	init();
}

TodoPrinter::TodoPrinter(){
	init();
}

TodoPrinter::~TodoPrinter() {
}

void TodoPrinter::init(){
	nameTag = "Name: ";
	descriptionTag = "Description: ";
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
			category = m_todo->getCategoryByID(_categoryID);
		} catch (int e) {
			if (e == -1){
				printf("ERROR: Could not get category of id %i\n", _categoryID);
			} else{
				printf("ERROR: Unknown error getting category.\n");
			}
			return;
		}
	}
	std::vector<ToDoItem>::iterator beginItr = m_todo->itemsBegin();
	std::vector<ToDoItem>::iterator endItr = m_todo->itemsEnd();
	if (_categoryID >= 0){
		printf("========== Things to Do in Category: %s ==========\n", category.name.c_str());
	} else{
		printf("======= Things to Do ==========\n");
	}
	int i = 0, shownAmt = 0;
	for (std::vector<ToDoItem>::iterator toDoItr = beginItr; toDoItr != endItr; toDoItr++){
		i++;
		if ((_categoryID >= 0 && toDoItr->getCategoryID() != category.id) ||
			(_showType == PrintShowType::NONE || ((_showType != PrintShowType::ALL)
				&& ((toDoItr->getCompleted() && _showType != PrintShowType::COMPLETE) ||
				(!toDoItr->getCompleted() && _showType != PrintShowType::INCOMPLETE))))) continue;
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
	bool hasLabel = _toDoItem.hasLabels();
	printf("[%s] %s%s\n", (_toDoItem.getCompleted()) ? "X" : " ", (_verbose) ? nameTag.c_str() : "", _toDoItem.toDoItemInfo.name.c_str());
	printf("%s%s\n", (_verbose) ? descriptionTag.c_str() : "", _toDoItem.toDoItemInfo.description.c_str());
	if (_verbose){
		printf("Category ID: %i\n", _toDoItem.getCategoryID());
	}
	if (hasLabel){
		printf("Label(s): ");
		for (std::forward_list<int>::const_iterator labelItr = _toDoItem.clabelsBegin(); labelItr != _toDoItem.clabelsEnd(); ++labelItr){
			if (labelItr != _toDoItem.clabelsBegin()){
				printf(", ");
			}
			ToDoLabel label;
			try{
				label = m_todo->getLabelByID(*labelItr);
			} catch (int e){
				label.color = -1; //give it fallback color value of -1
			}
			beginPrintPaint(label.color);
			printf("%s", label.name.c_str());
			endPrintPaint();
		}
		printf("\n");
	}
}

void TodoPrinter::printCategories(){
	std::vector<ToDoCategory>::iterator beginItr = m_todo->categoriesBegin();
	std::vector<ToDoCategory>::iterator endItr = m_todo->categoriesEnd();
	printf("======== Categories ===========\n");
	for (std::vector<ToDoCategory>::iterator cateItr = beginItr; cateItr != endItr; cateItr++){
		printf("[ID: %i] %s\n", cateItr->id, cateItr->name.c_str());
	}
	printf("===============================\n");
}

void TodoPrinter::printLabels(){
	std::vector<ToDoLabel>::iterator beginItr = m_todo->labelsBegin();
	std::vector<ToDoLabel>::iterator endItr = m_todo->labelsEnd();
	printf("======== Labels ===========\n");
	for (std::vector<ToDoLabel>::iterator labelItr = beginItr; labelItr != endItr; labelItr++){
		beginPrintPaint(labelItr->color);
		printf("[ID: %i] %s\n", labelItr->id, labelItr->name.c_str());
		endPrintPaint();
	}
	printf("===========================\n");
}

void TodoPrinter::printLabelColor(int _colorIndex, const char* _text){
	beginPrintPaint(_colorIndex);
	printf("%s", _text);
	endPrintPaint();
}

void TodoPrinter::beginPrintPaint(int _colorIndex){
#ifdef _WIN32
	if (_colorIndex >= 0)	SetConsoleTextAttribute(hstdout, colors[_colorIndex]);
#else
	if (_colorIndex >= 0)	printf("\033[1;%im", colors[_colorIndex]);
#endif
}

void TodoPrinter::endPrintPaint(){
#ifdef _WIN32
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#else
	printf("\033[0m");
#endif
}
