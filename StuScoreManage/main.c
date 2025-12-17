//注：此程序使用了GNU标准，部分内容仅在Linux下可以编译。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> //Linux下使用延时函数

//要求。。。好像没什么用了
#define MAX_STUDENT 30
#define MAX_COURSE 6

//定义延时时钟
struct timespec req;

typedef struct {
    int by_total_desc; //按总分降序
    int by_total_asc;  //按总分升序
    int by_number_asc; //按学号升序
    int by_name_dict;  //按姓名字典序
} Sort_Kind;
typedef struct {
    unsigned char *name;
    bool attend;
    float score;
} Subject;
typedef struct {
   unsigned char *name;
   Subject* Subject;
   float total;
} Student;


Student* readfile();
void writefile();
Student* list_record();
Student* search_by_name();
Student* search_by_number();
Student* total_and_average();
Student* statistic_analysis();
float* total(Subject *subjects, int subject_number);
char* sort();
Student* input_record();

//数组处理
void add_student(Student **arr, int *count, int *capacity,const unsigned char *name, Subject *subjects);
void format();
void delete();


int main(void) {
    printf("1.Input record\n2.Calculate total and average scoreof every course\n3.Calculate total and average score of every student\n4. Sort in descending order by total score of every student\n5. Sort in ascending order by total score of every student\n6. Sort in ascending order by number\n7. Sort in dictionary order by name\n8. Search by number\n9. Search by name\n10.Statistic analysis for every course\n11.List record\n12.Write to a file\n13.Read from file\n0.Exit\nPlease enter your choice:");
    fflush(stdout);

    int choice = 0;
    int count = 0;
    int capacity = 0;
    req.tv_nsec =300000000;
    req.tv_sec = 0;
    Student *students = NULL;

    for(;;){
        scanf("%d", &choice);
        if (choice < 0 || choice > 13) {
            printf("Invalid choice. Please enter a number between 0 and 13.\n");
        } else {
            printf("You selected option: %d.\n", choice);
        }
        switch (choice) {
            case 0 :{
                nanosleep(&req,NULL);
                printf("Exiting");
                fflush(stdout);
                nanosleep(&req,NULL);
                printf(".");
                fflush(stdout);
                nanosleep(&req,NULL);
                printf(".");
                fflush(stdout);
                nanosleep(&req,NULL);
                printf(".\n");                
                exit(0);
            };
            case 1 :{
                students = input_record();
            };
        }
    }    
    return 0;
}

//姓名 语 分数 数 分数 英 分数 物 分数 化 分数 生 分数
//输入考试科目数量，各名称。
Student* input_record() {
    int subject_number = 0;
    float subject_score;
    bool attend;
    int count = 0;
    int capacity = 0;
    Student students;


    printf("You choose input record.\n");
    printf("Please input subject number:");
    fflush(stdout);
    scanf("%d", &subject_number);
    getchar();
    Subject *subjects = (Subject *)malloc(sizeof(Subject) * subject_number);

    //课程录入
    printf("Now please input name of subjects by whitespace.\n");
    printf(">>>");
    fflush(stdout);
    for (int i = 0; i < subject_number; i++) {
        if (scanf("%ms", &subjects[i].name) != 1) {
            printf("Error: Not enough memory!\n");
            exit(1);
        }
    }
    printf("Enture your input.\n");
    for (int i = 0;i < subject_number; i++) {
        printf("%s ", subjects[i].name);
    }


    printf("\n");
    printf("Please input student's name and each subject score follow the order you input by whitespace.");
    for(int student_order = 0;;student_order++) {
        printf(">>>");
        fflush(stdout);


    }
    }

void add_student(Student **arr, int *count, int *capacity,const unsigned char *name, Subject *subjects) {
                    //动态扩容
                    if (*count >= *capacity) {
                        int new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);
                        Student *temp = (Student *)realloc(*arr, new_capacity * sizeof(Student));
                        if (temp == NULL) {
                            printf("Error: Not enough memory!");
                            exit(1);
                        }
                        *arr = temp;
                        *capacity = new_capacity;
                    }
                    Student *target = &(*arr)[*count];
                    target->name = (unsigned char *)malloc(strlen(name) + 1);
                    if ( target->name == NULL) {
                        printf("Error: Not enough memory!");
                    }
                    strcpy((char *)target->name, name);
                    target->Subject = subjects;

                    (*count)++;
                }

float* total(Subject *subjects, int subject_number) {
    float result = 0.0;
    for (int i = 0; i < subject_number; i++){
        if (subjects->attend == false) {
            i++;
        }
        result += subjects->score;
    }
    return &result;
}