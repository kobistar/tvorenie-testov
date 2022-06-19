#include <check.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wchar.h>
#include <locale.h>
#include "lstack.h"
#include "err.h"
struct Node
{
    PNode	Next;
    TElem	Elem;
};

struct LnkStack
{
    PNode	First;
    PNode	Last;
};

START_TEST(Test_funkcie_Top_s_LStask_velkosti_NULL){
    char line[5000];
    int value;
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    Top(NULL);
    
    FILE* fp = fopen("file.txt", "r");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Top(NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
}
END_TEST

START_TEST(Test_funkcie_Top_s_velkostou_LStack_5_s_random_clenmi){
    LStack S = CreateStack();
    srand(getpid());
    int member;
    for(int counter =1; counter <= 5; counter++){
        member = rand()%100;
        Push(member,S);
    }
    
    ck_assert_msg(S->First->Elem == member,"Assertion 'Top(LStack S) = %d with LStack size = 5 is FAILED' failed.",member);
    RemoveStack(&S);
}
END_TEST


START_TEST(Test_funkcie_Top_s_velkostou_LStack_5_s_pevnymi_clenmi){
    LStack S = CreateStack();
    for(int counter = 1; counter <= 5; counter++) Push(counter,S);

    ck_assert_msg(S->First->Elem == 5, "Assertion 'Top(LStack S) = 5 with LStack size = 5 is FAILED' failed.");
    RemoveStack(&S);
}
END_TEST


START_TEST(Test_funkcie_Top_s_velkostou_LStack_random_s_random_clenmi){
    LStack S = CreateStack();
    srand(getpid());

    int random_member;
    int LStack_size = rand()%100;
    while(LStack_size == 0)LStack_size = rand()%100;

    for(int counter = 1; counter <= LStack_size; counter++){
        random_member = rand()%100;
        Push(random_member,S);
    }
    ck_assert_msg( Top(S) == random_member, "Assertion 'Top(LStack S) = %d with LStack size = %d is FAILED' failed.", random_member, LStack_size);
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_Top_s_velkostou_LStack_0_s_0_clenmi){
    LStack S = CreateStack();
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    Top(S);    
    FILE* fp = fopen("file.txt", "r");

    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Top(LStack S) = Pop: empty stack with LStack size = 0 is FAILED because your print was %s' failed.", line);
    fclose(fp);
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_Pop_s_LStask_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    dup2(file,STDOUT_FILENO);
    Pop(NULL);    
    
    FILE* fp = fopen("file.txt", "r");
    if(fp == NULL) exit(0);
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Pop(NULL) = Error is FAILED because your print was %s' failed.", line);   
    
    fclose(fp);
}END_TEST

START_TEST(Test_funkcie_Pop_s_velkostou_LStack_0_s_0_clenmi){
    LStack S = CreateStack();
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    Pop(S);    
    
    FILE* fp = fopen("file.txt", "r");

    fscanf(fp,"%s",line);
    value = strcmp( line, "Error");
    ck_assert_msg(value == 0, "Assertion 'Pop(LStack S) = Pop: empty stack with LStack size = 0 is FAILED because your print was %s' failed.", line);
    fclose(fp);
}END_TEST

START_TEST(Test_funkcie_Pop_s_velkostou_LStack_1_s_pevnym_clenom){
    LStack S = CreateStack();
    Push(0,S);
    Pop(S);
    ck_assert_msg(IsEmptyStack(S), "Assertion 'Pop(LStack S) = 1 with LStack size = 1 is FAILED' failed.");
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_Pop_s_velkostou_LStack_5_s_pevnymi_clenmi){
    LStack S = CreateStack();
    for(int counter = 1; counter <= 5; counter++) Push(counter,S);

    Pop(S);
    ck_assert_msg(S->First->Elem == 4, "Assertion 'Pop(LStack S) = 5 with LStack size = 5 is FAILED' failed.");
    RemoveStack(&S);

}END_TEST


START_TEST(Test_funkcie_Pop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_trojnasobnym_volanim_Pop){
    LStack S0,S1;
    S0 = CreateStack();
    S1 = CreateStack();
    int counter;
    for(counter = 1; counter <= 10; counter++){
        Push(counter,S0);
        Push(counter,S1); 
    }

    for(counter = 1; counter <= 3; counter++){
        PNode PT = S1->First;
        if(S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);
        Pop(S0);
    }

    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'Pop(LStack S) = %d with LStack size = 10 is FAILED' failed.",S1->First->Elem);
    RemoveStack(&S0);
    RemoveStack(&S1);
}END_TEST


START_TEST(Test_funkcie_Pop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_viacnasobnym_volanim_Pop){
    LStack S0,S1;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());
    int counter;
    int replay = rand()%9;

    for(counter = 1; counter <= 10; counter++){
        Push(counter,S0);
        Push(counter,S1); 
    }

    for(counter = 1; counter <= replay; counter++){
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);
        Pop(S0);
    }

    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'Pop(LStack S) = %d with LStack size = 10 is FAILED' failed.",S1->First->Elem);
    RemoveStack(&S0);
    RemoveStack(&S1);

}END_TEST

