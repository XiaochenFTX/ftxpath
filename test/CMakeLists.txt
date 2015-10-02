
set(SOURCE_FILES
        main.cpp
        tester.h
        test_cwd.cpp
        test_cwd.h
        test_isabs.cpp
        test_isabs.h
        test_join.cpp
        test_join.h
        test_basename.cpp
        test_basename.h)

include_directories(../src)

link_directories(../bin)

add_executable(ftxpathtest ${SOURCE_FILES})

target_link_libraries(ftxpathtest ftxpath)

add_test(test_run ftxpathtest run)
add_test(test_cwd ftxpathtest cwd)
add_test(test_isabs ftxpathtest isabs)
add_test(test_join ftxpathtest join)
add_test(test_basename ftxpathtest basename)