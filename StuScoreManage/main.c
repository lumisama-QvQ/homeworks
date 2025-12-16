#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //Linux下使用

#define MAX_STUDENT 30
#define MAX_COURSE 6

typedef struct Sort_Kind {
    int by_total_desc; //按总分降序
    int by_total_asc;  //按总分升序
    int by_number_asc; //按学号升序
    int by_name_dict;  //按姓名字典序
};

typedef struct Node {
    char *key;
    unsigned int value;
    struct Node *next;
} Node;

char readfile();
char writefile();
char list_record();
char search_by_name();
char search_by_number();
char total_and_average();
char statistic_analysis();
char sort();
char* input_record();


int main(char) {
    printf("1.Input record\n2.Calculate total and average scoreof every course\n3.Calculate total and average score of every student\n4. Sort in descending order by total score of every student\n5. Sort in ascending order by total score of every student\n6. Sort in ascending order by number\n7. Sort in dictionary order by name\n8. Search by number\n9. Search by name\n10.Statistic analysis for every course\n11.List record\n12.Write to a file\n13.Read from file\n0.Exit\nPlease enter your choice:");
    int choice = 0;
    for(;;){
        scanf("%d", &choice);
        if (choice < 0 || choice > 13) {
            printf("Invalid choice. Please enter a number between 0 and 13.\n");
        } else {
            printf("You selected option %d.\n", choice);
        }
    }    
    return 0;
}
char* input_record() {
    printf("Input number of students:");
    int students = getchar();
    printf("Input number of courses:");
    int cources = getchar();

    for (int i = 0; i < students; i++) {

    }

}

unsigned int hashmap(unsigned *size) {
    Node HashTable[*size];
}