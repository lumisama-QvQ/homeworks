#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//延时函数的使用,不同平台可能不一样
//多国支持
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

//升降序模式
#define ASCEND (1U << 0)
#define DESCEND (1U << 1)
//查询/排序模式
#define NAME (1U << 2)
#define ID (1U << 3)
//检查模式
#define INT (1U << 4)
#define UINT (1U << 5)
#define STRING (1U << 6)

typedef struct subject {
    wchar_t* name;
    int total;
    float score;
} SUBJECT;

typedef struct student {
    wchar_t* name;
    SUBJECT* Subjects;
    float total;
    int sub_num;
    int att_num;
} STUDENT;

typedef struct level {
    int great;
    int good;
    int normal;
    int pass;
    int bad;
} LEVEL;

typedef struct guard_sub {
    wchar_t* name;
    int att_num;
    int real_num;
    float tt_score;
    LEVEL level;
} GUARD_SUB;

//功能函数
void menu(void);
void input_sub(SUBJECT**);
void del_sub(SUBJECT**,unsigned int);
void add_sub(SUBJECT**, SUBJECT*);
void change_sub(SUBJECT**,unsigned int, SUBJECT*);
void add_stu(STUDENT**, SUBJECT*, wchar_t*, unsigned int, float, unsigned int, unsigned int , unsigned int);
void read_doc(wchar_t*);void rank(STUDENT*, unsigned int);
void search(void*, STUDENT*, unsigned int);
void update_guard(GUARD_SUB**, SUBJECT*);
void output_stu(STUDENT*);
void output_sub(SUBJECT*);
void write_doc(STUDENT*);
//辅助函数
void delay(unsigned int);
int compare(void*, void*, unsigned int);
void free_memory(void);
void* input_c(unsigned int);

int main(void){
    //init
    GUARD_SUB *guard_subs = NULL;
    STUDENT *students = NULL;
    SUBJECT *subjects = NULL;
    unsigned int stu_num = 0;
    unsigned int capacity = 0;
    while(1){
        menu();
        unsigned int choose = *(int *)input_c(UINT);
        switch (choose) {
            case 1: {}
            case 2: {}
            case 3: {}
            case 4: {}
            case 5: {}
            case 6: {}
            case 7: {}
            case 8: {}
            case 9: {}
            case 10: {}
            case 11: {}
            case 12: {}
            case 13: {}
            default: {}
        }
        break;
    }
    return 0;
}