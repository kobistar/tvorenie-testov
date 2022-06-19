add_library(lib_tree_arr_lecturer SHARED ../student/tree_arr.c)
target_compile_definitions(lib_tree_arr_lecturer PRIVATE
        PrintRow=m_PrintRow
        PrintSubtree=m_PrintSubtree
        )

set(TESTS
        ../student/tree_arr.c
        test_tree_arr.c
        default.c
        )
include_directories(../student)
add_library(lib_tests SHARED ${TESTS})
target_link_libraries(lib_tests m)

add_executable(tests test_runner.c)
target_link_libraries(tests m lib_tests lib_tree_arr_lecturer ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(tree_arr tests)

SET(RUNNER
        ../student/tree_arr.c
        main.c
        default.c
        )

include_directories(../student)
add_executable(runner ${RUNNER})
target_link_libraries(runner m ${CHECK_LIBRARIES})

SET(SOLUTION_RUNNER
        ../student/tree_arr.c
        main.c
        )
