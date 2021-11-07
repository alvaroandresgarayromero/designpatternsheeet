#include <iostream>
#include <cstring>
#include <unistd.h>
#include <memory>

#include <creational/builder/builder.h>


int main()
{
    std::unique_ptr<HtmlElements> html = HtmlElements::builder("Alvaro")->add_child("test")->add_child("test2")->build();
    std::cout <<  html->str() << std::endl;
    std::cout << std::endl;
    return 0;
}