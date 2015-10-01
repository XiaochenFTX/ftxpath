
set(SOURCE_FILES
        main.cpp test_cwd.cpp test_cwd.h)

include_directories(../src)

link_directories(../bin)

add_executable(ftxpathtest ${SOURCE_FILES})

target_link_libraries(ftxpathtest ftxpath)

add_test(test_run ftxpathtest run)

add_test(test_cwd ftxpathtest cwd)