#include "stdafx.h"
#include "Options.h"

Options::Options()
{
    rapidxml::xml_document<> xmlDoc;
    rapidxml::file<> xmlFile("base_p/Options.xml");
    xmlDoc.parse<0>(xmlFile.data());
    for (rapidxml::xml_node<>* node = xmlDoc.first_node()->first_node(); node; node = node->next_sibling())
    {
        if (!strcmp(node->last_attribute("type")->value(), (const char*) "FPoint")) {
            FPoint multy;
            multy.x = atof(node->first_attribute("x")->value());
            multy.y = atof(node->first_attribute("y")->value());
            _configFPoint.insert({ node->name(), multy });
        }
        else if (!strcmp(node->last_attribute("type")->value(), (const char*)"vector")) {
            const int points_size = 5;
            for (int i = 0; i < points_size; i++)
            {
                std::string paramNumber = "p" + std::to_string(i);
                _configSplinePoints.push_back(atof(node->first_attribute(paramNumber.c_str())->value()));
            }
        }
        else if (!strcmp(node->last_attribute("type")->value(), (const char*)"string")) {
            _configString.insert({ node->name(), node->first_attribute("val")->value() });
        }
        else if (!strcmp(node->last_attribute("type")->value(), (const char*)"float")) {
            std::string naname = node->name();
            _configFloat.insert({ node->name(), atof(node->first_attribute("val")->value()) });
        }
        else if (!strcmp(node->last_attribute("type")->value(), (const char*)"int")) {
            std::string naname = node->name();
            _configInt.insert({ node->name(), atoi(node->first_attribute("val")->value()) });
        }
    }
}

const int Options::getParamInt(const std::string& paramName)
{
    std::map<std::string, int>::iterator it;
    it = _configInt.find(paramName);
    if (it != _configInt.end())
    {
        return it->second;
    }
}

const float Options::getParamFloat(const std::string& paramName)
{
    std::map<std::string, float>::iterator it;
    it = _configFloat.find(paramName);
    if (it != _configFloat.end())
    {
        return it->second;
    }
}

const FPoint& Options::getParamFPoint(const std::string& paramName)
{
    std::map<std::string, FPoint>::iterator it;
    it = _configFPoint.find(paramName);
    if (it != _configFPoint.end())
    {
        return it->second;
    }
}

const std::string& Options::getParamString(const std::string& paramName)
{
    std::map<std::string, std::string>::iterator it;
    it = _configString.find(paramName);
    if (it != _configString.end())
    {
        return it->second;
    }
}

const std::vector<float>& Options::getSplinePoints() const noexcept
{
    return _configSplinePoints;
}

const std::vector<uint8_t>& Options::getColor(const std::string& paramName) const noexcept
{
    std::map<std::string, std::vector<uint8_t>>::iterator it;
    it = _color.find(paramName);
    if (it != _color.end())
    {
        return it->second;
    }
}

