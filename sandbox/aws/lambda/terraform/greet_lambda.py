import os


def lambda_handler(event, context):
    lambda_environment = os.environ['greeting']

    message = f"{lambda_environment} from Lambda!"
    return {'message': message}
