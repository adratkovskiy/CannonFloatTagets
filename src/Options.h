#pragma once
class Options
{
public:
	Options();
	std::string getStr();
private:
	std::map<std::string, std::string> config;
};

