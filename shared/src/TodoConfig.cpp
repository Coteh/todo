#include "TodoConfig.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

TodoConfig::TodoConfig() {
}

TodoConfig::~TodoConfig() {
}

void TodoConfig::processConfig(std::string _configContents){
	rapidjson::Document doc;
	doc.Parse(_configContents.c_str());
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

std::string TodoConfig::writeConfig(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	writer.Key("todo_database_file");
	writer.String(m_toDoFilePath.c_str());
	writer.EndObject();

	return sb.GetString();
}

void TodoConfig::setToDoFilePath(std::string _filePath){
	m_toDoFilePath = _filePath;
}

std::string TodoConfig::getToDoFilePath() const{
	return m_toDoFilePath;
}
