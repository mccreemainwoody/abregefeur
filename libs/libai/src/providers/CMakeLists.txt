cmake_minimum_required(VERSION 3.25)

target_sources(libai
    PRIVATE
        ai_provider.cpp
)

target_link_libraries(libai
    PRIVATE
        CURL::libcurl
)
