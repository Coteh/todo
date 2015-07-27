#include "TodoConfig.h"
#include "FileIO.h"
#include "Helpers.h" //getProjectDirectory

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#define CONFIG_FILENAME "config.json"

TodoConfig::TodoConfig() {
	m_programFilePath = getProjectDirectory();
}

TodoConfig::~TodoConfig() {
}

void TodoConfig::loadConfigFile(){
	std::string fileContents = FileIO::readFile(m_programFilePath + FOLDER_DELIM + CONFIG_FILENAME);
	rapidjson::Document doc;
	doc.Parse(fileContents.c_str());
	if (doc.HasParseError()){
		throw -1;
	}
	rapidjson::Value *currJsonObj = &doc;
	for (rapidjson::Value::MemberIterator memberItr = currJsonObj->MemberBegin(); memberItr != currJsonObj->MemberEnd(); ++memberItr) {
		if (strcmp(memberItr->name.GetString(), "todo_database_file") == 0 && memberItr->value.IsString()){
			std::string todoDBStr = memberItr->value.GetString();
			m_toDoFilePath = todoDBStr;
		}
	}
}

void TodoConfig::saveConfigFile(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	writer.Key("todo_database_file");
	writer.String(m_toDoFilePath.c_str());
	writer.EndObject();

	FileIO::writeFile(m_programFilePath + FOLDER_DELIM + CONFIG_FILENAME, sb.GetString(), FileIO::FileWriteType::WRITE);
}

void TodoConfig::createNewConfigFile(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	writer.EndObject();

	FileIO::writeFile(m_programFilePath + FOLDER_DELIM + CONFIG_FILENAME, sb.GetString(), FileIO::FileWriteType::WRITE);
}

void TodoConfig::setToDoFilePath(std::string _filePath){
	m_toDoFilePath = _filePath;
}

std::string TodoConfig::getToDoFilePath(){
	return m_toDoFilePath;
}
