#pragma once
class Options
{
public:
	Options();
	float& getParamFloat(std::string paramName);
	FPoint& getParamFPoint(std::string paramName);
private:
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
};

