#include <iostream>
#include <cstring>
#include <unistd.h>
#include <memory>

#include "Journal.h"
//#include "builder/builder.h"
#include "factory/inner_factory.h"
#include "factory/abstract_factory.h"
/* This is a scratch board app for testing, debugging, and developing new
 * library features by linking directly to the static library
 * in the build tree. */


int main()
{

    Point p = Point::factory.newCatersian(5,4);


    // abstract factory: calling without using the factory
    std::unique_ptr<HotDrink> p_chef = std::make_unique<Coffee>();
    p_chef->prepare(10);

    // abstract factory: calling with factory
    std::unique_ptr<FactoryHotDrink> p_factory = std::make_unique<FactoryTea>();
    std::unique_ptr<HotDrink> p_waiter = p_factory->make();
    p_waiter->prepare(5);


    return 0;
}