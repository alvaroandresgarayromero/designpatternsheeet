#ifndef APP_AWSDEMOSQSBUILDER_H
#define APP_AWSDEMOSQSBUILDER_H

#include "AwsDemoBuilder.h"

class AwsDemoSqsBuilder : public AwsDemoBuilderBase
{
public:
    AwsDemoSqsBuilder(AwsDemo& a_root) : AwsDemoBuilderBase{a_root} {};

    AwsDemoSqsBuilder& has_url_name(const std::string &name);
};


#endif //APP_AWSDEMOSQSBUILDER_H
