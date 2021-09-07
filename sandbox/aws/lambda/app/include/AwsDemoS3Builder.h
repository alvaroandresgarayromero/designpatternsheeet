#ifndef APP_AWSDEMOS3BUILDER_H
#define APP_AWSDEMOS3BUILDER_H

#include "AwsDemoBuilder.h"

class AwsDemoS3Builder : public AwsDemoBuilderBase
{
public:
    AwsDemoS3Builder(AwsDemo& a_root) : AwsDemoBuilderBase{a_root} {};

    AwsDemoS3Builder& has_bucket_name(const std::string &name);
    AwsDemoS3Builder& has_key_name(const std::string &name);

};



#endif //APP_AWSDEMOS3BUILDER_H
