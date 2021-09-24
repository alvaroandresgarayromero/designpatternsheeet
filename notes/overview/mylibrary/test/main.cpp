#include <iostream>
#include <cstring>
#include <unistd.h>

#include "Machine.h"

/* This is a scratch board app for testing, debugging, and developing new
 * library features by linking directly to the static library
 * in the build tree. */
int main()
{
    Document doc{"Senior Final Thesis"};
    Machine my_minimal_printer;
    my_minimal_printer.print(doc);
    my_minimal_printer.scan(doc);


    Fax fax_machine;
    fax_machine.fax(doc);
    return 0;
}