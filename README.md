# ichaika_rest

This is a test project of rest service

## SETUP BUILD ENVIRONMENT

C+17 standard should be supported by target platform.
CentOS 8 is used as a target platform in the article.

## INSTALL REQUIRED LIBRARIES

### Install GTest suite

> sudo dnf install gtest-devel

### Install Drogon library

Install required libraries:

> sudo dnf install jsoncpp-devel
> sudo dnf install libuuid-devel
> sudo dnf install zlib-devel zlib-static

Download Drogon library:

> git clone https://github.com/drogonframework/drogon

Build and install Drogon librry

> cd drogon
> cmake -B build
> cmake --build build
> cmake --install build

## BUILD AND RUN PROJECT 

To build project in "build" directory use following commands:

> cd ichaika_rest
> cmake -B build
> cmake --build build

Run unit testss:

> ctest --test-dir build

Run application:

> ./build/ichaika_rest 5 2 

Run test

> ./post_get.sh