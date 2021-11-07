#ifndef OVERVIEW_BUILDER_H
#define OVERVIEW_BUILDER_H

#include <vector>
#include <iostream>
#include <sstream>

/* builders are used to construct object piece-wisely (in steps) */
class HtmlBuilder;

class HtmlElements
{
public:

    HtmlElements() {}
    HtmlElements(const std::string &name) : name(name) {}

    std::string name;
    std::vector<HtmlElements> elements;

    std::string str() const {
        std::ostringstream oss;
        oss << "_name: " << name << std::endl;
        for (auto value : elements){
            oss <<  "_elements: " << value.name << std::endl;
        }
        return oss.str();
    }

    // hint user to use builder
    static std::unique_ptr<HtmlBuilder> builder(const std::string &name)
    {
        return std::make_unique<HtmlBuilder>(name);
    }



};

/* here we define a separate builder class that encapsulates our interface */
class HtmlBuilder
{
private:
    std::unique_ptr<HtmlElements> root;
public:

    HtmlBuilder(const std::string &name) {
        root = std::make_unique<HtmlElements>(name);
    }

    HtmlBuilder *add_child(const std::string &name)
    {
        root->elements.push_back({name});
        return this;
    }

    /* to support conversion back to our interface */
    std::unique_ptr<HtmlElements> build()
    {
        return std::move(root);
    }


};




#endif //OVERVIEW_BUILDER_H
