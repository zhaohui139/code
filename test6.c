#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100 
typedef struct {
    char name[50];
    int score;     
    char grade[5]; 
    float gpa;     
} Student;
void get_grade_info(int score, char* grade, float* gpa);
void input_students(Student students[], int* count);
void print_all_students(Student students[], int count);
int search_student(Student students[], int count, char* target_name);
void bubble_sort(Student students[], int count);
int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n学生成绩管理系统\n");
        printf("1.录入学生姓名和成绩\n");
        printf("2.查询学生成绩\n");
        printf("3.按照成绩排序（降序）\n");
        printf("4.显示所有程序\n");
        printf("0.退出程序\n");
        printf("\n");
        printf("请选择功能(0~4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("输入错误，请输入数字！\n");
            while(getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                input_students(students, &count);
                break;
            case 2: {
                if (count == 0) {
                    printf("当前没有学生成绩，请输入\n");
                    break;
                }
                char target[50];
                printf("请输入要查询的学生姓名： ");
                scanf("%49s", target);
                int index = search_student(students, count, target);
                if (index != -1) {
                    printf("\n查询结果\n");
                    printf("姓名： %-10s | 成绩： %3d | 等级; %-3s | 绩点： %.1f\n", 
                           students[index].name, students[index].score, 
                           students[index].grade, students[index].gpa);
                } else {
                    printf("未找到名为 %s 的同学。\n", target);
                }
                break;
            }
            case 3:
                if (count == 0) {
                    printf("当前没有学生数据，请输入！\n");
                    break;
                }
                bubble_sort(students, count);
                printf("排序完成！\n");
                print_all_students(students, count);
                break;
            case 4:
                print_all_students(students, count);
                break;
            case 0:
                printf("感谢使用，谢谢！\n");
                return 0;
            default:
                printf("无效的输入，请重新输入！\n");
        }
    }
    return 0;
}
void get_grade_info(int score, char* grade, float* gpa) {
    if (score >= 97 && score <= 100) { strcpy(grade, "A+"); *gpa = 4.5; }
    else if (score >= 93 && score <= 96) { strcpy(grade, "A"); *gpa = 4.3; }
    else if (score >= 89 && score <= 92) { strcpy(grade, "A-"); *gpa = 4.0; }
    else if (score >= 85 && score <= 88) { strcpy(grade, "B+"); *gpa = 3.8; }
    else if (score >= 81 && score <= 84) { strcpy(grade, "B"); *gpa = 3.4; }
    else if (score >= 77 && score <= 80) { strcpy(grade, "B-"); *gpa = 3.0; }
    else if (score >= 73 && score <= 76) { strcpy(grade, "C+"); *gpa = 2.6; }
    else if (score >= 69 && score <= 72) { strcpy(grade, "C"); *gpa = 2.2; }
    else if (score >= 65 && score <= 68) { strcpy(grade, "C-"); *gpa = 1.8; }
    else if (score >= 60 && score <= 64) { strcpy(grade, "D"); *gpa = 1.2; }
    else if (score >= 40 && score <= 59) { strcpy(grade, "F"); *gpa = 0.0; }
    else if (score >= 0 && score <= 39) { strcpy(grade, "F-"); *gpa = 0.0; }
    else { strcpy(grade, "无效"); *gpa = 0.0; } 
}
void input_students(Student students[], int* count) {
    if (*count >= MAX_STUDENTS) {
        printf("存储空间已满，无法输入\n");
        return;
    }

    printf("开始录入 (输入 0 0 结束录入)\n");
    while (*count < MAX_STUDENTS) {
        char temp_name[50];
        int temp_score;

        printf("请输入学生姓名 (输入 'end' 退出录入): ");
        scanf("%49s", temp_name);
        
        if (strcmp(temp_name, "end") == 0) {
            break;
        }

        printf("请输入学生成绩 (0-100): ");
        if (scanf("%d", &temp_score) != 1) {
            printf("成绩输入错误，请重新输入！\n");
            while(getchar() != '\n');
            continue;
        }
        if (temp_score < 0 || temp_score > 100) {
            printf("成绩无效，录入终止。\n");
            break;
        }
        strcpy(students[*count].name, temp_name);
        students[*count].score = temp_score;
        get_grade_info(temp_score, students[*count].grade, &students[*count].gpa);
        
        (*count)++;
        printf("录入成功！\n");
    }
}
void print_all_students(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息。\n");
        return;
    }
    printf("\n%-15s %-10s %-10s %-10s\n", "姓名", "成绩", "等级", "绩点");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s %-10d %-10s %-10.1f\n", 
               students[i].name, students[i].score, 
               students[i].grade, students[i].gpa);
    }
}
int search_student(Student students[], int count, char* target_name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, target_name) == 0) {
            return i;
        }
    }
    return -1;
}
void bubble_sort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].score < students[j + 1].score) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}