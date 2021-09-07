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
        std::cout << "Message published successfully " << std::endl;
    }
    else
    {
        std::cout << "Error while publishing message " << psms_out.GetError().GetMessage()
                  << std::endl;
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "Error while publishing message "  +
                                psms_out.GetError().GetMessage())
    }
}


/* DESCRIPTION: Polls in 20 secs intervals for a message to arrive into AWS SQS Queue
 * INPUT: NONE
 * OUTPUT: Vector of messages
 * NOTE: Currently set to retrieve ONE message and timeout after 30 seconds
 */
const Aws::Vector<Aws::SQS::Model::Message> AwsDemo::read_sqs_messages()
{
    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    rm_req.SetQueueUrl(m_queueUrl.c_str());
    rm_req.SetMaxNumberOfMessages(1);

    auto rm_out = m_sqsClient.ReceiveMessage(rm_req);

    AWS_DEMO_ASSERT(rm_out.IsSuccess(),
                    "Error receiving message from queue " +
                    m_queueUrl + ": " + rm_out.GetError().GetMessage())

    const auto& messages = rm_out.GetResult().GetMessages();

    if(messages.size() != 0)
    {
        std::cout << "Successfully found " << messages.size() << " message(s) "
                  << " on queue " << m_queueUrl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "No messages received from queue " + m_queueUrl + ". " +
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
        std::cout << "Successfully deleted message " << msg_sqs.GetMessageId()
                  << " from queue " << m_queueUrl << std::endl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "Error deleting message "  + msg_sqs.GetMessageId() +
                        " from queue " + m_queueUrl + ": " +
                        dm_out.GetError().GetMessage() )
    }
}

/* DESCRIPTION: Gets and displays contents from S3 object
 * INPUT: None
 * OUTPUT: None
 */
void AwsDemo::display_s3_object_content()
{

    Aws::S3::S3Client s3_client;

    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(m_s3Bucket.c_str());
    object_request.SetKey(m_s3Key.c_str());

    Aws::S3::Model::GetObjectOutcome get_object_outcome =
            m_s3Client.GetObject(object_request);

    if (get_object_outcome.IsSuccess())
    {
        std::cout << "Successfully retrieved message content " <<
                  " from S3 bucket: " << m_s3Bucket << ", " << "key: " << m_s3Key << std::endl << std::endl;
    }
    else
    {
        AWS_DEMO_ASSERT(ALWAYS_ASSERT,
                        "Error: GetObject: "  +  get_object_outcome.GetError().GetExceptionName() +
                        ": " + get_object_outcome.GetError().GetMessage() )

    }

    auto& retrieved_file = get_object_outcome.GetResultWithOwnership().GetBody();

    std::string data;
    std::cout << "S3 Bucket:" << std::endl;
    while( std::getline(retrieved_file,data) )
    {
        std::cout << data << std::endl;
    }


}