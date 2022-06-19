add_library(lib_lstack_lecturer SHARED ../student/lstack.c)
target_compile_definitions(lib_lstack_lecturer PRIVATE
        Top=m_Top
        Pop=m_Pop
        TopAnPop=m_TopAnPop
        )

set(TESTS
        ../student/lstack.c
        test_lstack.c
        default.c
        )
include_directories(../student)
add_library(lib_tests SHARED ${TESTS})
target_link_libraries(lib_tests m)

add_executable(tests test_runner.c)
target_link_libraries(tests m lib_tests lib_lstack_lecturer ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(lstack tests)

SET(RUNNER
        ../student/lstack.c
        main.c
        default.c
        )

include_directories(../student)
add_executable(runner ${RUNNER})

SET(SOLUTION_RUNNER
        ../student/lstack.c
        main.c
        )
