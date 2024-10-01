add_library(longNumberLib
    LongNumber.cpp
    LongNumberModulo.cpp
)
target_include_directories(longNumberLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
