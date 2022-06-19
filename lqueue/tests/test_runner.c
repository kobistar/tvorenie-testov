#include <check.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Suite* suite_reverse(void);

int main(int argc, char* argv[]){
   
    SRunner* runner;
    srand((unsigned int) time(NULL));
    runner = srunner_create(suite_reverse());

    srunner_set_fork_status(runner, CK_FORK);
    srunner_run_all(runner, CK_NORMAL);
    int number_failed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}