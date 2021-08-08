/*
 * Simple sanity check to verify health of workspace
 */
#include <iostream>
#include <cstring>
#include <unistd.h>
//#include <aws/core/Aws.h>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

c
int main()
{
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hello from encryption " << hostname << std::endl;

    return 0;
}