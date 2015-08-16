#pragma once
#include <string>
#include <forward_list>

struct ToDoItemInfo {
	std::string name;
	std::string description;
};

class ToDoItem {
public:
	ToDoItemInfo toDoItemInfo;
	inline int getID() const {
		return id;
	}
	inline int getCategoryID() const {
		return categoryID;
	}
	inline bool getCompleted() const {
		return completed;
	}
	inline bool hasLabels() const {
		return !labelIDs.empty();
	}
	inline std::forward_list<int>::iterator labelsBegin(){
		return labelIDs.begin();
	}
	inline const std::forward_list<int>::const_iterator clabelsBegin() const{
		return labelIDs.cbegin();
	}
	inline std::forward_list<int>::iterator labelsEnd(){
		return labelIDs.end();
	}
	inline const std::forward_list<int>::const_iterator clabelsEnd() const{
		return labelIDs.cend();
	}
	inline void setID(int _id){
		id = _id;
	}
	inline void setCategoryID(int _categoryID){
		categoryID = _categoryID;
	}
	inline void setCompleted(bool _completed){
		completed = _completed;
	}
	inline void addLabelID(int _labelID){
		labelIDs.insert_after(labelIDs.before_begin(), _labelID);
	}
	inline void removeLabelID(int _labelID){
		std::forward_list<int>::iterator prevItr = labelIDs.before_begin();
		for (std::forward_list<int>::iterator labelsItr = labelIDs.begin(); labelsItr != labelIDs.end(); labelsItr++){
			if (*labelsItr == _labelID){
				labelIDs.erase_after(prevItr);
				return;
			}
			prevItr = labelsItr;
		}
	}
private:
	int id;
	int categoryID;
	bool completed;
	std::forward_list<int> labelIDs;
};

struct ToDoCategory {
	std::string name;
	int id;
};

struct ToDoLabel {
	std::string name;
	int color;
	int id;
};

enum LabelColor : unsigned int {
	WHITE = 0,
	GREEN = 1,
	MAGENTA = 2,
	YELLOW = 3,
	RED = 4,
	BLUE = 5,
	CYAN = 6,
	TEAL = 7,
	CRIMSON = 8
};
