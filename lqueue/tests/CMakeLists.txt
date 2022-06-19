add_library(lib_lqueue_lecturer SHARED ../student/lqueue.c)
target_compile_definitions(lib_lqueue_lecturer PRIVATE
        Front=m_Front
        Dequeue=m_Dequeue
        FrontAndDequeue=m_FrontAndDequeue
        )

set(TESTS
        ../student/lqueue.c
        test_lqueue.c
        default.c
        )
include_directories(../student)
add_library(lib_tests SHARED ${TESTS})
target_link_libraries(lib_tests m)

add_executable(tests test_runner.c)
target_link_libraries(tests m lib_tests lib_lqueue_lecturer ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(lqueue tests)


SET(RUNNER
        ../student/lqueue.c
        main.c
        default.c
        )

include_directories(../student)
add_executable(runner ${RUNNER})

SET(SOLUTION_RUNNER
        ../student/lqueue.c
        main.c
        )

