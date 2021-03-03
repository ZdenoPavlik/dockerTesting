# Get the base Ubuntu image from Docker Hub
FROM ubuntu:20.04

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the dependencies
RUN apt-get -y install clang gcc-9 g++-9 tzdata
RUN apt-get -y install git cmake build-essential
RUN apt-get -y install libgtest-dev libgmock-dev libboost-all-dev libcpprest-dev

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/dockertest1

# Specify the working directory
WORKDIR /usr/src/dockertest1

#install apt-add-repository
#RUN apt-get -y install software-properties-common apt-utils

#install pistache
#RUN git clone --recurse-submodules https://github.com/pistacheio/pistache.git
#RUN cd pistache
RUN git clone --recurse-submodules https://github.com/pistacheio/pistache.git && cd pistache && mkdir buildPistache && cd buildPistache && cmake -DCMAKE_BUILD_TYPE=Release .. && make && make install && cp /usr/local/lib/*.a /usr/lib
RUN ls /usr/lib
RUN ls /usr/local/lib
#RUN cmake -DCMAKE_BUILD_TYPE=Release ..
#RUN make
#RUN make install

# Use Clang to compile the Test.cpp source file
COPY *.a /usr/lib
RUN g++-9 -o main main.cpp

# Run the output program from the previous step
CMD ["./main"]
