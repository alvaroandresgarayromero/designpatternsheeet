#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <string>

using namespace Aws::Utils::Json;

aws::lambda_runtime::invocation_response lambda_handler( aws::lambda_runtime::invocation_request const& request)
{
    Aws::Utils::Json::JsonValue json(request.payload);

    if (!json.WasParseSuccessful()) {
        return aws::lambda_runtime::invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    Aws::String aws_s = json.View().WriteReadable();
    std::string s(aws_s.c_str(), aws_s.size());

    return aws::lambda_runtime::invocation_response::success(s, "application/json");
}

int main()
{
    aws::lambda_runtime::run_handler(lambda_handler);
    return 0;
}