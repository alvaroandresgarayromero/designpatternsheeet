/*
 * Simple sanity check to verify health of workspace
 */
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <S3Client.h>

int main()
{
    char hostname[255];
    memset(hostname, 0, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));

    std::cout << "Hello from encryption " << hostname << std::endl;

    return 0;
}