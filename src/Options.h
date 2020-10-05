#pragma once
class Options
{
public:
	Options();
	const float& getParamFloat(const std::string paramName);
	const FPoint& getParamFPoint(std::string paramName);
	const std::vector<float>& getSplinePoints() const noexcept;
private:
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
	std::vector<float> _configSplinePoints;
};

