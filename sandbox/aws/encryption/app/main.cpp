

#include <iostream>
#include <cstring>
#include <unistd.h>

#include <aws/core/Aws.h>

int main()
{
   // Aws::InitAPI();

    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hello from encryption: " << hostname << std::endl;

    return 0;
}