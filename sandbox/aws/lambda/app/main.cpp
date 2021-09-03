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
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    Aws::InitAPI(options);
    {
        Aws::S3::S3Client s3_client;

        Aws::S3::Model::GetObjectRequest object_request;
        object_request.SetBucket("tf-bucket");
        object_request.SetKey("payload.txt");

        Aws::S3::Model::GetObjectOutcome get_object_outcome =
                s3_client.GetObject(object_request);

        if (get_object_outcome.IsSuccess())
        {
            auto& retrieved_file = get_object_outcome.GetResultWithOwnership().
                    GetBody();

            std::string data;
            while( std::getline(retrieved_file,data) )
            {
                std::cout << data << std::endl;
            }

        }
        else
        {
            auto err = get_object_outcome.GetError();
            std::cout << "Error: GetObject: " <<
                      err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        }
    }

    Aws::ShutdownAPI(options);

    return 0;
}