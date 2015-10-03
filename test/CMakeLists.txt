
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
        test_abspath.h
        test_relpath.cpp
        test_relpath.h
        test_listdir.cpp
        test_listdir.h
        test_isdir.cpp
        test_isdir.h
        test_isfile.cpp
        test_isfile.h
        test_walk.cpp
        test_walk.h
        test_exists.cpp
        test_exists.h
        test_commonprefix.cpp
        test_commonprefix.h
        test_splitext.cpp
        test_splitext.h)

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
add_test(test_relpath ftxpathtest relpath)
add_test(test_listdir ftxpathtest listdir)
add_test(test_isdir ftxpathtest isdir)
add_test(test_isfile ftxpathtest isfile)
add_test(test_walk ftxpathtest walk)
add_test(test_exists ftxpathtest exists)
add_test(test_commonprefix ftxpathtest commonprefix)
add_test(test_splitext ftxpathtest splitext)