#pragma once

class Options
{
public:
	Options();

	int getParamInt(const std::string& paramName);
	float getParamFloat(const std::string& paramName);
	const FPoint& getParamFPoint(const std::string& paramName);
	const std::string& getParamString(const std::string& paramName);
	const std::vector<float>& getSplinePoints() const;
	const Color& getColor(const std::string& paramName);
	const IRect& getRect(const std::string& paramName);

private:
	std::map<std::string, std::string> _configString;
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
	std::map<std::string, int> _configInt;
	std::map<std::string, Color> _color;
	std::map<std::string, IRect> _rect;
	std::vector<float> _configSplinePoints;
};

