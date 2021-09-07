#include "AwsDemoS3Builder.h"

AwsDemoS3Builder& AwsDemoS3Builder::has_bucket_name(const std::string &name)
{
    ref_root.m_s3Bucket = name;
    return *this;
}

AwsDemoS3Builder& AwsDemoS3Builder::has_key_name(const std::string &name)
{
    ref_root.m_s3Key = name;
    return *this;
}

