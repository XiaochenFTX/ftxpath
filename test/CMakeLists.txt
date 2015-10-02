
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
        test_basename.h
        test_dirname.cpp
        test_dirname.h
        test_split.cpp
        test_split.h
        test_normpath.cpp
        test_normpath.h
        test_abspath.cpp
        test_abspath.h)

include_directories(../src)

link_directories(../bin)

add_executable(ftxpathtest ${SOURCE_FILES})

target_link_libraries(ftxpathtest ftxpath)

add_test(test_run ftxpathtest run)
add_test(test_cwd ftxpathtest cwd)
add_test(test_isabs ftxpathtest isabs)
add_test(test_join ftxpathtest join)
add_test(test_basename ftxpathtest basename)
add_test(test_dirname ftxpathtest dirname)
add_test(test_split ftxpathtest split)
add_test(test_normpath ftxpathtest normpath)
add_test(test_abspath ftxpathtest abspath)