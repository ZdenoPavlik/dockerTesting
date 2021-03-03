# Get the base Ubuntu image from Docker Hub
FROM ubuntu:20.04

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang gcc-9 g++-9

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/dockertest1

# Specify the working directory
WORKDIR /usr/src/dockertest1

# Use Clang to compile the Test.cpp source file
RUN g++-9 -o main main.cpp

# Run the output program from the previous step
CMD ["./main"]
