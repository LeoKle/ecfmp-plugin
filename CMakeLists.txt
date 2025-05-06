CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

CMAKE_POLICY(SET CMP0091 NEW)

PROJECT(ECFMP_PLUGIN VERSION "0.0.0" LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/src/Version.h.in
    ${CMAKE_BINARY_DIR}/Version.h
)

# INCLUDE_DIRECTORIES(
#     ${CMAKE_BINARY_DIR}
#     ${CMAKE_SOURCE_DIR}/src/
#     ${CMAKE_SOURCE_DIR}/external/include
#     ${CMAKE_SOURCE_DIR}
# )

SET(SOURCE_FILES
    src/api/RestApiCurl.cpp
    src/api/RestApiCurl.h
    src/data/EcfmpDataProvider.cpp
    src/data/EcfmpDataProvider.h
    src/data/IFlowMeasureDataProvider.h
    src/types/Filter.cpp
    src/types/Filter.h
    src/types/FlowMeasure.cpp
    src/types/FlowMeasure.h
    src/types/Measure.cpp
    src/types/Measure.h
    src/ECFMP.cpp
    src/ECFMP.h
    src/main.cpp
    src/main.h
)

# Create a static library target, used in tests and shared dll
ADD_LIBRARY(ECFMP_PLUGIN_STATIC STATIC ${SOURCE_FILES})

# Create shared library target - used for Euroscope
ADD_LIBRARY(ECFMP_PLUGIN_SHARED SHARED)
TARGET_SOURCES(ECFMP_PLUGIN_SHARED PRIVATE src/main.cpp src/main.h)
SET_TARGET_PROPERTIES(ECFMP_PLUGIN_SHARED PROPERTIES OUTPUT_NAME "ECFMP")

TARGET_LINK_LIBRARIES(ECFMP_PLUGIN_SHARED PRIVATE
    ECFMP_PLUGIN_STATIC
    ${CMAKE_SOURCE_DIR}/external/lib/EuroScopePlugInDLL.lib
)

# Set include directories
TARGET_INCLUDE_DIRECTORIES(ECFMP_PLUGIN_STATIC PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}
)

TARGET_INCLUDE_DIRECTORIES(ECFMP_PLUGIN_SHARED PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}
)
INCLUDE(external/CMakeLists.txt)

set(gtest_force_shared_crt)
enable_testing()
include(CTest)
add_subdirectory(tests)
