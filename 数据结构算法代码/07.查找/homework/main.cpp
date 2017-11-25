#include <stdio.h>
#include <stdlib.h>
struct Student
{
    int id;
    char name[100];
    int score;
};
int main()
{
    int i=0,j;
    Student student[4]=
    {
        {1024,"小甲鱼",100},
        {1026,"秋舞斜阳",60},
        {1028,"黑夜",100},
        {1030,"迷途",60}
    };
    printf("请输入要查询的学号：");
    scanf("%d",&j);
    while(student[i].id!=j && i<4)
    {
        i++;
    }
    printf("学号为%d\n",j);
    printf("姓名为%s\n",student[i].name);
    printf("成绩为%d\n",student[i].score);
    return 0;
}

