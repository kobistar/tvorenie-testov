#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <time.h>
#include "err.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "tree_arr.h"
#define COUNTER 20

struct TreeRecord
       {
            int MaxLevel;
            int *Array;
       };

START_TEST(Test_funkcie_PrintRow_s_volanim_Tree_velkosti_NULL_a_indexu_0){
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    PrintRow(NULL,0);   
    FILE* fp = fopen("file.txt", "r");
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'PrintRow(NULL,0) = Error is FAILED because your print was %s' failed.", line);  
    fclose(fp);
    remove("file.txt");
}END_TEST

START_TEST(Test_funkcie_PrintRow_s_volanim_Tree_velkosti_1_a_indexu_30){
    Tree T = CreateTree(3);
    MakeEmpty(T);
    for(int counter = 1; counter < 16; counter++) Insert(T,counter,4 + counter);

    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    PrintRow(T,30);   
    
    FILE* fp = fopen("file.txt", "r");
    if(fp == NULL) exit(0);
    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'PrintRow(NULL,0) = Error is FAILED because your print was %s' failed.", line);
    fclose(fp);
    remove("file.txt");
}END_TEST


START_TEST(Test_na_PrintRow_velkost_stromu_3_vypis_3_levelu){
    char *array[] = {"12","13","14","15","16","17","18","19"};
    Tree T = CreateTree(3);
    int counter;
    for(counter = 1; counter < 16; counter++) Insert(T,counter,4 + counter);

    PrintRow(T,3);
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);

    dup2(file,STDOUT_FILENO);
    close(file);
    
    FILE* fp = fopen("file.txt", "r");
    
    char line[100];
    int value;
    printf("\n");
    for(counter = 0; counter < 8; counter++){
        fscanf(fp,"%s",line);
        value = strcmp(line,array[counter]);
        ck_assert_msg(value == 0, "Assertion 'PrintRow(Tree T, int level) == %s pole[x]' failed.", array[counter]);   
    }
    fclose(fp);
    DisposeTree(T);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintRow_velkosti_stromu_10_vypis_random_levelu){
    int maxlevel = 10;
    srand(getpid());
    int level = rand()%maxlevel;
    int counter;
    Tree T1 = CreateTree( maxlevel );
    char array[5000];
    for(counter = 1; counter < pow(2,maxlevel+1); counter++) Insert(T1,counter,4 + counter);    
    for(counter = pow(2,level); counter < pow(2,level+1); counter++) sprintf(array,"%d",4 + counter);
    
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    PrintRow(T1,level);
    
    close(file);
    
    FILE* fp = fopen("file.txt", "r");
    
    char line[5000];
    int value;
    printf("\n");
    counter = pow(2,level) + 4;
    for(int counter2 = 0; counter2 < pow(2,level); counter2++){
        fscanf(fp,"%s",line);
        sprintf(array,"%02d",counter);
        value = strcmp(line,array);
        ck_assert_msg(value == 0, "Assertion 'line %s != %s pole[%d]' failed.", line,array, counter2);
        counter++;   
    }
    fclose(fp);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintRow_s_velkostou_stromu_random_vypis_random_levelu){
    srand(getpid());
    int maxlevel = rand()%10;
    int level;

    if(maxlevel == 0) level = 0;
    else level = rand()%maxlevel;
    
    int counter;
    Tree T1 = CreateTree(maxlevel);
    char array[5000];
    for(counter = 1; counter < pow(2,maxlevel+1); counter++) Insert(T1,counter,counter + 4);    

    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    PrintRow(T1,level);
    close(file);
    
    FILE* fp = fopen("file.txt", "r");
    
    char line[5000];
    int value;
    printf("\n");
    counter = pow(2,level)+4;

    for(int counter2 = 0; counter2 < pow(2,level); counter2++){
        fscanf(fp,"%s",line);
        sprintf(array,"%02d",counter);
        value = strcmp(line,array);
        ck_assert_msg(value == 0, "Assertion 'line %s != %s pole[%d]' failed.", line,array, counter2);
        counter++;   
    }
    fclose(fp);
    remove("file.txt");
}
END_TEST


