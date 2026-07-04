#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STU 100
#define ID_LEN 15
#define NAME_LEN 10
#define CLASS_LEN 20
// 自动生成的文件名称
#define FILE_NAME "kaoqin_data.txt"

// 学生结构体
typedef struct {
    char id[ID_LEN];
    char name[NAME_LEN];
    char Class[CLASS_LEN];
    int normal;
    int late;
    int absent;
   
} Student;

Student stuArr[MAX_STU];
int stuCount = 0;

// 获取当前日期
void getToday(char* dateBuf) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(dateBuf, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);sprintf(dateBuf, "%04d-%02d-%02d %02d:%02d:%02d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,   // 时 0~23
        t->tm_min,    // 分
        t->tm_sec     // 秒
    );
}

// 加载文件：文件不存在直接学生数置0，无任何默认学生
void loadData() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        stuCount = 0;
        return;
    }
    stuCount = 0;
    while (fscanf(fp, "%s %s %s %d %d %d ",
        stuArr[stuCount].id, stuArr[stuCount].name, stuArr[stuCount].Class,
        &stuArr[stuCount].normal, &stuArr[stuCount].late, &stuArr[stuCount].absent) != EOF)
    {
        stuCount++;
    }
    fclose(fp);
}

// 保存数据："w"模式，没有文件会自动新建
void saveData() {
    FILE* fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("文件创建失败！\n");
        return;
    }
    for (int i = 0; i < stuCount; i++) {
        fprintf(fp, "%s %s %s %d %d %d \n",
            stuArr[i].id, stuArr[i].name, stuArr[i].Class,
            stuArr[i].normal, stuArr[i].late, stuArr[i].absent);
    }
    fclose(fp);
}

// 菜单
void showMenu() {
    printf("\n====学生考勤管理系统====\n");
    printf("1. 查看全部学生\n");
    printf("2. 登记考勤(0正常/1迟到/2旷课)\n");
    printf("3. 添加新学生\n");
    printf("4. 班级考勤率\n");
    printf("5. 缺勤预警\n");
    printf("6. 查找某个学生\n");
    printf("7. 删除学生\n");
    printf("0. 退出并自动保存数据\n");
    printf("========================\n");
    printf("请输入功能编号：");
}

// 展示学生
void showAll() {
    printf("\n%-12s %-8s %-10s %-6s %-6s %-6s\n", "学号", "姓名", "班级", "出勤", "迟到", "旷课");
    for (int i = 0; i < stuCount; i++) {
        
            printf("%-12s %-8s %-10s %-6d %-6d %-6d \n",
                stuArr[i].id, stuArr[i].name, stuArr[i].Class,
                stuArr[i].normal, stuArr[i].late, stuArr[i].absent);
        }
       
            
    }

