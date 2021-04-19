# Get the base Ubuntu image from Docker Hub
FROM ubuntu:20.04
#maintenaner
#version

# Update apps on the base image
RUN apt-get -y update && apt-get upgrade -y && apt-get -y install apt-transport-https

# Install the dependencies, beware of layers!
RUN apt-get -y install gcc-9 g++-9 tzdata
RUN apt-get -y install git cmake build-essential
RUN apt-get -y install libgtest-dev libgmock-dev libboost-all-dev
RUN apt-get -y install libcpprest-dev

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/dockertest1

# Specify the working directory
WORKDIR /usr/src/dockertest1

RUN ls &&\
    pwd &&\
    cd ~ &&\
    pwd &&\
    ls

RUN mkdir -p build &&\
    cd build &&\
    cmake .. &&\
    make -j 5

# Run the output program from the previous step
RUN ls
CMD ["build/cppRestSdkInDocker"]

#Entry point vs CMD
#https://www.ctl.io/developers/blog/post/dockerfile-entrypoint-vs-cmd/

#attach, exec
#user management
#arguments, environment variables
#other commands like CMD, COPY, WORKDIR, ADD (vs COPY)