START_TEST(Test_funkcie_PrintRow_s_velkostou_stromu_0_a_vypisom_0_levelu){
    Tree T = CreateTree(0);
    Insert(T,1,5);
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    PrintRow(T,0);

    FILE* fp = fopen("file.txt", "r");
    char line[10];
    int value;
    printf("\n");
    fscanf(fp,"%s",line);
    value = strcmp(line,"05");
    ck_assert_msg(value == 0, "Assertion 'line %s != 05' failed.", line);   
    
    fclose(fp);
    DisposeTree(T);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintSubtree_velkosti_3_podstromom_3){
    int counter;
    char array[500];
    int level = 0;
    char line[500];
    int value;
    
    //vytvorenie struktury
    Tree T1 = CreateTree(3);
    
    //plnenie 
    for(counter = 1; counter < 16; counter++)Insert(T1,counter,4 + counter);
    
    //volenie testovanej funkcie 
    PrintSubtree(T1,3);
    
    //otvorenie subora a presmerovanie OUTPUT-u do suboru 
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    

    FILE* fp = fopen("file.txt", "r");
    printf("\n");
    counter = 3;
    while(1 > counter/16){
        for(int counter2 = counter; counter2 < counter + (int)pow(2,level); counter2++){
            sprintf(array,"%02d",T1->Array[counter2]);
            fscanf(fp,"%s",line);
            printf("line = %s\n",line);
            value = strcmp(line,array);
            ck_assert_msg(value == 0, "Assertion 'line %s != %s pole[%d]' failed.", line,array,counter);
        }
        counter = counter * 2;
        level++;
    }
    fclose(fp);
    DisposeTree(T1);
    //remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintSubtree_velkosti_10_a_podstromom_random){
    int maxlevel = 10;
    int counter;
    srand(getpid());
    int level = rand()%2047;
    if(level == 0) level = rand()%2047;

    Tree T1 = CreateTree( maxlevel );
    char array[5000];
    for(counter = 1; counter < pow(2,maxlevel+1); counter++)Insert(T1,counter,4 + counter);
    
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    PrintSubtree(T1,level);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");

    counter = level;
    level = 0;
    while(1 > counter/pow(2,T1->MaxLevel + 1)){
        for(int counter2 = counter; counter2 < counter + (int)pow(2,level); counter2++){
            sprintf(array,"%02d",T1->Array[counter2]);
            fscanf(fp,"%s",line);
            value = strcmp(line,array);
            ck_assert_msg(value == 0, "Assertion 'line %s != %s pole[%d]' failed.", line,array,counter2);
        }
        counter = counter * 2;
        level++;
    }
    fclose(fp);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintSubtree_velkosti_random_podstrom_random){
    srand(getpid());
    int quantity;
    int counter;
    int level;
    char array[5000];
    int maxlevel = rand()%10;

    if(maxlevel == 0){
        quantity = 1;
        level = 1;
    }
    else{
        quantity = pow(2,maxlevel + 1);
        level = rand()%(quantity -1);
        while(level == 0) level = rand()%(quantity -1);
    } 
    
    Tree T1 = CreateTree(maxlevel);
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    for(counter = 1; counter < pow(2,maxlevel + 1); counter++) Insert(T1,counter,4 + counter);
    PrintSubtree(T1,level);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");

    counter = level;
    level=0;
    while(1 > counter/pow(2,T1->MaxLevel + 1)){
        for(int counter2 = counter; counter2 < counter + (int)pow(2,level); counter2++){
            sprintf(array,"%02d",T1->Array[counter2]);
            fscanf(fp,"%s",line);
            value = strcmp(line,array);
            ck_assert_msg(value == 0, "Assertion 'line %s != %s pole[%d]' failed.", line,array,counter2);
        }
        counter = counter * 2;
        level++;
    }
    fclose(fp);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_PrintSubtree_velkosti_0_podstromom_1){
    Tree T1 = CreateTree(0);
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    dup2(file,STDOUT_FILENO);
    Insert(T1,1,5);
    PrintSubtree(T1,1);
    
    FILE* fp = fopen("file.txt", "r");
    char line[500];
    int value;
    printf("\n");
    
    fscanf(fp,"%s",line);
    value = strcmp(line,"05");
    ck_assert_msg(value == 0, "Assertion 'line %s != 05' failed.", line);
    fclose(fp);
    remove("file.txt");
}
END_TEST

