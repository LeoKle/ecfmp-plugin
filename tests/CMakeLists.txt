if(BUILD_TESTING)
    find_package(GTest REQUIRED)

    add_executable(tests
        test_main.cpp
    )

    target_include_directories(tests PRIVATE
        ${CMAKE_SOURCE_DIR}/tests
    )
    
    TARGET_LINK_LIBRARIES(tests PRIVATE
        ECFMP_PLUGIN_STATIC
        GTest::gtest_main
        GTest::gtest
        GTest::gmock
    )
    
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()