#pragma once
class Options
{
public:
	Options();
	const float& getParamFloat(std::string paramName) noexcept;
	const FPoint& getParamFPoint(std::string paramName) noexcept;
	const std::vector<float>& getSplinePoints() noexcept;
private:
	std::map<std::string, float> _configFloat;
	std::map<std::string, FPoint> _configFPoint;
	std::vector<float> _configSplinePoints;
};

