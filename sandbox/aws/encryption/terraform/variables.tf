variable "a_aws_user" {
    type = list(object({
        access_key = string
        secret_key = string
        token = string
    }))
    default = [
        {
            access_key = "ASIAW2GKBYBTPR7JVYRW"
            secret_key = "HUSN5RE/EvZPFFJe7uHRmrHsI8YMGxpzUngjEGJR"
            token = "FwoGZXIvYXdzELn//////////wEaDJk4OMNF3tECtorBdCK8AZYxOPceliUfxlnQMjIEDSfURdDejGr60VH1EZFZieLhct1oMC6KQ+midDOPNHsr5owe5CEeMzoz+m8dqO9E6VwTz8TB8zjL6njdS4Mxc6W0HJBTxUAZavP2S8h47bJ94coMEfQ250F7kGWo1swRceZRZ1ADHF5aj+aJwVPS8oUmiDuBlhbtg3W6qmv0KSGl3MwrMn/mJT8+yXYrn/m9wyQ578fBcNzEJjwDH3pkVLEAsm1pRgcVgLMqfXooKLCakogGMi04QtTffXYzBP9naQ03soWmt5bRF5/f4Z6ZG2lXIRbTLGn0IkBkMj9MOisHZuA="
        }
    ]
}

variable "a_region" {
    type = string
    default = "us-east-1"
}