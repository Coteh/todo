#pragma once
#include <string>
class TodoConfig {
public:
	TodoConfig();
	~TodoConfig();

	void loadConfigFile();
	void saveConfigFile();
	void createNewConfigFile();

	void setToDoFilePath(std::string _filePath);
	std::string getToDoFilePath();
private:
	std::string m_programFilePath;
	std::string m_toDoFilePath;
};

