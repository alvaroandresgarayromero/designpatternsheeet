#include <iostream>
#include <cstring>
#include <unistd.h>

#include "Journal.h"


/* This is a scratch board app for testing, debugging, and developing new
 * library features by linking directly to the static library
 * in the build tree. */
int main()
{
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hello from: " << hostname << std::endl;

    Journal obj{"Dear Diary"};
    obj.add_entry("I'm writing this from library test main function");

    std::cout << obj << std::endl;

    return 0;
}