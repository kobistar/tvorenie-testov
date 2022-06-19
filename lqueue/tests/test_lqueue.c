#include <check.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wchar.h>
#include <locale.h>
#include "lqueue.h"
#include "err.h"
struct Node{
    PNode	Next;
    TElem	Elem;
};

struct LnkQueue{
    PNode	Front;
    PNode	Rear;
};

START_TEST(Test_funkcie_Front_s_LQueue_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    Front(NULL);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Front(NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
}
END_TEST

START_TEST(Test_funckie_Front_s_volanim_prazdneho_LQueue){
    LQueue Q;
    Q = CreateQueue();
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    Front(Q);
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Front(LQueue) = Error with LQueue_size = NULL is FAILED because your print was %s' failed.", line);
    fclose(fp);

}END_TEST

START_TEST(Test_funkcie_Front_s_velkostou_LQueue_10_a_pevne_danymi_cislami){
    LQueue Q;
    int counter;
    Q = CreateQueue();

    for(counter = 0; counter < 10; counter++) Enqueue(counter,Q);
    
    ck_assert_msg(Front(Q) == 0, "Assertion 'Front(LQueue Q) = 0 with LQueue size = 10 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_Front_s_velkostou_LQueue_10_a_random_cislami){
    LQueue Q;
    int number;
    int first_number;
    Q = CreateQueue();
    srand(getpid());

    for(int counter = 0; counter < 10; counter++){ 
        number  = rand()%100;
        if(counter == 0) first_number = number;
        Enqueue(number,Q);
    }
    ck_assert_msg(Front(Q) == first_number, "Assertion 'Front(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",first_number);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Front_s_velkostou_LQueue_random_a_random_cislami){
    LQueue Q;
    int number;
    int first_number;
    Q = CreateQueue();
    srand(getpid());

    int LQueue_size = rand()%100;
    while(LQueue_size == 0) LQueue_size = rand()%100;

    for(int counter = 0; counter < LQueue_size; counter++){
        number = rand()%100;
        if(counter == 0) first_number = number;
        Enqueue(number,Q);
    }

    ck_assert_msg(Front(Q) == first_number, "Assertion 'Front(LQueue Q) = %d with LQueue size = %d is FAILED' failed.",first_number, LQueue_size);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Front_s_velkostou_LQueue_1_a_danym_cislom){
    LQueue Q;
    Q = CreateQueue();
    Enqueue(0,Q);

    ck_assert_msg(Front(Q) == 0, "Assertion 'Front(LQueue Q) = 0 with LQueue size = 1 is FAILED' failed.");
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Front_s_velkostou_LQueue_1_a_jednym_random_cislom){
    LQueue Q;
    srand(getpid());
    Q = CreateQueue();
    
    int random_number = rand()%100;
    Enqueue(random_number,Q);
    ck_assert_msg(Front(Q) == random_number, "Assertion 'Front(LQueue Q) = %d with LQueue size = 1 is FAILED' failed.",random_number);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_LQueue_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    Dequeue(NULL);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Dequeue(NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);

}END_TEST

START_TEST(Test_funckie_Dequeue_s_volanim_prazdneho_LQueue){
    LQueue Q;
    Q = CreateQueue();
    setlocale(LC_ALL, "sk_SK.UTF-8");
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    Dequeue(Q);    
    
    FILE* fp = fopen("file.txt", "r");
    if(fp == NULL) exit(0);
    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Dequeue(LQueue) = Error with LQueue_size = NULL is FAILED because your print was %s' failed.", line);
    fclose(fp);
}END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_a_pevne_danymi_cislami){
    LQueue Q;
    Q = CreateQueue();
    for(int counter = 0; counter < 10; counter++){
        Enqueue(counter,Q);
    }
    Dequeue(Q);

    ck_assert_msg(Q->Front->Elem == 1, "Assertion 'Dequeue(LQueue Q) = 1 with LQueue size = 10 is FAILED' failed.");
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_a_random_cislami){
    LQueue Q;
    int number;
    int second_number;
    srand(getpid());
    Q = CreateQueue();

    for(int counter = 0; counter < 10; counter++){
        number = rand()%100;
        if(counter == 1) second_number = number;
        Enqueue(number,Q);
    }
    Dequeue(Q);
    ck_assert_msg(Q->Front->Elem == second_number,"Assertion 'Dequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",second_number);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_random_a_random_cislami){
    LQueue Q;
    int number;
    int second_number;
    Q = CreateQueue();
    srand(getpid());

    int LQueue_size = rand()%100;
    while(LQueue_size < 2) LQueue_size = rand()%100;

    for(int counter = 0; counter < LQueue_size; counter++){
        number = rand()%100;
        if(counter == 1) second_number = number;
        Enqueue(number,Q);
    }
    Dequeue(Q);
    ck_assert_msg(Q->Front->Elem == second_number, "Assertion 'Dequeue(LQueue Q) = %d with LQueue size = %d is FAILED' failed.",second_number, LQueue_size);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_1_a_danym_cislom){
    LQueue Q;
    Q = CreateQueue();
    Enqueue(0,Q);
    Dequeue(Q);
    ck_assert_msg(IsEmptyQueue(Q), "Assertion 'Dequeue(LQueue Q) = 0 with LQueue size = 1 is FAILED' failed.");
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_1_a_random_cislom){
    LQueue Q;
    srand(getpid());
    Q = CreateQueue();

    int random_number = rand()%100;
    Enqueue(random_number,Q);
    Dequeue(Q);
    ck_assert_msg(IsEmptyQueue(Q), "Assertion 'Dequeue(LQueue Q) = %d with LQueue size = 1 is FAILED' failed.",random_number);
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_trojnasobnym_volanim_Dequeue){
    LQueue Q1, Q2;
    PNode PT;
    int counter;
    Q1 = CreateQueue();
    Q2 = CreateQueue();

    for(counter = 0; counter < 10; counter++){
        Enqueue(counter,Q1);
        Enqueue(counter,Q2);
    }
    
    for(counter = 0; counter < 3; counter++){
        Dequeue(Q1);
        PT = Q2->Front;
        if( Q2->Front == Q2->Rear) Q2->Rear = NULL;
        Q2->Front = Q2->Front->Next;
        free(PT);
    }
    ck_assert_msg(Q1->Front->Elem == Q2->Front->Elem, "Assertion Dequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed", Q2->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_vianasobnym_random_volanim_Dequeue){
    LQueue Q1, Q2;
    PNode PT;
    srand(getpid());
    int replay = rand()%9;
    int counter;
    
    Q1 = CreateQueue();
    Q2 = CreateQueue();
    
    for(counter = 0; counter < 10; counter++){
        Enqueue(counter,Q1);
        Enqueue(counter,Q2);
    }
    for(counter = 0; counter < replay; counter++){
        Dequeue(Q1);
        PT = Q2->Front;
        if( Q2->Front == Q2->Rear) Q2->Rear = NULL;
        Q2->Front = Q2->Front->Next;
        free(PT);
    }
    ck_assert_msg(Q1->Front->Elem == Q2->Front->Elem, "Assertion Dequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed", Q2->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_random_cislami_a_trojnasobnym_volanim_Dequeue){
    LQueue Q1, Q2;
    PNode PT;
    srand(getpid());
    int random_number;
    int counter;
    
    Q1 = CreateQueue();
    Q2 = CreateQueue();

    for(counter = 0; counter < 10; counter++){
        random_number = rand()%100;
        Enqueue(random_number,Q1);
        Enqueue(random_number,Q2);
    }
    for(counter = 0; counter < 3; counter++){
        Dequeue(Q1);
        PT = Q2->Front;
        if( Q2->Front == Q2->Rear) Q2->Rear = NULL;
        Q2->Front = Q2->Front->Next;
        free(PT);
    }
    ck_assert_msg(Q1->Front->Elem == Q2->Front->Elem, "Assertion Dequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed", Q2->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_random_cislami_a_vianasobnym_random_volanim_Dequeue){
    LQueue Q1, Q2;
    PNode PT;
    srand(getpid());

    int random_number;
    int counter;
    int replay = rand()% 9;
     
    Q1 = CreateQueue();
    Q2 = CreateQueue();
    
    for(counter = 0; counter < 10; counter++){
        random_number = rand()%100;
        Enqueue(random_number,Q1);
        Enqueue(random_number,Q2);
    }
    for(counter = 0; counter < replay; counter++){
        Dequeue(Q1);
        PT = Q2->Front;
        if( Q2->Front == Q2->Rear) Q2->Rear = NULL;
        Q2->Front = Q2->Front->Next;
        free(PT);
    }
    ck_assert_msg(Q1->Front->Elem == Q2->Front->Elem, "Assertion Dequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed", Q2->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);
}
END_TEST

START_TEST(Test_funkcie_Dequeue_s_random_velkostou_LQueue_s_random_cislami_a_vianasobnym_random_volanim_Dequeue){
    LQueue Q1, Q2;
    PNode PT;
    srand(getpid());
    int random_number;
    int counter;

    Q1 = CreateQueue();
    Q2 = CreateQueue();

    int LQueue_size = rand()%100;
    while(LQueue_size < 2) LQueue_size = rand()%100;

    for(counter = 0; counter < LQueue_size; counter++){
        random_number = rand()%100;
        Enqueue(random_number,Q1);
        Enqueue(random_number,Q2);
    }
    int replay = rand()%(LQueue_size - 1);

    for(counter = 0; counter < replay; counter++){
        Dequeue(Q1);
        PT = Q2->Front;
        if( Q2->Front == Q2->Rear) Q2->Rear = NULL;
        Q2->Front = Q2->Front->Next;
        free(PT);
    }
    ck_assert_msg(Q1->Front->Elem == Q2->Front->Elem, "Assertion Dequeue(LQueue Q) = %d with LQueue size = %d is FAILED' failed", Q2->Front->Elem, LQueue_size);
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);
}
END_TEST


START_TEST(Test_funkcie_FrontAndDequeue_s_LQueue_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    FrontAndDequeue(NULL);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'FrontAndDequeue(NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);

}END_TEST

START_TEST(Test_funckie_FrontAndDequeue_s_volanim_prazdneho_LQueue){
    LQueue Q;
    Q = CreateQueue();
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[10];
    int value;
    
    dup2(file,STDOUT_FILENO);
    FrontAndDequeue(Q);   
    
    FILE* fp = fopen("file.txt", "r");
    if(fp == NULL) exit(0);
    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'FrontAndDequeue(LQueue) = Error with LQueue_size = NULL is FAILED because your print was %s' failed.", line);
    fclose(fp);

}END_TEST

START_TEST(Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_a_pevne_danymi_cislami){
    LQueue Q;
    
    Q = CreateQueue();

    for( int counter = 1; counter <= 10; counter++) Enqueue(counter,Q);
    int delete_number = FrontAndDequeue(Q);
    
    ck_assert_msg(delete_number == 1, "Assertion 'FrontAndDequeue(LQueue Q) = 1 with LQueue size = 10 is FAILED' failed.");
    ck_assert_msg(Q->Front->Elem == 2, "Assertion 'FrontAndDequeue(LQueue Q) = 2 with LQueue size = 10 is FAILED' failed.");
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_2_a_pevne_danymi_cislami){
    LQueue Q;
    Q = CreateQueue();
    
    for(int counter =1; counter <= 2; counter++) Enqueue(counter,Q);

    int delete_number = FrontAndDequeue(Q);
    ck_assert_msg(delete_number == 1, "Assertion 'FrontAndDequeue(LQueue Q) = 1 with LQueue size = 10 is FAILED' failed.");
    ck_assert_msg(!IsEmptyQueue(Q) && Q->Front->Elem == 2, "Assertion 'FrontAndDequeue(LQueue Q) = 2 with LQueue size = 10 is FAILED' failed.");
    RemoveQueue(&Q);
}
END_TEST

START_TEST(Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_trojnasobnym_volanim_FrontAndDequeue){
    LQueue Q0, Q1;
    int counter;
    
    Q0 = CreateQueue();
    Q1 = CreateQueue();

    for(counter = 1; counter <= 10; counter++){
        Enqueue(counter,Q0);
        Enqueue(counter,Q1);
    }

    for(counter = 1; counter <= 3; counter++){
        int delete_number = FrontAndDequeue(Q0);
        ck_assert_msg(delete_number == Q1->Front->Elem, "Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q1->Front->Elem);
        PNode PT = Q1->Front;
        if( Q1->Front == Q1->Rear) Q1->Rear = NULL;
        Q1->Front = Q1->Front->Next;
        free(PT);   
    }
        
    ck_assert_msg(Q0->Front->Elem == Q1->Front->Elem,"Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q0->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q0);
}
END_TEST

START_TEST(Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_viacnasobnym_random_volanim_FrontAndDequeue){
    LQueue Q0,Q1;
    int counter;
    int delete_number;
    Q0 = CreateQueue();
    Q1 = CreateQueue();
    srand(getpid());

    for( counter = 1; counter <= 10; counter++){
        Enqueue(counter,Q0);
        Enqueue(counter,Q1);
    }
    int replay = rand()%9;

    for( counter = 1; counter <= replay; counter++){
        delete_number = FrontAndDequeue(Q0);
        ck_assert_msg(delete_number == Q1->Front->Elem,  "Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q1->Front->Elem);
        PNode PT = Q1->Front;
        if( Q1->Front == Q1->Rear) Q1->Rear = NULL;
        Q1->Front = Q1->Front->Next;
        free(PT);   
    }
        
    ck_assert_msg(Q0->Front->Elem == Q1->Front->Elem, "Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q0->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q0);

}
END_TEST

START_TEST(Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_random_s_danymi_cislami_a_viacnasobnym_random_volanim_FrontAndDequeue){
    LQueue Q0,Q1;
    int counter;
    int random_number;
    int delete_number;
    int LQueue_size = rand()%100;

    Q0 = CreateQueue();
    Q1 = CreateQueue();
    srand(getpid());
    
    while(LQueue_size < 2) LQueue_size = rand()%100;
    for( counter = 1; counter <= LQueue_size; counter++){
        random_number = rand()%100;
        Enqueue(random_number,Q0);
        Enqueue(random_number,Q1);
    }
    int replay = rand()%(LQueue_size - 1);

    for( counter = 1; counter <= replay; counter++){
        delete_number = FrontAndDequeue(Q0);
        ck_assert_msg(delete_number == Q1->Front->Elem, "Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q1->Front->Elem);
        PNode PT = Q1->Front;
        if( Q1->Front == Q1->Rear) Q1->Rear = NULL;
        Q1->Front = Q1->Front->Next;
        free(PT);  
    }
        
    ck_assert_msg(Q0->Front->Elem == Q1->Front->Elem, "Assertion 'FrontAndDequeue(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.",Q0->Front->Elem);
    RemoveQueue(&Q1);
    RemoveQueue(&Q0);
}
END_TEST

Suite* suite_reverse(void){

    Suite* suite = suite_create("Suite reverse()");
    TCase *tc;

    tc = tcase_create("4.4.0");
    tcase_add_test(tc,Test_funkcie_Front_s_LQueue_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.4.1");
    tcase_add_test(tc,Test_funckie_Front_s_volanim_prazdneho_LQueue);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.4.2");
    tcase_add_test(tc,Test_funkcie_Front_s_velkostou_LQueue_10_a_pevne_danymi_cislami);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.4.3");
    tcase_add_loop_test(tc,Test_funkcie_Front_s_velkostou_LQueue_10_a_random_cislami,0,20);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("4.4.4");
    tcase_add_loop_test(tc,Test_funkcie_Front_s_velkostou_LQueue_random_a_random_cislami,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.4.5");
    tcase_add_test(tc,Test_funkcie_Front_s_velkostou_LQueue_1_a_danym_cislom);
    suite_add_tcase(suite,tc);

     tc = tcase_create("4.4.6");
    tcase_add_test(tc,Test_funkcie_Front_s_velkostou_LQueue_1_a_jednym_random_cislom);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.0");
    tcase_add_test(tc,Test_funkcie_Dequeue_s_LQueue_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.1");
    tcase_add_test(tc,Test_funckie_Dequeue_s_volanim_prazdneho_LQueue);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.2");
    tcase_add_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_a_pevne_danymi_cislami);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.3");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_a_random_cislami,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.4");
    tcase_add_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_1_a_danym_cislom);
    suite_add_tcase(suite,tc);

     tc = tcase_create("4.5.5");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_random_a_random_cislami,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.6");
    tcase_add_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_1_a_random_cislom);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.7");
    tcase_add_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_trojnasobnym_volanim_Dequeue);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.8");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_vianasobnym_random_volanim_Dequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.9");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_random_cislami_a_trojnasobnym_volanim_Dequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.10");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_velkostou_LQueue_10_s_random_cislami_a_vianasobnym_random_volanim_Dequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.5.11");
    tcase_add_loop_test(tc,Test_funkcie_Dequeue_s_random_velkostou_LQueue_s_random_cislami_a_vianasobnym_random_volanim_Dequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.0");
    tcase_add_test(tc,Test_funkcie_FrontAndDequeue_s_LQueue_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.1");
    tcase_add_test(tc,Test_funckie_FrontAndDequeue_s_volanim_prazdneho_LQueue);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.2");
    tcase_add_test(tc,Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_a_pevne_danymi_cislami);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.3");
    tcase_add_test(tc,Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_2_a_pevne_danymi_cislami);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.4");
    tcase_add_loop_test(tc,Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_trojnasobnym_volanim_FrontAndDequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.5");
    tcase_add_loop_test(tc,Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_10_s_danymi_cislami_a_viacnasobnym_random_volanim_FrontAndDequeue,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.6.6");
    tcase_add_loop_test(tc,Test_funkcie_FrontAndDequeue_s_velkostou_LQueue_random_s_danymi_cislami_a_viacnasobnym_random_volanim_FrontAndDequeue,0,20);
    suite_add_tcase(suite,tc);
   
    return suite;
}