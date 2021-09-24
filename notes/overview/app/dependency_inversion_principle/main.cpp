#include <iostream>
#include <cstring>
#include <unistd.h>

#include <overview/Temperature.h>

/* Dependency inversion principle has two definitions
 * - High level modules should not depend on low-level modules.
 *   Both should depend on abstraction.
 *   For instance. We can have an abstract interface class that has many concrete classes.
 *   Next we have separate high level module that uses dynamic polymorphism of the interface
 *   base class to access the concrete low level classes.
 * - Abstraction should not depend on details. Details should depend on abstraction.
 *   Therefore, keep abstract interfaces very generic so concrete classes define the details. */


/* High level module:
 * Test class can run tests on
 * actual machine or simulated machine */
class Test
{
public:
    // STP 01 states that temperature must be greater than 0!
    // note: this requirement was randomly made
    template<typename T>
    void STP_01( ITemp<T> &obj)
    {
        std::cout << "Running test on the " << obj.display() << std::endl;

        if(obj.getTemperature() > 0)
        {
            std::cout << "Success STP_01 passed" << std::endl;
        }
        else
        {
            std::cout << "Error STP_01 failed" << std::endl;
        }
    }
};

int main()
{

    Test stp_runner;

    VirtualMachine vm;
    vm.setTemperature(50);
    stp_runner.STP_01(vm);
    std::cout << std::endl << std::endl;

    Machine m;
    m.setTemperature(0);
    stp_runner.STP_01(m);

    return 0;
}