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
        _config.insert({ node->name(), atof(node->first_attribute()->value()) });
    }
}

float Options::getParam(std::string paramName)
{
    auto search = _config.find(paramName);
    if (search != _config.end())
    {
        return search->second;
    }
    else
    {
        return 0.0f;
    }
}

