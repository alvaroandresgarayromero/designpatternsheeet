

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

    std::cout << "Hello from lambda: " << hostname << std::endl;

    // @todo uses AWS SQS to send message to trigger lambda function


    return 0;
}