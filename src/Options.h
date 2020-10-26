#pragma once

class Options
{
public:
	Options();
	const int getParamInt(const std::string& paramName);
	const float getParamFloat(const std::string& paramName);
	const FPoint& getParamFPoint(const std::string& paramName);
	const std::string& getParamString(const std::string& paramName);
	const std::vector<float>& getSplinePoints() const noexcept;
	const std::vector<uint8_t>& getColor(const std::string& paramName) const noexcept;
private:
	std::map<std::string, std::string> _configString;
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
	std::map<std::string, int> _configInt;
	std::map<std::string, std::vector<uint8_t>> _color;
	std::vector<float> _configSplinePoints;
};

