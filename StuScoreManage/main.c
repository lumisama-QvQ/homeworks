#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <threads.h>
#include <time.h>//延时函数的使用,不同平台可能不一样
#include <stdbool.h>
#include <stdbool.h>
//多国支持
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
//状态
#define ON 1
#define OFF 0
#define SETTING 2
//升降序模式
#define ASCEND 3
#define DESCEND 4
//查询/排序模式
#define NAME 5
#define ID 6
//检查模式
#define INT 7
#define UINT 8
#define FLOAT 9
#define STRING 10
//错误类型
#define EMPTY 11
#define MISS_TYPE 12
#define NORMAL 13
//修改类型
#define DEL 14
#define ADD 15
#define CHANGE 16
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
    float input_f;
} INPUT_DUF;
//功能函数
void menu(void);
void input_sub(SUBJECT**);
void del_sub(SUBJECT**,int);
void add_sub(SUBJECT**, SUBJECT*, int*, int*);
void change_sub(SUBJECT**,int, SUBJECT*);
int add_stu(STUDENT**, SUBJECT*, int* , int*, int);
void read_doc(wchar_t*);
void rank(STUDENT*, int);
void search(void*, STUDENT*, int);
void update_guard(GUARD_SUB**, SUBJECT*);
void output_stu(STUDENT*);
void output_sub(SUBJECT*);
void write_doc(STUDENT*);
int def_sub(SUBJECT**);
void sub_cpy(SUBJECT*, SUBJECT*, int);
//辅助函数
void sleep(int);//单位毫秒,不能超过1000
int compare(void*, void*, int);
void* input_c(int, int*);
void ft_stdout(void);

int main(void){
    //init
    GUARD_SUB *guard_subs = NULL;
    STUDENT *students = NULL;
    SUBJECT *def_subjects = NULL;
    int status = 0;
    int sub_count = 0;
    int stu_count = 0;
    int stu_capacity = 0;
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
                //subjects及其内容需主动free
                sub_count = def_sub(&def_subjects);
                printf("Now, ");
                fflush(stdout);
                sleep(400);
                SUBJECT *temp_subjects = NULL;
                printf("Input students information.\n");
                printf("Input Exit to quit\nInput setting to change subjects of current student\n");
                //temp_subjects及其内容需手动释放
                sub_cpy(temp_subjects, def_subjects, sub_count);
                int button = ON;
                while (button){
                    //students及其内容需要手动free
                    button = add_stu(&students, temp_subjects,&stu_count, &stu_capacity, sub_count);
                    if (button == SETTING) {}
                }
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
        }else if (mode == FLOAT) {
            static INPUT_DUF temp;
            temp.input_f = getchar();
            if (temp.input_f == '\n') {
                *stats = EMPTY;
                return NULL;
            } else {
                ungetc(temp.input_f, stdin);
                if (scanf("%f", &temp.input_f) != 1) {
                    while (getchar() != '\n');
                    *stats = MISS_TYPE;
                    return NULL;
                }else{
                    *stats = NORMAL;
                    return &temp.input_f;
                }
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
        int *def_total = 0;
        def_total =  (int *)input_c(UINT, &status);
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
        subject.total = *def_total;
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
int add_stu(STUDENT **students, SUBJECT *subjects, int *stu_count, int *capacity, int sub_count) {
    int status = 0;
    wchar_t *temp;
    while(1) {
        ft_stdout();
        temp = (wchar_t *)input_c(STRING, &status);
        switch (status) {
            case EMPTY:{
                sleep(999);
                printf("Can't be empty!\n");
                sleep(300);
                printf("Please input all again!\n");
                free(temp);
                continue;
            }case MISS_TYPE:{
                sleep(999);
                printf("Illegal characters!\n");
                sleep(300);
                printf("Please input all again!\n");
                free(temp);
                continue;
            }case NORMAL: break;
            default:exit(1);
        }
        if (status == NORMAL) break;
    }
    if (wcscmp(temp, (wchar_t *)"Exit") || wcscmp(temp, (wchar_t *)"exit")) return OFF;
    if (wcscmp(temp, (wchar_t *)"settings") || wcscmp(temp, (wchar_t *)"Setting")) {
        while (getchar() != '\n');
        return SETTING;
    }
    if (*stu_count >= *capacity) {
        *capacity += 8;
        STUDENT *ptr = (STUDENT *)realloc(*students, *capacity);
        if (ptr == NULL) exit(1);
        *students = ptr;
    }
    STUDENT *student = &(*students)[*stu_count];
    student->name = (wchar_t *)malloc(sizeof(wchar_t *) + (wcslen(temp) + 1));
    if (student->name == NULL) exit(1);
    wcscpy(student->name, temp);
    student->Subjects = (SUBJECT *)malloc(sizeof(*subjects));
    if (student->Subjects == NULL) exit(1);
    sub_cpy(student->Subjects, subjects, sub_count);
    student->sub_num = sub_count;
    int score = 0;
    for (int i = 0; i < *stu_count; i++){
        while (1){
            score = *(float *)input_c(FLOAT, &status);
            switch (status) {
                case EMPTY:{
                    sleep(999);
                    printf("Format error!\n");
                    sleep(200);
                    printf("Please input all again.\n");
                    i = 0;
                    continue;
                }case MISS_TYPE:{
                    sleep(999);
                    printf("Illegal characters\n");
                    sleep(200);
                    printf("Please input all again.\n");
                    i = 0;
                    continue;
                }case NORMAL:break;
                default:exit(1);
            }if (status == NORMAL) break;
        }
        if (score == -1) student->Subjects[i].attend = false;
        else if (score < 0 || score > subjects[i].total) {
            sleep(999);
            printf("Score anomaly!\n");
            sleep(200);
            printf("Please input all again.\n");
            i = 0;
            continue;
        }else {
            student->att_num++;
            student->total += score;
            student->Subjects[i].score = score;
        }
    }
    return ON;
}
void sub_cpy(SUBJECT *subjects_to, SUBJECT *subjects_from, int count) {
    for (int i = 0; i < count; i++){
        subjects_to[i].name = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(subjects_from[i].name) + 1));
        if (subjects_to[i].name == NULL) exit(1);
        wcscpy(subjects_to[i].name, subjects_from[i].name);
    }
}