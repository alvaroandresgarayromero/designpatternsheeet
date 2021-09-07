#ifndef APP_AWSDEMO_H
#define APP_AWSDEMO_H

#include <iostream>
#include <string>
#include <memory>

#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/DeleteMessageRequest.h>


#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>

#include <aws/sns/SNSClient.h>
#include <aws/sns/model/PublishRequest.h>


class AwsDemoBuilder;


class AwsDemo
{
private:
    /* User defined parameters */
    std::string m_snsMessage, m_snsTopicARN;       // AWS SNS Queue full ARN path and message

    std::string m_queueUrl;                        // AWS SQS Queue full URL path

    std::string m_s3Bucket, m_s3Key;               // AWS S3 Bucket name, and key name

    /* private managed by constructor */
    Aws::SQS::SQSClient m_sqsClient;
    Aws::S3::S3Client m_s3Client;
    Aws::SNS::SNSClient m_snsClient;

    //Aws::SQS::Model::Message m_queueMsg;

    AwsDemo()
    {
        std::cout << "AwsDemo started" << std::endl << std::endl;

        /* create SNS Client */
        // no further construction required

        /* create SQS Client */
        Aws::Client::ClientConfiguration client_cfg;
        client_cfg.requestTimeoutMs = 30000;
        m_sqsClient = Aws::SQS::SQSClient{client_cfg};

        /* Create S3 Client */
        // no further construction required
    };

public:
    ~AwsDemo() {};

    /* user must use create method to init elements */
    static AwsDemoBuilder create();

    /* SNS helper methods */
    void publish_sns_message();

    /* SQS helper methods */
    const Aws::Vector<Aws::SQS::Model::Message> get_sqs_messages();
    void delete_sqs_message(const Aws::SQS::Model::Message &msg_sqs);
    void sqs_message_display(const Aws::SQS::Model::Message &msg_sqs );

    /* S3 helper methods */
    Aws::S3::Model::GetObjectOutcome get_s3_object_content();
    void s3_object_content_display(Aws::S3::Model::GetObjectOutcome& s3_object);

    friend class AwsDemoBuilder;
    friend class AwsDemoSqsBuilder;
    friend class AwsDemoS3Builder;
    friend class AwsDemoSnsBuilder;
};




#endif //APP_AWSDEMO_H
