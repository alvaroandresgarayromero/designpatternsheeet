#include "AwsDemoSqsBuilder.h"

AwsDemoSqsBuilder& AwsDemoSqsBuilder::has_url_name(const std::string &name)
{
    ref_root.m_queueUrl = name;
    return *this;
}