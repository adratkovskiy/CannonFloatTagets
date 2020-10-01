#include "stdafx.h"
#include "Options.h"

Options::Options()
{
	rapidxml::xml_document<char> doc;
	try {
        std::string fname_xml = "base_p/Options.xml";
		//std::ifstream file(fname_xml.c_str());
        //IO::InputStream stream = Core::fileSystem.OpenRead(fname_xml);
        //IO::InputStream file;

        IO::InputStreamPtr file = Core::fileSystem.OpenRead(fname_xml);
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');

        doc.parse<0>(&buffer[0]);
    }
    catch (rapidxml::parse_error e) {
        e.what();
    }
    rapidxml::xml_node<>* root_node = doc.first_node();

    if (root_node != NULL)
    {
        rapidxml::xml_node<>* node = root_node->first_node("section");
        if (node) node = node->first_node("parameter");
        while (node != NULL)
        {
            rapidxml::xml_attribute<>* a = node->first_attribute("id");
            if (a != NULL)
            {
                config[a->value()] = node->value();
            }

            node = node->next_sibling();
        }
    }

    typedef std::map<std::string, std::string>::const_iterator it;
    for (it i = config.begin(); i != config.end(); i++)
    {
        std::cout << i->first << "\t= " << i->second << std::endl;
    }
    std::cout << "Configuration loaded" << std::endl;
}

std::string Options::getStr()
{
    config;
    std::map<std::string, std::string>::iterator it;
    for (it = config.begin(); it != config.end(); ++it)
    {
        it->first;
    }
    return "asd";
}