START_TEST(Test_funkcie_Pop_s_velkostou_LStack_random_s_random_clenmi_a_viacnasobnym_volanim_Pop){
    LStack S0,S1;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());
    int LStask_size = rand()%100;
    int counter;
    int random_number;
    while(LStask_size <= 1) LStask_size = rand()%100;
    
    for(int counter = 1; counter <= LStask_size; counter++){
        random_number = rand()%100;
        Push(random_number,S0);
        Push(random_number,S1); 
    }
    int replay = rand()%(LStask_size - 1);
    for(counter = 1; counter <= replay; counter++){
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);
        Pop(S0);
    }

    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'Pop(LStack S) = %d with LStack size = %d is FAILED' failed.",S1->First->Elem, LStask_size);
    RemoveStack(&S0);
    RemoveStack(&S1);

}END_TEST

START_TEST(Test_funkcie_Pop_s_velkostou_LStack_random_s_pevnymi_clenmi_a_trojnasobnym_volanim_Pop){
  LStack S0,S1;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());
    int counter;
    int LStack_size = rand()%100;
    while(LStack_size <= 3)LStack_size = rand()%100;
    
    for(counter = 1; counter <= LStack_size; counter++){
        Push(counter,S0);
        Push(counter,S1); 
    }

    for(counter = 1; counter <= 3; counter++){
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);
        Pop(S0);
    }

    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'Pop(LStack S) = %d with LStack size = %d is FAILED' failed.",S1->First->Elem, LStack_size);
    RemoveStack(&S0);
    RemoveStack(&S1);

}END_TEST


START_TEST(Test_funkcie_Pop_s_velkostou_LStack_random_a_pevnymi_clenmi){

    LStack S0,S1;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());
    int LStack_size = rand()%100;
    while(LStack_size <= 1) LStack_size = rand()%100;
    
    for(int counter = 1; counter <= LStack_size; counter++){
        Push(counter,S0);
        Push(counter,S1); 
    }

    PNode PT = S1->First;
    if( S1->First == S1->Last) S1->Last = NULL;
    S1->First = S1->First->Next;
    free(PT);
    Pop(S0);

    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'Pop(LStack S) = %d with LStack size = %d is FAILED' failed.",S1->First->Elem, LStack_size);
    RemoveStack(&S0);
    RemoveStack(&S1);

}END_TEST


START_TEST(Test_funkcie_TopAndPop_s_LStask_velkosti_NULL){
   int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[5];
    int value;
    
    dup2(file,STDOUT_FILENO);
    TopAndPop(NULL);    
    
    FILE* fp = fopen("file.txt", "r");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'TopAndPop(NULL) = Error is FAILED because your print was %s' failed.", line);   
    fclose(fp);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_0_a_pevnymi_clenmi){
    LStack S = CreateStack();
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT,0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    TopAndPop(S);    
    
    FILE* fp = fopen("file.txt", "r");
    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");

    ck_assert_msg(value == 0, "Assertion 'TopAndPop(LStack S) = Pop: empty stack with LStack size = 0 is FAILED because your print was %s' failed.", line);   
    fclose(fp);
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_10_a_pevnymi_clenmi){
    LStack S = CreateStack();

    for( int counter = 1; counter <= 10; counter++) Push(counter,S);
    
    int deleteNumber = TopAndPop(S);
    ck_assert_msg(deleteNumber == 10, "Assertion 'TopAndPop(LQueue Q) = 10 with LQueue size = 10 is FAILED' failed.");
    ck_assert_msg(S->First->Elem == 9, "Assertion 'TopAndPop(LQueue Q) = 9 with LQueue size = 10 is FAILED' failed.");
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_2_a_pevnymi_clenmi){
    LStack S = CreateStack();
    
    for( int counter =1; counter <= 2; counter++) Push(counter,S);

    int deleteNumber = TopAndPop(S);
    ck_assert_msg(deleteNumber == 2, "Assertion 'TopAndPop(LQueue Q) = 2 with LQueue size = 2 is FAILED' failed.");
    
    ck_assert_msg(!IsEmptyStack(S) && S->First->Elem == 1, "Assertion 'TopAndPop(LQueue Q) = 1 with LQueue size = 2 is FAILED' failed.");
    RemoveStack(&S);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_trojnasobnym_volanim_TopAndPop){
    LStack S0,S1;
    int counter;
    int deleteNumber;
    S0 = CreateStack();
    S1 = CreateStack();

    for(counter =1; counter <= 10; counter++){
        Push(counter,S0);
        Push(counter,S1);
    }

    for(counter =1; counter <= 3; counter++){
        deleteNumber = TopAndPop(S0);
        ck_assert_msg(deleteNumber == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", deleteNumber);
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);
    }
        
    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", deleteNumber);
    RemoveStack(&S0);
    RemoveStack(&S1);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_viacnasobnym_volanim_TopAndPop){
    LStack S0,S1;
    int counter;
    int deleteNumber;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());

    for(counter = 1; counter <= 10; counter++){
        Push(counter,S0);
        Push(counter,S1);
    }
    int replay = rand()%9;

    for(counter = 1; counter <= replay; counter++){
        deleteNumber = TopAndPop(S0);
        ck_assert_msg(deleteNumber == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", deleteNumber);
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT); 
    }
        
    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", S0->First->Elem);
    RemoveStack(&S0);
    RemoveStack(&S1);
}
END_TEST

