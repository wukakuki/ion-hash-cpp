#[[
 Copyright (C) Siqi.Wu - All Rights Reserved
 Unauthorized copying of this file, via any medium is strictly prohibited
 Written by Siqi.Wu <lion547016@gmail.com>, July 2021
]]

cmake_minimum_required(VERSION 3.20)
project(ionhashcpp)

set(CMAKE_CXX_STANDARD 14)

file(GLOB ionhashcpp_SRC
        "Ion*.h"
        "MessageDigestIonHasher.h"
        "MessageDigestIonHasherProvider.h"
        "Ion*.cpp"
        )

add_library(ionhashcpp SHARED ${ionhashcpp_SRC})

target_link_libraries(ionhashcpp PUBLIC "libionc.so")
target_link_libraries(ionhashcpp PUBLIC "libdecNumber.so")

target_compile_definitions(ionhashcpp PUBLIC "DECNUMDIGITS=64")
