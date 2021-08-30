# CLion with AWS C++ SDK remote docker environment
# Clion remote docker environment dockerfile: https://github.com/JetBrains/clion-remote
# AWS C++ SDK dockerfile: https://github.com/aws/aws-sdk-cpp/blob/master/CI/docker-file/Ubuntu/20.04/Dockerfile
#
# Build and run:
#   docker-compose up
#
# ssh credentials (test user):
#   user@password

FROM ubuntu:20.04

WORKDIR /app
COPY . /app

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTEND="noninteractive" TZ="America/Los_Angeles" apt-get install -y tzdata

RUN apt-get install -y ssh \
      build-essential \
      gcc \
      g++ \
      gdb \
      clang \
      cmake \
      rsync \
      tar \
      python3 \
      python3-pip \
      git \
      zip \
      wget \
      zlib1g-dev \
      libssl-dev \
      libcurl4-openssl-dev \
      openjdk-8-jdk doxygen \
      ninja-build \
  && apt-get clean

# create 'python3' twin brother named 'python'
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10

# Install maven
RUN apt-get install -y maven

# Install awscli
RUN pip install awscli --upgrade

# Install Boost: Version 1.76.0
RUN cd /home && wget https://sourceforge.net/projects/boost/files/boost/1.76.0/boost_1_76_0.tar.bz2 \
    && tar --bzip2 -xf boost_1_76_0.tar.bz2 \
    && rm boost_1_76_0.tar.bz2 \
    && cd boost_1_76_0 \
    && ./bootstrap.sh --prefix=/usr/local \
    && ./b2 install \
    && cd /home \
    && rm -rf boost_1_76_0

# Install AWS C++ SDK: S3 Bucket, SQS
RUN cd /home \
    && git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp \
    && cd aws-sdk-cpp \
    && mkdir build \
    && cd build \
    && cmake .. -DBUILD_ONLY="s3;sqs" \
    && make install \
    && cd /home \
    && rm -rf aws-sdk-cpp


# Install AWS Lambda runtime (yes separate dependency from AWS C++ SDK)
# Enables us to create C++ lambda functions
RUN cd /home \
    && git clone https://github.com/awslabs/aws-lambda-cpp.git \
    && cd aws-lambda-cpp \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release \
    && make install \
    && cd /home \
    && rm -rf aws-lambda-cpp

# Install Terraform
RUN cd /home \
    && apt-get update && apt-get install -y gnupg software-properties-common curl \
    && curl -fsSL https://apt.releases.hashicorp.com/gpg | apt-key add - \
    && apt-add-repository "deb [arch=amd64] https://apt.releases.hashicorp.com $(lsb_release -cs) main" \
    && apt-get update && apt-get install terraform

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

RUN useradd -m user \
  && yes password | passwd user

RUN usermod -s /bin/bash user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]