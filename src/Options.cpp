#include "stdafx.h"
#include "Options.h"

Options::Options()
{
    rapidxml::xml_document<> xmlDoc;
    rapidxml::file<> xmlFile("base_p/Options.xml");
    xmlDoc.parse<0>(xmlFile.data());
    std::string opt0, opt1;
    for (rapidxml::xml_node<>* node = xmlDoc.first_node()->first_node(); node; node = node->next_sibling())
    {
        const char* ca = "FPoint";
        const char* typeName = node->last_attribute("type")->value();
        if (!strcmp(node->last_attribute("type")->value(), ca)) {
            FPoint multy;
            multy.x = atof(node->first_attribute("x")->value());
            multy.y = atof(node->first_attribute("y")->value());
            _configFPoint.insert({ node->name(), multy });
        }
        else {
            std::string naname = node->name();
            _configFloat.insert({ node->name(), atof(node->first_attribute("val")->value()) });
        }
    }
}

float& Options::getParamFloat(std::string paramName)
{
    std::map<std::string, float>::iterator it;
    it = _configFloat.find(paramName);
    if (it != _configFloat.end())
    {
        return it->second;
    }
}

FPoint& Options::getParamFPoint(std::string paramName)
{
    std::map<std::string, FPoint>::iterator it;
    it = _configFPoint.find(paramName);
    if (it != _configFPoint.end())
    {
        return it->second;
    }
}

