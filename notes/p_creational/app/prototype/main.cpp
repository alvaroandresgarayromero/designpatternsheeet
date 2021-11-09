#include <iostream>
#include <cstring>
#include <unistd.h>
#include <memory>

#include <creational/prototype/prototype.h>
#include <creational/prototype/prototype_serialize.h>

int main()
{
    /* prototype specialization using factory design pattern,
     * we can define a contact business baseline that can be used to create new employees
     * without having to redefine the address and suite. */
    auto contact1 = EmployeeFactory::newEmployee("Alvaro");
    auto contact2 = EmployeeFactory::newEmployee("Courtney");
    std::cout << *contact1 << std::endl;
    std::cout << *contact2 << std::endl;
    std::cout << std::endl << std::endl;


    std::cout << "---- Class copy constructor only supports shallow copy example ---- " << std::endl;
    std::cout << "---- Shows that with serialization, we don't need to define a deep copy constructor ---- " << std::endl;

    /* prototype using boost serialize feature: shows cloning mechanism without deep copy */
    Test obj{"testing boost serialization", 10};


#if 0
    /* note, make sure to put a breakpoint prior to the program terminating
     * since shallow copy will cause memory assert due to attempting to release the heap twice */
    Test obj_shallow_copy = obj;
    std::cout << "Shallow Copy Before: " << std::endl;
    std::cout << "obj: " << obj << std::endl << "obj_shallow_copy: " << obj_shallow_copy << std::endl;
    std::cout << "Shallow Copy After: " << std::endl;
    obj_shallow_copy.update_data(123);
    std::cout << "obj: " << obj << std::endl << "obj_shallow_copy: " << obj_shallow_copy << std::endl;
    std::cout << "Put your breakpoint here!" << std::endl;
#else
    Test obj_shallow_copy = clone(obj);
    std::cout << "Boost Serialization Before: " << std::endl;
    std::cout << "obj: " << obj << std::endl << "obj_shallow_copy: " << obj_shallow_copy << std::endl;
    std::cout << "Boost Serialization After: " << std::endl;
    obj_shallow_copy.update_data(123);
    std::cout << "obj: " << obj << std::endl << "obj_shallow_copy: " << obj_shallow_copy << std::endl;

#endif

    return 0;
}