// 考勤信息登记 
void signAttendance() {
    char id[ID_LEN], date[20];
    int status;
    getToday(date);
    printf("今日日期：%s\n输入学生学号：", date);
    scanf("%s", id);
    printf("输入出勤状态(0正常/1迟到/2旷课)：");
    scanf("%d", &status);
    for (int i = 0; i < stuCount; i++) {
        if (strcmp(stuArr[i].id, id) == 0) {
            if (status == 0)
            {
                stuArr[i].normal++;
                printf("登记成功：正常出勤！\n"); // 添加出勤 
            }
            else if (status == 1)
            {
                stuArr[i].late++;
                printf("登记成功：迟到！\n");    // 添加迟到 
            }
            else if (status == 2)
            {
                stuArr[i].absent++;
                
                printf("登记成功：旷课！\n");    // 添加旷课 
            }
            else
            {
                printf("状态输入错误！\n");
            }
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 添加新学生
void addStudent() {
    char newId[ID_LEN], newName[NAME_LEN], newClass[CLASS_LEN]; // 储存新增的学号，姓名，班级 
    printf("输入学号：");
    scanf("%s", newId);
    for (int i = 0; i < stuCount; i++) {
        if (strcmp(stuArr[i].id, newId) == 0) {
            printf("学号重复，添加失败！\n"); // 如果已有该学生则添加失败，返回 
            return;
        }
    }
    printf("输入姓名：");
    scanf("%s", newName);
    printf("输入班级：");
    scanf("%s", newClass);
    strcpy(stuArr[stuCount].id, newId);
    strcpy(stuArr[stuCount].name, newName);
    strcpy(stuArr[stuCount].Class, newClass);
    stuArr[stuCount].normal = stuArr[stuCount].late = stuArr[stuCount].absent = 0;
    stuCount++;
    printf("学生添加完成！\n");
}

// 查看班级考勤率 
void showClassStats() {
    loadData();
    printf("输入需要查找的班级:\n");
    char Class[CLASS_LEN];
    int sum_normal = 0, sum_late = 0, sum_absent = 0;
    int total_normal = 0, total_students = 0;
    int i;

    scanf("%s", Class); 

    for (i = 0; i < stuCount; i++) { // 将输入班级与数组中的班级进行匹配，当数组中的班级与输入班级相等就可以找到这个班级所有学生的考勤情况 
        if (strcmp(stuArr[i].Class, Class) == 0) {
            sum_normal += stuArr[i].normal; // 把该班级的所有学生的出勤数、迟到数、旷课数分别进行相加 
            sum_late += stuArr[i].late;
            sum_absent += stuArr[i].absent;
           
        }
    }

   

    total_normal = sum_normal + sum_late;
    total_students = total_normal + sum_absent;

    
    double classRate;
    
        classRate = (double)total_normal / total_students * 100; // 计算出勤率 
    

    printf("班级出勤率: %.2f%%\n", classRate); // 输出该班级的出勤率 
}

// 缺勤3次预警 
void warnAbsent()
{
    loadData();
    int i;
    printf("==========缺勤预警名单==========\n");
    for (i = 0; i < stuCount; i++)
    {
        // 缺勤满3次触发预警
        if (stuArr[i].absent >= 3) // 查找旷课数量满3次的学生 
        {
            printf("预警：%s %s  累计缺勤%d次，请约谈\n", stuArr[i].name, stuArr[i].Class, stuArr[i].absent);
        }
    }
    printf("================================\n");
    getchar();
}

// 查找某个学生的考勤数据 
void findSb() {
    loadData();
    int i;
    char id[ID_LEN];
    printf("输入需要查找的学生学号:\n");
    scanf("%s", id);
    for (int i = 0; i < stuCount; i++) {
        if (strcmp(stuArr[i].id, id) == 0) // 将输入学号以原有学号进行匹配，当数组学号与输入学号相等就可以找到该学生
        {
            printf("学号：%s 姓名:%s  班级:%s 出勤:%d 迟到:%d 旷课:%d\n ", stuArr[i].id, stuArr[i].name, stuArr[i].Class, stuArr[i].normal, stuArr[i].late, stuArr[i].absent);
    } // 输出该学生的考勤信息 
    }
}

// 删除学生    
void deleteStudent() {
    char delId[ID_LEN];
    printf("输入要删除的学生学号：");
    scanf("%s", delId);

    int index = -1;
    for (int i = 0; i < stuCount; i++) {
        if (strcmp(stuArr[i].id, delId) == 0) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("未找到学号 %s 的学生！\n", delId);
        return;
    }

    printf("找到以下学生：\n");
    printf("学号：%s  姓名：%s  班级：%s\n",
        stuArr[index].id, stuArr[index].name, stuArr[index].Class);
    printf("确认删除？(y/n)：");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("删除已取消\n");
        return;
    }

    for (int i = index; i < stuCount - 1; i++) {
        stuArr[i] = stuArr[i + 1];
    }
    stuCount--;  // 学生总数减1

    printf("学生 %s 已删除！\n", delId);
}

// 主程序入口 
int main() {
    int op;
    loadData();
    while (1) {
        showMenu();
        scanf("%d", &op);
        switch (op) {
        case 1: showAll(); break;              // 查看全部     
        case 2: signAttendance(); break;       // 登记考勤 
        case 3: addStudent(); break;           // 添加学生 
        case 4: showClassStats(); break;       // 班级统计 
        case 5: warnAbsent();break;            // 缺勤预警 
        case 6: findSb(); break;               // 查找学生 
        case 7: deleteStudent(); break;        // 删除学生 
        case 0:
            saveData();
            printf("数据已保存，程序退出\n");
            system("pause");
            return 0;
        default: printf("输入错误编号！\n");
        }
        printf("\n按回车继续...");
        getchar(); getchar();
        system("cls");
    }
}
