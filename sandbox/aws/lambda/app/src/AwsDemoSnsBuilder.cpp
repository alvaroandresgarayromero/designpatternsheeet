#include "AwsDemoSnsBuilder.h"

AwsDemoSnsBuilder& AwsDemoSnsBuilder::has_message_content(const std::string &name)
{
    ref_root.m_snsMessage = name;
    return *this;
}

AwsDemoSnsBuilder& AwsDemoSnsBuilder::has_topic_arn_name(const std::string &name)
{
    ref_root.m_snsTopicARN = name;
    return *this;
}