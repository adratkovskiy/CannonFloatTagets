#pragma once
class Options
{
public:
	Options();
	float getParam(std::string paramName);
private:
	std::map<std::string, float> _config;
};

