#include "AwsDemo.h"
#include "AwsDemoBuilder.h"
#include "utils.h"

/* DESCRIPTION: Entrypoint for fluent builder interface for constructing a AwsDemo object.
 * INPUT: NONE
 * OUTPUT: builder class instance
 */
AwsDemoBuilder AwsDemo::create()
{
    return AwsDemoBuilder{};
}

void AwsDemo::publish_sns_message()
{
    Aws::SNS::Model::PublishRequest psms_req;
    psms_req.SetMessage(m_snsMessage);
    psms_req.SetTopicArn(m_snsTopicARN);

    auto psms_out = m_snsClient.Publish(psms_req);

    if (psms_out.IsSuccess())
    {
        std::cout << "SNS: Message published successfully " << std::endl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "SNS: Error while publishing message "  +
                                psms_out.GetError().GetMessage())
    }
}


/* DESCRIPTION: Polls in 20 secs intervals for a message to arrive into AWS SQS Queue
 * INPUT: NONE
 * OUTPUT: Vector of messages
 * NOTE: Currently set to retrieve ONE message and timeout after 30 seconds
 */
const Aws::Vector<Aws::SQS::Model::Message> AwsDemo::get_sqs_messages()
{
    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    rm_req.SetQueueUrl(m_queueUrl.c_str());
    rm_req.SetMaxNumberOfMessages(1);

    auto rm_out = m_sqsClient.ReceiveMessage(rm_req);

    AWS_DEMO_ASSERT(rm_out.IsSuccess(),
                    "SQS: Error receiving message from queue " +
                    m_queueUrl + ": " + rm_out.GetError().GetMessage())

    const auto& messages = rm_out.GetResult().GetMessages();

    if(messages.size() != 0)
    {
        std::cout << "SQS: Successfully found " << messages.size() << " message(s) "
                  << "from queue " << m_queueUrl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "SQS: No messages received from queue " + m_queueUrl + ". " +
                        "Go to the AWS SQS Console and check if the message is in the dead letter queue")
    }

    return messages;
}

/* DESCRIPTION: Deletes message from AWS SQS queue.
 * INPUT: Requested message to remove from queue
 * OUTPUT: None
 */
void AwsDemo::delete_sqs_message(const Aws::SQS::Model::Message &msg_sqs)
{
    Aws::SQS::Model::DeleteMessageRequest dm_req;
    dm_req.SetQueueUrl(m_queueUrl.c_str());
    dm_req.SetReceiptHandle(msg_sqs.GetReceiptHandle());

    auto dm_out = m_sqsClient.DeleteMessage(dm_req);
    if (dm_out.IsSuccess())
    {
        std::cout << "SQS: Successfully deleted message " << msg_sqs.GetMessageId()
                  << " from queue " << m_queueUrl << std::endl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "SQS: Error deleting message "  + msg_sqs.GetMessageId() +
                        " from queue " + m_queueUrl + ": " +
                        dm_out.GetError().GetMessage() )
    }
}

/* DESCRIPTION: Displays SQS message in a human-readable format
 * INPUT: SQS message object
 * OUTPUT:None
 */
void AwsDemo::sqs_message_display(const Aws::SQS::Model::Message &msg_sqs )
{

    Aws::OStringStream oss;

    Aws::Utils::Json::JsonValue json_sqs_data(msg_sqs.GetBody());
    AWS_DEMO_ASSERT(json_sqs_data.WasParseSuccessful(),
                    "SQS: Failed to parse data contents into human readable json format")

    oss << "Received message:" << std::endl;
    oss << "  MessageId: " << msg_sqs.GetMessageId() << std::endl;
    oss << "  ReceiptHandle: " << msg_sqs.GetReceiptHandle() << std::endl;
    oss << "  Body: " << json_sqs_data.View().WriteReadable()  << std::endl << std::endl;

    std::cout << oss.str() << std::endl;

}


/* DESCRIPTION: Gets object from S3 bucket
 * INPUT: None
 * OUTPUT: S3 Object Outcome
 */
Aws::S3::Model::GetObjectOutcome AwsDemo::get_s3_object_content()
{
    Aws::S3::S3Client s3_client;

    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(m_s3Bucket.c_str());
    object_request.SetKey(m_s3Key.c_str());

    Aws::S3::Model::GetObjectOutcome s3_object_outcome =
            m_s3Client.GetObject(object_request);

    if (s3_object_outcome.IsSuccess())
    {
        std::cout << "S3: Successfully retrieved message content " <<
                  "from S3 bucket: " << m_s3Bucket << ", " << "key: " << m_s3Key << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "S3: Error: GetObject: "  +  s3_object_outcome.GetError().GetExceptionName() +
                        ": " + s3_object_outcome.GetError().GetMessage() )
    }

    return s3_object_outcome;

}

/* DESCRIPTION: Displays S3 object contents in a human-readable format
 * INPUT: S3 object outcome
 * OUTPUT:None
 */
void AwsDemo::s3_object_content_display(Aws::S3::Model::GetObjectOutcome& s3_object)
{
    Aws::OStringStream oss;

    Aws::IOStream& retrieved_file = s3_object.GetResult().GetBody();

    Aws::Utils::Json::JsonValue json(retrieved_file);

    AWS_DEMO_ASSERT(json.WasParseSuccessful(),
                    "S3: Failed to parse data contents into human readable json format")

    oss << "Object's Content:" << std::endl;
    oss << "  Body: " <<  json.View().WriteReadable() << std::endl;

    std::cout << oss.str() << std::endl;


}

