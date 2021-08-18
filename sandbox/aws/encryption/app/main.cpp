#include <iostream>
#include <cstring>
#include <unistd.h>

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

#define OVERRIDE_AWS_CREDENTIALS
//#undef OVERRIDE_AWS_CREDENTIALS


int main()
{
    /* Init required parameters for AWS initialization routine */
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    Aws::InitAPI(options);
    {

        #ifdef OVERRIDE_AWS_CREDENTIALS
            /* Initialize AWS user credentials
             * (these macros are predefined during compile time. See CMakeList.txt)*/
            Aws::String access_key{ACCESS_KEY};
            Aws::String secret_key{SECRET_KEY};

            Aws::Auth::AWSCredentials credentials;
            credentials.SetAWSAccessKeyId(access_key);
            credentials.SetAWSSecretKey(secret_key);

            /* Initialize AWS user configuration */
            Aws::Client::ClientConfiguration clientConfig;
            clientConfig.region = Aws::Region::US_EAST_1;

            Aws::S3::S3Client s3_client(credentials, clientConfig);

        #else

            /* Uses AWS credentials and config files from
             * /home/user/.aws/ */
            Aws::S3::S3Client s3_client;
        #endif

        Aws::S3::Model::PutObjectRequest putObjectRequest;
        putObjectRequest.WithBucket("tf-bucket-encryption").WithKey("sweet4.txt");

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

        //std::cout << s3_client << std::endl;


        char hostname[255];
        memset(hostname, 0, sizeof(hostname));
        gethostname(hostname, sizeof(hostname));

        std::cout << "Hello from encryption: " << hostname << std::endl;

    }

    Aws::ShutdownAPI(options);


    return 0;
}