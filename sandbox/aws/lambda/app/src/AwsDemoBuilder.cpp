#include "AwsDemoBuilder.h"
#include "AwsDemoSqsBuilder.h"
#include "AwsDemoS3Builder.h"
#include "AwsDemoSnsBuilder.h"

AwsDemoSqsBuilder AwsDemoBuilderBase::sqs() const
{
    return AwsDemoSqsBuilder{ref_root};
}

AwsDemoS3Builder AwsDemoBuilderBase::s3() const
{
    return AwsDemoS3Builder{ref_root};
}

AwsDemoSnsBuilder AwsDemoBuilderBase::sns() const
{
    return AwsDemoSnsBuilder{ref_root};
}