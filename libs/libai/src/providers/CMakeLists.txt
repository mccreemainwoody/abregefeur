cmake_minimum_required(VERSION 3.25)

target_sources(libai
    PRIVATE
        ai_provider.cpp
        openai.cpp
)

target_link_libraries(libai
    PUBLIC
        CURL::libcurl
    PRIVATE
        nlohmann_json::nlohmann_json
)
