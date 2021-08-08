#include <iostream>
#include <cstring>
#include <unistd.h>

#include <overview/Journal.h>

int main()
{
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hello from overview notes: " << hostname << std::endl;

    Journal obj{"Dear Diary"};
    obj.add_entry("I'm writing this from Dependency Inversion Principle main");

    std::cout << obj << std::endl;

    return 0;
}