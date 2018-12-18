#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <time.h>
void food();
void show();
void move();
void turn();
void check();
void ini();
int  dy[4] = { 0, 1, 0, -1 };
int  dx[4] = { -1, 0, 1, 0 };
int sum = 5;  
int over = 0;
int speed;   
char map[17][17];

struct snake {
    int x, y;  
    int dir;  
} A[100];

void ini() { 
    speed = 500;
    over = 0;
    sum = 5;
    int i, j;
    for (i = 0; i < 100; i++) {  
        A[i].dir = 0;
        A[i].x = 0;
        A[i].y = 0;
    }
    A[0].x = 1; A[0].y = 1; 
    A[1].x = 1; A[1].y = 2;
    A[2].x = 1; A[2].y = 3;
    A[3].x = 1; A[3].y = 4;
    A[4].x = 1; A[4].y = 5; A[4].dir = 1;
    srand(time(0));
    for (i = 0; i < 17; i++) { 
        for (j = 0; j < 17; j++) {
            map[i][j] = '*';
        }
    }
    for (i = 1; i < 16; i++) {
        for (j = 1; j < 16; j++) {
            map[i][j] = ' ';
        }
    }
    map[A[4].x][A[4].y] = 'H'; 
    for (i = 0; i < sum - 1; i++) { 
        map[A[i].x][A[i].y] = 'X';
    }
    food();

}


void show() {  
    int i, j, x, y;
    for (i = 0; i < 17; i++) {
        for (j = 0; j < 17; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    while (1) {
        Sleep(speed);  
        turn();
        move();
        if (over) {  
            while (1) {
                char ch = _getch();
                if (ch == 113) {   
                    return;
                }
                else if (ch == 114) {  
                    ini();
                    break;
                }
            }
        }
        system("cls");  
        for (i = 0; i < 17; i++) {  
            for (j = 0; j < 17; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }

    }
}

void food() {  
    int x, y;
    while (1) {
        x = (int)(15 * rand() / (RAND_MAX + 1.0));  
        y = (int)(15 * rand() / (RAND_MAX + 1.0));
        if (map[x][y] == ' ') {  
            map[x][y] = 'O';
            break;
        }
    }
}


void move() {  
    int i, x, y;
    int t = sum;  
    check();  
    if (t == sum) {  
        for (i = 0; i < sum - 1; i++) {
            if (i == 0) {  
                map[A[i].x][A[i].y] = ' ';
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            else {  
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            map[A[i].x][A[i].y] = 'X';  
        }
        A[sum - 1].x = A[sum - 1].x + dx[A[sum - 1].dir];  
        A[sum - 1].y = A[sum - 1].y + dy[A[sum - 1].dir];
        map[A[sum - 1].x][A[sum - 1].y] = 'H';  
    }
    else {
        map[A[sum - 2].x][A[sum - 2].y] = 'X';  
        A[sum - 1].x = A[sum - 2].x + dx[A[sum - 2].dir];  
        A[sum - 1].y = A[sum - 2].y + dy[A[sum - 2].dir];
        A[sum - 1].dir = A[sum - 2].dir;  
        map[A[sum - 1].x][A[sum - 1].y] = 'H';  
        food();
    }

}

void check() {  
    int x, y, i, j;
    x = A[sum - 1].x + dx[A[sum - 1].dir];  
    y = A[sum - 1].y + dy[A[sum - 1].dir];
    if (map[x][y] == '*' || map[x][y] == 'X') {  
        if (x != A[0].x || y != A[0].y) { 
            map[8][4] = 'G'; map[8][5] = 'A'; map[8][6] = 'M'; map[8][7] = 'E'; 
            map[8][9] = 'O'; map[8][10] = 'V'; map[8][11] = 'E'; map[8][12] = 'R';
            map[8][8] = ' ';
            system("cls");
            for (i = 0; i < 17; i++) {
                for (j = 0; j < 17; j++) {
                    printf("%c", map[i][j]);
                }
                printf("\n");
            }
            printf("Input 'r' to restart\nInput 'q' to quit\n");
            over = 1;
        }
    }
    else if (map[x][y] == 'O') {
        sum++; 
        speed = ((600 - sum * 20)>100) ? (600 - sum * 20) : 100;
    }
}

void turn() { 
    if (_kbhit()) {
        char dir = _getch();  
        switch (dir) {  
        case 119: A[sum - 1].dir = (A[sum - 1].dir == 2)?2:0; break;
        case 100: A[sum - 1].dir = (A[sum - 1].dir == 3)?3:1; break;
        case 115: A[sum - 1].dir = (A[sum - 1].dir == 0)?0:2; break;
        case 97: A[sum - 1].dir = (A[sum - 1].dir == 1)?1:3; break;
        }
    }
}

int main() {
    printf("任意键开始\n");
    char ch = _getch();
    system("cls");
    ini();
    show();
    return 0;
}
/*--------------------- 
作者：patrick_lii 
来源：CSDN 
原文：https://blog.csdn.net/patrick_lii/article/details/78927023 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/ 