START_TEST(Test_funkcie_SubTree_s_Tree_velkosti_NULL){
  
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;    
    dup2(file,STDOUT_FILENO);
    PrintSubtree(NULL,30);   
    
    FILE* fp = fopen("file.txt", "r");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'line %s != Error' failed.", line);   
    fclose(fp);
   // remove("file.txt");

}END_TEST

START_TEST(Test_funkcie_SubTree_s_Tree_a_zlym_indexom){
    Tree T = CreateTree(1);
    MakeEmpty(T);
    Insert(T,1,5);
    int file = open("file.txt", O_TRUNC | O_RDONLY| O_WRONLY | O_CREAT, 0777);
    char line[100];
    int value;
    
    dup2(file,STDOUT_FILENO);
    PrintSubtree(T,20);   
    close(file);
    
    FILE* fp = fopen("file.txt", "r");
    fscanf(fp,"%s",line);
    value = strcmp(line,"Error");
    ck_assert_msg(value == 0, "Assertion 'line %s != Error' failed.", line);   
    fclose(fp);
    //remove("file.txt");

}END_TEST


Suite* suite_reverse(void){

    Suite* suite = suite_create("Suite reverse()");
    TCase *tc;

    tc = tcase_create("5.1.0");
    tcase_add_test(tc,Test_funkcie_SubTree_s_Tree_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.1");
    tcase_add_test(tc,Test_funkcie_SubTree_s_Tree_a_zlym_indexom);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("5.1.2");
    tcase_add_test(tc,Test_funkcie_PrintSubtree_velkosti_3_podstromom_3);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.3");
    tcase_add_loop_test(tc,Test_funkcie_PrintSubtree_velkosti_10_a_podstromom_random,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.4");
    tcase_add_loop_test(tc,Test_funkcie_PrintSubtree_velkosti_random_podstrom_random,0,10);
    suite_add_tcase(suite,tc);
    
    tc = tcase_create("5.1.5");
    tcase_add_test(tc,Test_funkcie_PrintRow_s_volanim_Tree_velkosti_NULL_a_indexu_0);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.6");
    tcase_add_test(tc,Test_funkcie_PrintRow_s_velkostou_stromu_0_a_vypisom_0_levelu);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.7");
    tcase_add_loop_test(tc,Test_funkcie_PrintRow_s_velkostou_stromu_random_vypis_random_levelu,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.8");
    tcase_add_loop_test(tc,Test_funkcie_PrintRow_velkosti_stromu_10_vypis_random_levelu,0,10);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.9");
    tcase_add_test(tc,Test_na_PrintRow_velkost_stromu_3_vypis_3_levelu);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.1.10");
    tcase_add_test(tc,Test_funkcie_PrintRow_s_volanim_Tree_velkosti_1_a_indexu_30);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.0");
    tcase_add_test(tc,Test_funkcie_PrintSubtree_velkosti_3_podstromom_3);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.1");
    tcase_add_loop_test(tc,Test_funkcie_PrintSubtree_velkosti_10_a_podstromom_random,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.2");
    tcase_add_loop_test(tc,Test_funkcie_PrintSubtree_velkosti_random_podstrom_random,0,20);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.3");
    tcase_add_test(tc,Test_funkcie_PrintSubtree_velkosti_0_podstromom_1);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.4");
    tcase_add_test(tc,Test_funkcie_SubTree_s_Tree_velkosti_NULL);
    suite_add_tcase(suite,tc);

    tc = tcase_create("5.2.5");
    tcase_add_test(tc,Test_funkcie_SubTree_s_Tree_a_zlym_indexom);
    suite_add_tcase(suite,tc);
    return suite;
}
