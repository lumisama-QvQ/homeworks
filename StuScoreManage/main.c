#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//延时函数的使用,不同平台可能不一样
#include <stdbool.h>
//多国支持
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <limits.h>

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
void sleep(unsigned int);//单位毫秒,不能超过1000
int compare(void*, void*, unsigned int);
void free_memory(void);
void* input_c(unsigned int);
void ft_stdout();

int main(void){
    //init
    GUARD_SUB *guard_subs = NULL;
    STUDENT *students = NULL;
    SUBJECT *subjects = NULL;
    unsigned int stu_num = 0;
    unsigned int capacity = 0;
    while(1){
        menu();
        //choose需主动free
        unsigned int choose = *(unsigned int *)input_c(UINT);
        break;
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
void sleep(unsigned int time_ms) {
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
void* input_c(unsigned int agr) {
    void *result = NULL;
    if (agr == UINT){
        result = (long int *)malloc(sizeof(long int));
        char buffer[100];
        while (1) {
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                while (getchar() != '\n');
                sleep(999);
                printf("Some thing wrong!\n");
            }else {
                if (buffer[0] == '\n') {
                    sleep(999);
                    printf("Cannot be empty!\n");
                }else {
                    long int temp;
                    if (sscanf(buffer, "%ld", &temp) != 1) {
                        while (getchar() != '\n');
                        sleep(999);
                        printf("Please enter a positive integer!\n");
                    } else {
                        if ( temp < 0 || temp > UINT_MAX) {
                            sleep(999);
                            printf("Please enter a positive integer\n");
                        } else {
                            *(unsigned int *)result = (unsigned int)temp;
                            break;
                        }
                    }
                }
            }
            ft_stdout();
        }
    } else if (agr == INT){
        result = (int *)malloc(sizeof(int));
        while(1){
        int check = scanf("%d", (int *)result);
        if (check != 1) {
            sleep(999);
            printf("Please enter the number!\n");
            ft_stdout();
            while (getchar() != '\n');
        } else break;
        }
    } else if (agr == STRING){
        result = (wchar_t *)malloc(sizeof(wchar_t) * 20);
        while (1){
            if (fgetws((wchar_t *)result, 20, stdin) != NULL) {
                ((wchar_t *)result)[wcscspn((wchar_t *)result, L"\n")] = L'\0';
                if (wcslen((wchar_t *)result) == 0){
                    sleep(999);
                    printf("Cannot be empty!\n");
                    ft_stdout();
                } else {
                    wchar_t *buffer = result;
                    while ((*buffer != L'\0')) {
                        if (iswalnum(buffer == 0)) {
                            sleep(999);
                            printf("Illegal characters!\n");
                            ft_stdout();
                            break;
                    }
                    buffer++;
                }
                    break;
                }
            } else printf("Some thing worng!\n");
        }
    }
    return result;
}
void ft_stdout(void) {
    printf(">>>");
    fflush(stdout);
}