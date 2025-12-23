#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <time.h>//延时函数的使用,不同平台可能不一样
#include <stdbool.h>
#include <stdbool.h>
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
//错误类型
#define EMPTY (1U << 7)
#define MISS_TYPE (1U << 8)
#define NORMAL (1U << 9)

typedef struct subject {
    wchar_t* name;
    int total;
    bool attend;
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

typedef union {
    int input_i;
    wchar_t* input_s;
} INPUT_DUF;
//功能函数
void menu(void);
void input_sub(SUBJECT**);
void del_sub(SUBJECT**,int);
void add_sub(SUBJECT**, SUBJECT*, int*, int*);
void change_sub(SUBJECT**,int, SUBJECT*);
void add_stu(STUDENT**, SUBJECT*, wchar_t*, int, float, int, int* , int*);
void read_doc(wchar_t*);
void rank(STUDENT*, int);
void search(void*, STUDENT*, int);
void update_guard(GUARD_SUB**, SUBJECT*);
void output_stu(STUDENT*);
void output_sub(SUBJECT*);
void write_doc(STUDENT*);
int def_sub(SUBJECT**);
//辅助函数
void sleep(int);//单位毫秒,不能超过1000
int compare(void*, void*, int);
void* input_c(int, int*);
void ft_stdout(void);

int main(void){
    //init
    GUARD_SUB *guard_subs = NULL;
    STUDENT *students = NULL;
    SUBJECT *subjects = NULL;
    int status = 0;
    int stu_num = 0;
    int capacity = 0;
    menu();
    while(1){
        int choose = 0;
        void *ptr = NULL;
        while(1){
            ptr = (int *)input_c(UINT, &status);
            getchar();
            switch (status) {
                case EMPTY: {
                    sleep(999);
                    printf("Can't be empty!\n");
                    break;
                }case MISS_TYPE: {
                    sleep(999);
                    printf("Please enter a positive integer!\n");
                    break;
                }case NORMAL: {
                    choose = *(int *)ptr;
                    break;
                };
                default:exit(1);
            }
            if (status == NORMAL) break;
            ft_stdout();
        }
        SUBJECT *subjects = NULL;
        switch (choose) {
            case 0: {
                printf("Exit");
                for (int i = 0; i < 3;i++){
                    sleep(200);
                    printf(".");
                    fflush(stdout);
                }
                break;
            }
            case 1: {
                //subjects需主动free
                def_sub(&subjects);

            }
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
            default: {
                printf("Please input 1~13!\n");
                ft_stdout();
            }
        }
    }
    return 0;
}
void sleep(int time_ms) {
    struct timespec spec;
    spec.tv_nsec = time_ms * 1E6;
    spec.tv_sec = 0;
    nanosleep(&spec, NULL);
}
void menu(void){
    printf("1.Input record\n");
    sleep(100);
    printf("2.Calculate total and average score of every course\n");
    sleep(100);
    printf("3.Calculate total and average score of every student\n");
    sleep(100);
    printf("4. Sort in descending order by total score of every student\n");
    sleep(100);
    printf("5. Sort in ascending order by total score of every student\n");
    sleep(100);
    printf("6. Sort in ascending order by number\n");
    sleep(100);
    printf("7. Sort in dictionary order by name\n");
    sleep(100);
    printf("8. Search by number\n");
    sleep(100);
    printf("9. Search by name\n");
    sleep(100);
    printf("10.Statistic analysis for every course\n");
    sleep(100);
    printf("11.List recordn\n");
    sleep(100);
    printf("12.Write to a file\n");
    sleep(100);
    printf("13.Read from file\n");
    sleep(100);
    printf("0.Exit\n");
    sleep(100);
    printf("Please enter your choice:");
    fflush(stdout);
}

//input_c会在下一次读取时覆盖上一次值，必须深拷贝！
//输入错误时，input_c会清空缓冲区
void* input_c(int mode, int *stats) {
    static INPUT_DUF buffer;
    if (mode == UINT){
        int c = getchar();//check
        if (c == '\n') {
            *stats = EMPTY;
            return NULL;
        } else {
            ungetc(c, stdin);
            if (scanf("%d", &buffer.input_i) != 1){
                while (getchar() != '\n');
                *stats = MISS_TYPE;
                return NULL;
            } else {
                if ( buffer.input_i < 0 ) {
                    while (getchar() != '\n');
                    *stats = MISS_TYPE;
                    return 0;
                } else {
                    *stats = NORMAL;
                    return &buffer.input_i;
                }
            }
        }
    } else if (mode == INT){
        int c = getchar();
        if (c == '\n') {
            *stats = EMPTY;
            return NULL;
        } else {
            ungetc(c, stdin);
            if (scanf("%d", &buffer.input_i) != 1){
                while (getchar() != '\n');
                *stats = MISS_TYPE;
                return NULL;
            } else {
                *stats = NORMAL;
                return &buffer.input_i;
            }
        }
    } else if (mode == STRING){
        wchar_t *temp;
        temp = (wchar_t *)malloc(sizeof(wchar_t) * 20);//最多10个汉字
        if (temp == NULL) exit(1);
            wchar_t c = getchar();
            if (c == '\n') {
            *stats = EMPTY;
            return NULL;
            } else {
                ungetc(c, stdin);
                scanf("%ls", temp);
                wchar_t *lp;
                lp = temp;
                while ((*lp != L'\0')) {
                    if (iswalnum(lp == 0)) {
                        while (getchar() != '\n');
                        *stats = MISS_TYPE;
                        return NULL;
                        break;
                    }
                lp++;
                }
                buffer.input_s = (wchar_t *)malloc(sizeof(wchar_t) * wcslen(temp) + 1);
                if (buffer.input_s == NULL) exit(1);
                wcscpy(buffer.input_s, temp);
                *stats = NORMAL;
                return &buffer.input_s;
            }
        }
        return NULL;
}
void ft_stdout(void) {
    printf(">>>");
    fflush(stdout);
}
int def_sub(SUBJECT **subjects) {
    printf("Enter default subject number\n");
    int num = 0;
    int status = 0;
    while (1){
        ft_stdout();
        void *ptr = NULL;
        ptr = (int *)input_c(UINT, &status);
        getchar();
        switch (status) {
            case EMPTY:{
                sleep(999);
                printf("Can't be empty\n");
                break;
            }case MISS_TYPE:{
                sleep(999);
                printf("Please enter a positive integer!\n");
                break;
            }case NORMAL: {
                num = *(int *)ptr;
                break;
            }
            default:exit(1);
        }
        if (status == NORMAL) break;
    }
    printf("Enter the subject name and total score, separated by a space.\n");
    SUBJECT subject;
    wchar_t temp_name[20];
    subject.name = temp_name;
    int count = 0;
    int capacity = num;
    *subjects = (SUBJECT *)malloc(sizeof(SUBJECT) * num);
    for (int i = 0; i < num ; i++) {
        wchar_t *name;
        ft_stdout();
        name = (wchar_t *)input_c(STRING, &status);
        switch (status) {
            case EMPTY:{
                sleep(999);
                printf("can't be empty!\n");
                sleep(400);
                printf("Please input all again!\n");
                i = 0;
                continue;
            }case MISS_TYPE: {
                sleep(999);
                printf("Illegal characters!\n");
                sleep(300);
                printf("Please input all again!\n");
                i = 0;
                continue;
            }case NORMAL:break;
                default:exit(1);
        }
        wcscpy(subject.name, name);
        int *def_score = 0;
        def_score =  (int *)input_c(UINT, &status);
        switch (status) {
            case MISS_TYPE: {
                sleep(999);
                printf("Please enter a positive integer!\n");
                sleep(500);
                printf("Please input all again!\n");
                i = 0;
                continue;
                case EMPTY:{
                    sleep(999);
                    printf("Score can't be empty!\n");
                    sleep(500);
                    printf("Please input all again!\n");
                    i = 0;
                    continue;
                }
            }case NORMAL:{}
            default:exit(1);
        }
        subject.score = *def_score;
        add_sub(subjects, &subject, &count, &capacity);
    }
    getchar();
    return num;
}
void add_sub(SUBJECT **subjects, SUBJECT *subject, int *count, int *capacity) {
    if ( *count >= *capacity) {
        *capacity += 2;
        SUBJECT *new_ptr = (SUBJECT *)realloc(*subjects, sizeof(SUBJECT) * *capacity);
        if (new_ptr == NULL) exit(1);
        *subjects = new_ptr;
    }
    SUBJECT *temp  = &(*subjects)[*count];
    temp->score = subject->score;
    temp->name = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(subject->name) + 1));
    wcscpy(temp->name, subject->name);
    (*count)++;
}