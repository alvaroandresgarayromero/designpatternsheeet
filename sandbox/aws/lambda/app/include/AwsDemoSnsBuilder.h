#ifndef APP_AWSDEMOSNSBUILDER_H
#define APP_AWSDEMOSNSBUILDER_H


#include "AwsDemoBuilder.h"

class AwsDemoSnsBuilder : public AwsDemoBuilderBase
{
public:
    AwsDemoSnsBuilder(AwsDemo& a_root) : AwsDemoBuilderBase{a_root} {};

    AwsDemoSnsBuilder& has_message_content(const std::string &name);
    AwsDemoSnsBuilder& has_topic_arn_name(const std::string &name);

};


#endif //APP_AWSDEMOSNSBUILDER_H
