#include <iostream>

#include <aws/core/Aws.h>

#include "AwsDemo.h"
#include "AwsDemoBuilder.h"
#include "AwsDemoSqsBuilder.h"
#include "AwsDemoS3Builder.h"
#include "AwsDemoSnsBuilder.h"

int main()
{
    /* Init required parameters for AWS initialization routine */
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
    Aws::InitAPI(options);
    {

        /* Construct AWS DEMO */
        AwsDemo awsdemo = AwsDemo::create()
                          .sns().has_topic_arn_name("arn:aws:sns:us-east-1:867387895277:tf_topic_test")
                                .has_message_content("This message is published by SNS as a payload to AWS lambda")
                          .sqs().has_url_name("https://sqs.us-east-1.amazonaws.com/867387895277/tf_queue_2")
                          .s3().has_bucket_name("buckettestalvaro")
                               .has_key_name("test20.txt");

        /* AWS SNS is used to create asynchronous event trigger to AWS Lambda */
        awsdemo.publish_sns_message();

        /* AWS Lambda Destination is set to route asynchronous function results
         * as an execution record to AWS SQS. Let's verify aws lambda completed processing successfully */
        auto messages = awsdemo.get_sqs_messages();
        auto message = messages[0];
        awsdemo.sqs_message_display(message);
        awsdemo.delete_sqs_message(message);

        /* AWS Lambda wrote an object with the payload contents to AWS S3 */
        auto s3_object = awsdemo.get_s3_object_content();
        awsdemo.s3_object_content_display(s3_object);
    }

    Aws::ShutdownAPI(options);

    return 0;
}