START_TEST(Test_funkcie_TopAndPop_s_velkostou_LStack_random_s_random_clenmi_a_viacnasobnym_volanim_TopAndPop){
    LStack S0,S1;
    int counter;
    int deleteNumber;
    int random_number;
    S0 = CreateStack();
    S1 = CreateStack();
    srand(getpid());

    int LStak_size = rand()%100;
    while(LStak_size < 2) LStak_size = rand()%100;
    
    for(counter = 1; counter <= LStak_size; counter++){
        random_number = rand()%100;
        Push(random_number,S0);
        Push(random_number,S1);
    }
    
    int replay = rand()%(LStak_size - 1);
    for(counter = 1; counter <= replay; counter++){
        deleteNumber = TopAndPop(S0);
        
        ck_assert_msg(deleteNumber == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", deleteNumber);
        PNode PT = S1->First;
        if( S1->First == S1->Last) S1->Last = NULL;
        S1->First = S1->First->Next;
        free(PT);  
    }
        
    ck_assert_msg(S0->First->Elem == S1->First->Elem, "Assertion 'TopAndPop(LQueue Q) = %d with LQueue size = 10 is FAILED' failed.", S0->First->Elem);
    RemoveStack(&S0);
    RemoveStack(&S1);
}
END_TEST

Suite* suite_reverse(void){

    Suite* suite = suite_create("Suite reverse()");
    TCase *tc;

    tc = tcase_create("4.1.0");
    tcase_add_test(tc, Test_funkcie_Top_s_LStask_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.1.1");
    tcase_add_loop_test(tc, Test_funkcie_Top_s_velkostou_LStack_5_s_random_clenmi,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.1.2");
    tcase_add_test(tc, Test_funkcie_Top_s_velkostou_LStack_5_s_pevnymi_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.1.3");
    tcase_add_loop_test(tc, Test_funkcie_Top_s_velkostou_LStack_random_s_random_clenmi,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.1.4");
    tcase_add_test(tc,Test_funkcie_Top_s_velkostou_LStack_0_s_0_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.0");
    tcase_add_test(tc,Test_funkcie_Pop_s_LStask_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.1");
    tcase_add_test(tc,Test_funkcie_Pop_s_velkostou_LStack_0_s_0_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.2");
    tcase_add_test(tc,Test_funkcie_Pop_s_velkostou_LStack_1_s_pevnym_clenom);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("4.2.3");
    tcase_add_test(tc,Test_funkcie_Pop_s_velkostou_LStack_5_s_pevnymi_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.4");
    tcase_add_test(tc,Test_funkcie_Pop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_trojnasobnym_volanim_Pop);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("4.2.5");
    tcase_add_loop_test(tc,Test_funkcie_Pop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_viacnasobnym_volanim_Pop,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.6");
    tcase_add_loop_test(tc,Test_funkcie_Pop_s_velkostou_LStack_random_s_random_clenmi_a_viacnasobnym_volanim_Pop,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.7");
    tcase_add_loop_test(tc,Test_funkcie_Pop_s_velkostou_LStack_random_s_pevnymi_clenmi_a_trojnasobnym_volanim_Pop,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.2.8");
    tcase_add_loop_test(tc,Test_funkcie_Pop_s_velkostou_LStack_random_a_pevnymi_clenmi,0,10);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("4.3.0");
    tcase_add_test(tc,Test_funkcie_TopAndPop_s_LStask_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.3.1");
    tcase_add_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_0_a_pevnymi_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.3.2");
    tcase_add_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_10_a_pevnymi_clenmi);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("4.3.3");
    tcase_add_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_2_a_pevnymi_clenmi);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.3.4");
    tcase_add_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_trojnasobnym_volanim_TopAndPop);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.3.5");
    tcase_add_loop_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_10_s_pevnymi_clenmi_a_viacnasobnym_volanim_TopAndPop,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("4.3.6");
    tcase_add_loop_test(tc,Test_funkcie_TopAndPop_s_velkostou_LStack_random_s_random_clenmi_a_viacnasobnym_volanim_TopAndPop,0,10);
    suite_add_tcase(suite,tc);

    return suite;
}