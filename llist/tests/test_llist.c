#include <check.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "llist.h"

// testovacia funckcia, ktorá overuje správnosť implementácie funkcie FastCat() s plnením oboch LList(ov)
int random_FastCat_together(int LList_size){
    LList L0, L1;

    L0 = MakeEmpty( NULL );
    L1 = MakeEmpty( NULL );

    for(int counter = 0; counter < LList_size; counter++){ 
        InsertBeg( counter, L0 );
        InsertEnd( counter, L1 );
    }

    FastCat(L0,L1);

    PNode P = First(L0);
    if(!IsEmpty(L0) && LList_size == 0) return 1;
    else if(IsEmpty(L0) && LList_size != 0) return 1;
    if(!IsEmpty(L1) && LList_size == 0) return 1;
    else if(!IsEmpty(L1)) return 1;
    
    LList_size--;
    int first_loop = 0;         
    while(P != NULL){
        if(Get(P) != LList_size) return 1;
        
        if(LList_size != 0 && first_loop < 1) LList_size--;
        else first_loop++;
        
        if (first_loop > 1) LList_size++;
        P = Next(P); 
    }

    RemoveList(&L0);
    RemoveList(&L1);

    return 0;
}

// testovacia funckcia, ktorá overuje správnosť implementácie funkcie FastCat() s plnením jedného LList(u) 
int random_FastCat_one(int LList_size){
    LList L0,L1;

    L0 = MakeEmpty( NULL );
    L1 = MakeEmpty( NULL );

    for(int counter = 0; counter < LList_size; counter++ ) InsertBeg( counter, L0 );
    
    FastCat(L1,L0);

    PNode P = First(L0);
    if(!IsEmpty(L0)) return 1;
    if(!IsEmpty(L1) && LList_size == 0) return 1;
    else if(IsEmpty(L1) && LList_size != 0) return 1;
    
    LList_size--;
    int first_loop = 0;         
    while(P != NULL){
        if(Get(P) != LList_size) return 1;
        
        if(LList_size != 0 && first_loop < 1) LList_size--;
        else first_loop++;
        
        if (first_loop > 1) LList_size++;
        P = Next(P);
    }

    RemoveList(&L0);
    RemoveList(&L1);

    return 0;
}
// testovacia funckcia, ktorá overuje správnosť implementácie funkcie FreshCat() s plnením oboch LList(ov)
int random_freshCat_together(int LList_size){
    LList L0,L1,L2;

    L0 = MakeEmpty( NULL );
    L1 = MakeEmpty( NULL );
    L2 = MakeEmpty( NULL );

    
    for(int counter = 0; counter < LList_size; counter++ ){
        InsertBeg( counter, L0 );
        InsertEnd( counter, L1);
    }
    
    L2=FreshCat(L0,L1 );

    if(!IsEmpty(L0) && LList_size == 0) return 1;
    else if(IsEmpty(L0) && LList_size != 0) return 1;
    
    if(!IsEmpty(L1) && LList_size == 0) return 1;
    else if(IsEmpty(L1) && LList_size != 0) return 1;
    
    if(!IsEmpty(L2) && LList_size == 0) return 1;
    else if(IsEmpty(L2) && LList_size != 0) return 1;

    PNode P_L0 = First(L0);
    PNode P_L1 = First(L1);
    PNode P_L2 = First(L2);
        
    int first_loop = 0;         
    LList_size--;
    while(P_L2 != NULL){
        if(Get(P_L2) != LList_size) return 1;
        
        if(LList_size != 0 && first_loop < 1) LList_size--;
        else first_loop++;
        
        if (first_loop > 1) LList_size++;
        P_L2 = Next(P_L2);
    }

    LList_size--;
    while(P_L0 != NULL){
        if(Get(P_L0) != LList_size) return 1;
        P_L0 = Next(P_L0);
        LList_size--;
    }
    LList_size++;
    while(P_L1 != NULL){
        if(Get(P_L1) != LList_size) return 1;
        P_L1 = Next(P_L1);
        LList_size++;
    }
    
    RemoveList(&L0);
    RemoveList(&L1);
    RemoveList(&L2);

    return 0;
}
// testovacia funckcia, ktorá overuje správnosť implementácie funkcie FreshCat() s plnením jedného LList(u)
int random_FreshCat_one(int LList_size){
    LList L0,L1,L2;

    L0 = MakeEmpty( NULL );
    L1 = MakeEmpty( NULL );
    L2 = MakeEmpty( NULL );

    
    for(int counter = 0; counter < LList_size; counter++ ) InsertBeg( counter, L0 );
    
    
    L2=FreshCat(L0,L1 );

    if(!IsEmpty(L0) && LList_size == 0) return 1;
    else if(IsEmpty(L0) && LList_size != 0) return 1;
    
    if(!IsEmpty(L1)) return 1;
    
    if(!IsEmpty(L2) && LList_size == 0) return 1;
    else if(IsEmpty(L2) && LList_size != 0) return 1;

    PNode P_L0 = First(L0);
    PNode P_L2 = First(L2);
        
    LList_size--;
    while(P_L2 != NULL){
        if(Get(P_L2) != LList_size) return 1;
        if(Get(P_L0) != LList_size) return 1;            

        LList_size--;
        P_L2 = Next(P_L2);
        P_L0 = Next(P_L0);
    }
    
    RemoveList(&L0);
    RemoveList(&L1);
    RemoveList(&L2);

    return 0;
}
// testovacia funckcia, ktorá overuje správnosť implementácie funkcie Cut() jednorázovým alebo viacnásobným volaním funkcie Cut()
int random_Cut(int LList_size, int member){
    LList L0,L1;

    L0 = MakeEmpty( NULL );
    L1 = MakeEmpty( NULL );
    for(int i = 0; i < LList_size; i++ ) InsertBeg( i, L0 );
    
    PNode P1 = Member(member,L0);
    L1 = Cut(L0,P1);

    PNode P_L0, P_L1;
    P_L0 = First(L0);
    P_L1 = First(L1);

    LList_size--;
    while(P_L0 != NULL){
        if(Get(P_L0) != LList_size) return 1;            
        if(LList_size > member -1 ) LList_size--;        
        P_L0 = Next(P_L0);
    }
    while(P_L1 != NULL){
        if(Get(P_L1) != LList_size) return 1; 
        if((LList_size <= member -1) && LList_size > 0) LList_size--;        
        P_L1 = Next(P_L1);
    }

    RemoveList(&L0);
    RemoveList(&L1);
    return 0;
}

