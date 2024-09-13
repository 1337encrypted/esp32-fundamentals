set(SOURCES ./src/main.cpp)

idf_component_register(
    SRCS 
        ${SOURCES}
    INCLUDE_DIRS 
        .
        inc
        src
    REQUIRES
        freertos
        esp_common
        gpio
)
