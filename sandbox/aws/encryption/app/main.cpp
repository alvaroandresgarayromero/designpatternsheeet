#include <iostream>
#include <cstring>
#include <unistd.h>

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

int main()
{
    /* Init required parameters for AWS initialization routine */
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    {
        /* Initialize AWS user credentials */
        Aws::String access_key{"ASIAW2GKBYBTLTT5NINY"};
        Aws::String secret_key{"lF+tKopHERN1ow9P7TlH6EElozcGv3AY2CYIyQzl"};
        Aws::String token{"FwoGZXIvYXdzEL3//////////wEaDKLAWRw4rxGZ0OVbSyK8ARtgsXNVHrG2RJU3yImANC6pAOMHSbqMLs5viNh4ntUv59N4vzSio5kpHuqyHNtX4qodHTrJIi/jtU7IrjF9pMiv2QvkUi9/L2xAXaetGztOWeDnaGxFKBKV8lwTy3GA7AcPb6yrkZfdD6XsPLwT7l91Xw8v46j8Ox080n3zNfwE+2zXmjQb5hSyXHwIEBbBN/LEDMhkfm9xwuu6pVfL6hiJ+FMf50KeiWmpLx2BVPQuJjwE8G4SDj9WPFEVKLSsy4gGMi0K06uJQLwL2gmSWG8k3pDT6ste7eGXjGMamvnafBqhlDOqrM6J1RRYqP9UA0s="};

        Aws::Auth::AWSCredentials credentials;
        credentials.SetAWSAccessKeyId(access_key);
        credentials.SetAWSSecretKey(secret_key);
        credentials.SetSessionToken(token);

        /* Initialize AWS user configuration */
        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = Aws::String("US_EAST_1");

        Aws::S3::S3Client s3_client(credentials, clientConfig);

        Aws::S3::Model::PutObjectRequest putObjectRequest;
        putObjectRequest.WithBucket("tf-bucket-encryption");

        //this can be any arbitrary stream (e.g. fstream, stringstream etc...)
        auto requestStream = Aws::MakeShared<Aws::StringStream>("s3-sample");
        *requestStream << "Hello World!";

        putObjectRequest.SetBody(requestStream);

        auto putObjectOutcome = s3_client.PutObject(putObjectRequest);

        if(putObjectOutcome.IsSuccess())
        {
            std::cout << "Put object succeeded" << std::endl;
        }
        else
        {
            std::cout << "Error while putting Object " << putObjectOutcome.GetError().GetExceptionName() <<
            " " << putObjectOutcome.GetError().GetMessage() << std::endl;
        }

        char hostname[255];
        memset(hostname, 0, sizeof(hostname));
        gethostname(hostname, sizeof(hostname));

        std::cout << "Hello from encryption: " << hostname << std::endl;

    }

    Aws::ShutdownAPI(options);


    return 0;
}