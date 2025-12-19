//注：此程序使用了GNU标准，部分内容可能仅在Linux下可以编译。
/*
(1) 输入每个学生的学号、姓名和各科考试成绩；✔
(2) 计算每门课程的总分和平均分；
(3) 计算每个学生的总分和平均分；✔
(4) 按每个学生的总分由高到低排出名次表；
(5) 按每个学生的总分由低到高排出名次表；
(6) 按学号由小到大排出成绩表；
(7) 按姓名的字典顺序排出成绩表；
(8) 按学号查询学生排名及其考试成绩；
(9) 按姓名查询学生排名及其考试成绩；
(10) 按优秀(90~100分)、良好(80~89分)、中等(70~79分)、及格(60~69分)、不及格(0~59分)5个类别，对每门课程分别统计每个类别的人数以及所占的百分比；
(11) 输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分；
(12) 将每个学生的记录信息写入文件；
(13) 从文件中读出每个学生的记录信息并显示。
*/
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

typedef enum {
    student_id,
    student_name,
} Search_kind;
typedef struct {
    float total;
    float average;
} Statistics;
typedef enum {
    by_total_desc, //按总分降序
    by_total_asc, //按总分升序
    by_number_asc, //按学号升序
    by_name_dict,  //按姓名字典序
} Sort_Kind;
//*char->name
typedef struct {
    char *name;
    bool attend;
    float score;
} Subject;
//*name *Subject
typedef struct {
    char *name;
    Subject* Subject;
    float average;
    Statistics *statistics;
} Student;





Student* readfile();//未实现
void writefile();//未实现
Student* list_record();//未实现
Student* search_by_name();//未实现
Student* search_by_number();//未实现
char* statistic_analysis();//未实现
char* sort();//未实现
Student* input_record();
void et_point();

//数据处理
void add_student(Student **arr, int *count, int *capacity,const char *name, Subject subjects, Statistics statistics);
void format();//未实现
void delete();//未实现
void search(Student *student, Search_kind kind,char *context);//未实现

int main(void) {
    int choice = 0;
    int count = 0;
    int capacity = 0;
    req.tv_nsec =300000000;
    req.tv_sec = 0;
    Student *students = NULL;

    for(;;){
        printf("1.Input record\n2.Calculate total and average scoreof every course\n3.Calculate total and average score of every student\n4. Sort in descending order by total score of every student\n5. Sort in ascending order by total score of every student\n6. Sort in ascending order by number\n7. Sort in dictionary order by name\n8. Search by number\n9. Search by name\n10.Statistic analysis for every course\n11.List record\n12.Write to a file\n13.Read from file\n0.Exit\nPlease enter your choice:");
        fflush(stdout);
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
                et_point();
                exit(0);
            };
            case 1 :{
                students = input_record();
                printf("Finish input");
                et_point();
            };
        }
    }    
    return 0;
}

//eg: 姓名 语 分数 数 分数 英 分数 物 分数 化 分数 生 分数
//输入考试科目数量，各名称。
Student* input_record() {
    int subject_number = 0;
    int capacity = 0;
    Statistics statistics;
    //*student->*name
    //*student->*subject->*name
    Student *students = NULL;
    printf("You choose input record.\n");
    printf("Please input subject number:");
    fflush(stdout);
    scanf("%d", &subject_number);
    getchar();
    //char**=>char*(char**[i])=>string
    char **subjects_name = NULL;
    subjects_name = (char **)malloc(sizeof(char *) * subject_number);
    
    //课程录入
    printf("Now please input name of subjects by whitespace.\n");
    printf(">>>");
    fflush(stdout);
    for (int i = 0; i < subject_number; i++) {
        //解决，%ms参数应取二级指针
        if (scanf("%ms", &subjects_name[i]) != 1) {
            printf("Error: Not enough memory!\n");
            exit(1);
        }
    }
    getchar();
    printf("Enture your input.\n");
    for (int i = 0;i < subject_number; i++) {
        printf("%s ", subjects_name[i]);
    }
    //学生录入
    printf("\n");
    printf("Please input student's name and each score of subject which follow the order you input by whitespace.\n");
    for(int student_count = 0;;student_count++) {
        printf(">>>");
        fflush(stdout);
        char *student_name;
        int attend = 0;
        scanf("%ms", &student_name);
        //提前返回，此时students可能为NULL
        if (strcmp(student_name, "exit") == 0) return students;
        Subject *temp = (Subject *)malloc(sizeof(Subject) * subject_number);
        for(int i = 0; i < subject_number; i++){
            scanf("%f", &temp[i].score);
            //temp(动态)=>name->subjects_name
            temp[i].name = subjects_name[i];
            if (temp[i].score == -1.0) {
                temp[i].attend = false;
            }
            else {
                temp[i].attend = true;
                statistics.total += temp[i].score;
                attend += 1;
            }
            statistics.average = statistics.total / attend;
        }
        add_student(&students, &student_count, &capacity, student_name, *temp, statistics);
    }

    return students;
}

void add_student(Student **arr, int *count, int *capacity,const char *name, Subject subjects, Statistics statistics) {
                    //subjects->temp(input_record)(动态)
                    //动态扩容
                    if (*count >= *capacity) {
                        int new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);
                        Student *temp = (Student *)realloc(*arr, new_capacity * sizeof(Student));
                        if (temp == NULL) {
                            printf("Error: Not enough memory!");
                            exit(1);
                        }
                        //*arr=>*students(input_record)->*temp(add_student)(动态)
                        *arr = temp;
                        *capacity = new_capacity;
                    }
                    //target(动态)->&(*student(input_record))[student_count(input_record)]
                    Student *target = &(*arr)[*count];
                    target->name = (char *)malloc(strlen(name) + 1);
                    if ( target->name == NULL) {
                        printf("Error: Not enough memory!");
                    }
                    //target=>name(动态）->name
                    strcpy((char *)target->name, name);
                    target->Subject = &subjects;
                    target->statistics = &statistics;
                    (*count)++;
                }

void et_point() {
    for(int i = 0; i < 3; i++){
        fflush(stdout);
        nanosleep(&req,NULL);
        printf(".");
    }
}