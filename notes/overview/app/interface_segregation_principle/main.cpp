#include <iostream>
#include <cstring>
#include <unistd.h>

#include <overview/Machine.h>

/* Interface Segregation Principle aims to not
 * create interfaces that are too large.
 *
 * Background: Imagine we have a IMachine interface with a bunch of
 * pure virtual methods, fax(), print(), scan(). These methods
 * consume a document structure.
 *
 * Use Case 1: We can use the IMachine abstract class to create a multi-function
 * printer. The current IMachine interface would work fine.
 *
 * Use Case 2: What if the developer just needs to a create a printer
 * or just a scanner? Currently, the printer class would inherit
 * methods not related to its purpose.
 *
 * Task: Create an interface to meet use case 2 requirements.
 * Segregate the IMachine class to IPrinter, IScanner, IFax interfaces.
 * And then create a printer and machine concrete classes from the interfaces.
 *
 */

int main()
{
    Document doc{"Senior Thesis"};
    Machine my_minimal_printer;
    my_minimal_printer.print(doc);
    my_minimal_printer.scan(doc);


    Fax fax_machine;
    fax_machine.fax(doc);

    return 0;
}