
set(SOURCE_FILES
        main.cpp )

include_directories(../src)

add_executable(ftxpathtest ${SOURCE_FILES})

add_test(test_run ftxpathtest)