#ifndef APP_AWSDEMOBUILDER_H
#define APP_AWSDEMOBUILDER_H

#include <iostream>
#include "AwsDemo.h"

class AwsDemoSqsBuilder;
class AwsDemoS3Builder;
class AwsDemoSnsBuilder;

/* Maintains a reference of one AwsDemo object to avoid replications */
class AwsDemoBuilderBase
{
protected:
    AwsDemo &ref_root;
    AwsDemoBuilderBase(AwsDemo& a_root) : ref_root{a_root} {}

public:
    /* enable conversion from 'AwsDemoBuilderBase types' to 'AwsDemo' */
    operator AwsDemo() const
    {
        return std::move(ref_root);
    }

    /* builder facets construction.
     * Construction occurs on the .cpp file to avoid circular dependency
     * since, for ex, AwsDemoSqsBuilder is derived from AwsDemoBuilderBase*/
    AwsDemoSqsBuilder sqs() const;
    AwsDemoS3Builder s3() const;
    AwsDemoSnsBuilder sns() const;

};


/* Constructs the AwsDemo object element */
class AwsDemoBuilder : public AwsDemoBuilderBase {
private:
    AwsDemo root;
public:
    AwsDemoBuilder() : AwsDemoBuilderBase{root} {};
};





#endif //APP_AWSDEMOBUILDER_H
