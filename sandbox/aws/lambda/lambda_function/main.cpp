#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/platform/Environment.h>


#include <string>

using namespace Aws::Utils::Json;

void dump_s3( std::string const& payload, Aws::S3::S3Client const& s3_client);


aws::lambda_runtime::invocation_response lambda_handler( aws::lambda_runtime::invocation_request const& request,
                                                         Aws::S3::S3Client const& client)
{
    /* Get payload data */
    Aws::Utils::Json::JsonValue json(request.payload);

    if (!json.WasParseSuccessful()) {
        return aws::lambda_runtime::invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    Aws::String aws_s = json.View().WriteReadable();
    std::string s(aws_s.c_str(), aws_s.size());

    dump_s3(s, client);

    return aws::lambda_runtime::invocation_response::success(s, "application/json");
}

void dump_s3( std::string const& payload, Aws::S3::S3Client const& s3_client)
{
    /* Prepare S3 Bucket PutObject Request */
    Aws::S3::Model::PutObjectRequest putObjectRequest;
    putObjectRequest.WithBucket("tf-bucket").WithKey("payload.txt");

    auto requestStream = Aws::MakeShared<Aws::StringStream>("s3-sample");
    *requestStream << payload;

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
}

//int main()
//{
//    aws::lambda_runtime::run_handler(lambda_handler);
//    return 0;
//}
int main()
{
    /* Init required parameters for AWS initialization routine */
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    InitAPI(options);
    {

        Aws::Client::ClientConfiguration config;
        config.caFile = "/etc/pki/tls/certs/ca-bundle.crt"; // REQUIRED!
        Aws::S3::S3Client s3_client(config);

        // function wrapper handler_fn
        auto handler_fn = [&s3_client](aws::lambda_runtime::invocation_request const& req) {
            return lambda_handler(req, s3_client);
        };

        aws::lambda_runtime::run_handler(handler_fn);
    }
    ShutdownAPI(options);
    return 0;
}