START_TEST(Test_funkcie_FastCat_s_LListmi_velkosti_NULL){
   // int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT);
   // dup2(file,STDOUT_FILENO);
    FastCat(NULL,NULL);
    
    FILE* fp = fopen("file.txt", "rb");
    char line[5000];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'FastCat(NULL,NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
   // remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_random){
    srand(getpid()); 
    int LList_size = rand() %100;
    ck_assert_msg(random_FastCat_together(LList_size) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = %d is FAILED' failed.",LList_size);
}
END_TEST


START_TEST(Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_1){
    ck_assert_msg(random_FastCat_together(1) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 1 is FAILED' failed.");
}
END_TEST


START_TEST(Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_10){
    ck_assert_msg(random_FastCat_together(10) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 10 is FAILED' failed.");
}
END_TEST


START_TEST(Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_0){
    ck_assert_msg(random_FastCat_together(0) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 0 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_random){
    srand(getpid()); 
    int LList_size = rand()%100;
    ck_assert_msg(random_FastCat_one(LList_size) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = %d is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_0){
    ck_assert_msg(random_FastCat_one(0) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 0 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_1){
    
    ck_assert_msg(random_FastCat_one(1) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 1 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_10){
    
    ck_assert_msg(random_FastCat_one(10) == 0, "Assertion 'FastCat(LList L1,LList L2) with LList size = 10 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_LListmi_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT);
    dup2(file,STDOUT_FILENO);
    FreshCat(NULL,NULL);
    
    FILE* fp = fopen("file.txt", "r");
    char line[5000];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'FreshCat(NULL,NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
    //remove("file.txt");
}
END_TEST


START_TEST(Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_random){
    srand(getpid()); 
    int LList_size = rand() %100;
    ck_assert_msg(random_freshCat_together(LList_size) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = %d is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_0){
    
    ck_assert_msg(random_freshCat_together(0) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 0 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_1){
    
    ck_assert_msg(random_freshCat_together(1) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 1 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_10){
    
    ck_assert_msg(random_freshCat_together(10) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 10 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_random){
    srand(getpid()); 
    int LList_size = rand() %100;
    ck_assert_msg(random_FreshCat_one(LList_size) == 0,"Assertion 'FreshCat(LList L1,LList L2) with LList size = %d is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_0){
    
    ck_assert_msg(random_FreshCat_one(1) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 0 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_1){
    
    ck_assert_msg(random_FreshCat_one(1) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 1 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_10){
    
    ck_assert_msg(random_FreshCat_one(10) == 0, "Assertion 'FreshCat(LList L1,LList L2) with LList size = 10 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_Cut_s_LListom_a_velkosti_NULL){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT);
    dup2(file,STDOUT_FILENO);
    Cut(NULL,NULL);
    
    FILE* fp = fopen("file.txt", "r");
    char line[5000];
    int value;
    
    fscanf(fp,"%s",line);
    
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'Cut(NULL,NULL) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
    //remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_random){
    srand(getpid());
    int LList_size = rand()%100;
    while(LList_size <= 1) LList_size = rand()%100;
    int member = rand()%(LList_size - 1);
    ck_assert_msg(random_Cut(LList_size,member) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = %d and PNode size = %d is FAILED' failed.",LList_size, member);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_0){
    srand(getpid());
    int LList_size = rand()%100;
    while(LList_size == 0) LList_size = rand()%100;
    ck_assert_msg( random_Cut(LList_size,0) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = %d and PNode size = 0 is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_1){
    srand(getpid());
    int LList_size = rand()%100;
    while(LList_size <= 1) LList_size = rand()%100;
    ck_assert_msg(random_Cut(LList_size,1) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = %d and PNode size = 1 is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_10){
    srand(getpid());
    int LList_size = rand()%100;
    while(LList_size <= 10) LList_size = rand()%100;

    ck_assert_msg(random_Cut(LList_size,10) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = %d and PNode size = 10 is FAILED' failed.",LList_size);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_10_a_smernikom_P_velkosti_random){
    srand(getpid());
    int member = rand()%9;
    ck_assert_msg( random_Cut(10,member) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = 10 and PNode size = %d is FAILED' failed.", member);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_50_a_smernikom_P_velkosti_random){
    srand(getpid());
    int member = rand()%49;
    ck_assert_msg( random_Cut(50,member) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = 50 and PNode size = %d is FAILED' failed.", member);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_100_a_smernikom_P_velkosti_random){
    srand(getpid());
    int member = rand()%99;
    ck_assert_msg( random_Cut(100,member) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = 100 and PNode size = %d is FAILED' failed.", member);
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_2_a_smernikom_P_velkosti_1){
    ck_assert_msg( random_Cut(2,1) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = 2 and PNode size = 1 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_2_a_smernikom_P_velkosti_0){
    ck_assert_msg( random_Cut(2,0) == 0,"Assertion 'Cut(LList L1,PNode P) with LList size = 2 and PNode size = 0 is FAILED' failed.");
}
END_TEST

START_TEST(Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_100_a_smernikom_P_velkosti_30){
    ck_assert_msg( random_Cut(100,30) == 0, "Assertion 'Cut(LList L1,PNode P) with LList size = 10 and PNode size = 3 is FAILED' failed.");
}
END_TEST


Suite* suite_reverse(void){

    Suite* suite = suite_create("Suite reverse()");
    TCase *tc;

    tc = tcase_create("3.1.0");
    tcase_add_test(tc, Test_funkcie_FastCat_s_LListmi_velkosti_NULL);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.1.1");
    tcase_add_loop_test(tc, Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_random,0,10);
    suite_add_tcase(suite, tc);
    
    tc = tcase_create("3.1.2");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_1);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.1.3");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.1.4");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_0);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.2.0");
    tcase_add_loop_test(tc,Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_random,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.2.1");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_0);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.2.2");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_1);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.2.3");
    tcase_add_test(tc,Test_funkcie_FastCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.3.0");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_LListmi_velkosti_NULL);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.3.1");
    tcase_add_loop_test(tc,Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_random,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.3.2");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_0);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.3.3");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_1);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.3.4");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_oboch_LListov_rovnako_s_LListmi_velkosti_10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.4.0");
    tcase_add_loop_test(tc,Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_random,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.4.1");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_0);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.4.2");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_1);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.4.3");
    tcase_add_test(tc,Test_funkcie_FreshCat_s_plnenim_jedneho_LListu_s_LListom_velkosti_10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.0");
    tcase_add_test(tc,Test_funkcie_Cut_s_LListom_a_velkosti_NULL);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.1");
    tcase_add_loop_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_random,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.2");
    tcase_add_loop_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_0,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.3");
    tcase_add_loop_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_1,0,10);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.4");
    tcase_add_loop_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_rendom_a_smernikom_P_velkosti_10,0,10);
    suite_add_tcase(suite, tc);
    
    tc = tcase_create("3.5.5");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_10_a_smernikom_P_velkosti_random);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.6");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_50_a_smernikom_P_velkosti_random);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.7");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_100_a_smernikom_P_velkosti_random);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.8");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_2_a_smernikom_P_velkosti_1);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.9");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_2_a_smernikom_P_velkosti_0);
    suite_add_tcase(suite, tc);

    tc = tcase_create("3.5.10");
    tcase_add_test(tc,Test_funkcie_Cut_s_plnenim_LListu_s_LListom_velkosti_100_a_smernikom_P_velkosti_30);
    suite_add_tcase(suite, tc);

    return suite;
}