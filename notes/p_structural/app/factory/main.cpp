#include <iostream>
#include <cstring>
#include <unistd.h>
#include <memory>

#include <creational/factory/inner_factory.h>
#include <creational/factory/abstract_factory.h>

int main()
{
    // inner factory
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