#pragma once

class Options
{
public:
	Options();
	const float getParamFloat(const std::string& paramName);
	const FPoint& getParamFPoint(const std::string& paramName);
	const std::string& getParamString(const std::string& paramName);
	const std::vector<float>& getSplinePoints() const noexcept;
private:
	std::map<std::string, std::string> _configString;
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
	std::vector<float> _configSplinePoints;
};

