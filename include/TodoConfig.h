#pragma once
#include <string>
class TodoConfig {
public:
	TodoConfig();
	~TodoConfig();

	void processConfig(std::string _configContents);
	std::string writeConfig();

	void setToDoFilePath(std::string _filePath);
	std::string getToDoFilePath();
private:
	std::string m_toDoFilePath;
};

