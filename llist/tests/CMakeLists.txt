add_library(lib_llist_lecturer SHARED ../student/llist.c)
target_compile_definitions(lib_llist_lecturer PRIVATE
        FastCat=m_FastCat
        FreshCat=m_FreshCat
        Cut=m_Cut
        )

set(TESTS
        ../student/llist.c
        test_llist.c
        default.c
        )
include_directories(../student)
add_library(lib_tests SHARED ${TESTS})
target_link_libraries(lib_tests m)

add_executable(tests test_runner.c)
target_link_libraries(tests m lib_tests lib_llist_lecturer ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(llist tests)

SET(RUNNER
        ../student/llist.c
        main.c
        default.c
        )

include_directories(../student)
add_executable(runner ${RUNNER})
target_link_libraries(runner m ${CHECK_LIBRARIES})

SET(SOLUTION_RUNNER
        ../student/llist.c
        main.c
        )
