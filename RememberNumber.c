#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

#define UNCHOOSEN 0
#define MIXPOCKER 1
#define RIGHTPOCKER 2

int main() {
    /*prompt*/
    printf("*******************************************************************************************************\n");
    printf("**测试game：记忆扑克牌v2.0\n");
    printf("**\n**说明：接下来将要记忆x(1 <= x <= 52)张扑克牌，\n**记忆的总时间为y秒，\n**你需要在记忆时间过后的z秒后从给出的w（w>=x)张扑克牌中找出其中的记忆过的扑克牌\n");
    printf("*******************************************************************************************************\n");
    printf("\n");

    /*test random*/
    /*
    int tpe;
    srand((unsigned)time(NULL));
    for (tpe = 0; tpe < 10; tpe++)
        printf("%d ", rand() % 4);
    printf("\n");
    printf("现在设置x,y,z,w:\n");*/

    /*set paramater*/
    int x, y, z, w;
    int eff_x, eff_y, eff_z, eff_w;
    int setsand;
    printf("设置记忆卡牌数x，输入数字后回车: \n");
    eff_x = scanf("%d", &x);
    while (x > 52 || x < 1 || eff_x != 1) {
        printf("x is out of range, type a number and press enter again to set x:\n");
        eff_x = scanf("%d", &x);
    }
    printf("设置记忆时间y(s)，输入数字后回车: \n");
    eff_y = scanf("%d", &y);
    while (eff_y != 1) {
        printf("y is out of range, type a number and press enter again to set y:\n");
        eff_y = scanf("%d", &y);
    }
    printf("设置记忆过后空缺时间z(s)，输入数字后回车: \n");
    eff_z = scanf("%d", &z);
    while (eff_z != 1) {
        printf("z is out of range, type a number and press enter again to set z:\n");
        eff_z = scanf("%d", &z);
    }
    printf("设置总共的卡牌数w(w>=x)，输入数字后回车: \n");
    eff_w = scanf("%d", &w);
    while (eff_w != 1 || w > 52 || w < x) {
        printf("w is out of range, type a number and press enter again to set w:\n");
        eff_w = scanf("%d", &w);
    }
    printf("稍等片刻……\n");
    /*initialize pocket*/
    int pocket[13][4];
    int correct[52];
    int i, j;
    int number, suit;
    for (i = 0; i < 13; i++)
        for (j = 0; j < 4; j++) {
            pocket[i][j] = UNCHOOSEN;
        }
    for (i = 0; i < 52; i++) {
        correct[i] = 0;
    }
    srand((unsigned)time(NULL));
    /*set the pocket to choose*/
    for (i = 0; i < x; i++) {
        
        number = rand(10003) % 13;
        suit = rand(10086) % 4;
        Sleep(10);
        if (pocket[number][suit] == UNCHOOSEN)
            pocket[number][suit] = RIGHTPOCKER;
        else {
            i--;
        }
    }
    /*set the mix pocket*/
    srand((unsigned)time(NULL));
    for (i = 0; i < w - x; i++) {
        //srand((unsigned)time(NULL));
        number = rand(10048) % 13;
        suit = rand(10000) % 4;
        if (pocket[number][suit] == UNCHOOSEN)
            pocket[number][suit] = MIXPOCKER;
        else {
            i--;
        }
    }
    /*show the choose pocket*/
    system("cls");
    int remembertime;
    remembertime = y;
    while (y) {
        printf("here is the pocket to remember:\n");
        /*output the pockets to remember*/
        for (i = 0; i < 13; i++)
            for (j = 0; j < 4; j++) {
                if (pocket[i][j] == RIGHTPOCKER) {
                    printf("数字:%d\t", i + 1);
                    switch (j) {
                    case 0:
                        printf("花色:黑桃\n");
                        break;
                    case 1:
                        printf("花色：梅花\n");
                        break;
                    case 2:
                        printf("花色：红桃\n");
                        break;
                    case 3:
                        printf("花色：方块\n");
                        break;
                    default:
                        break;
                    }
                }
            }
        /*show the remaining time*/
        printf("剩余记忆时间：%d秒", y--);
        Sleep(1000);
        system("cls");
    }
    /*waiting for a time*/
    
    int z_s;
    //z_s = z * 60;
    z_s = z;
    while (z_s) {
        printf("记忆时间已过\n");
        printf("请在%d秒后从一堆牌中后选出你记住的牌\n", z_s--);
        Sleep(1000);
        system("cls");
    }
    /*choose the pockets*/
    int index;
    printf("请从以下牌中选择(输入)出刚才出现过的%d张牌的编号:\n", x);
    printf("输入示例：\n1 3 7 10\n");
    printf("----------------------------------\n");
    for (i = 0, index = 1; i < 13; i++)
        for (j = 0; j < 4; j++) {
            if (pocket[i][j] != UNCHOOSEN) {
                if (pocket[i][j] == RIGHTPOCKER)correct[index - 1] = 1;
                printf("编号：%d\t", index++);
                printf("数字:%d\t", i + 1);
                switch (j) {
                case 0:
                    printf("花色:黑桃\n");
                    break;
                case 1:
                    printf("花色：梅花\n");
                    break;
                case 2:
                    printf("花色：红桃\n");
                    break;
                case 3:
                    printf("花色：方块\n");
                    break;
                default:
                    break;
                }
            }
        }
    printf("----------------------------------\n");
    printf("输入之前出现过的牌的编号:\n");
    i = 0; j = 0;
    int tempNum;
    while (i < x) {
        scanf("%d", &tempNum);
        if (tempNum > 52) {
            printf("过大编号");
            continue;
        }
        else if (correct[tempNum - 1]) {
            j++;
            correct[tempNum - 1] = 0;
        }
        i++;
    }
    printf("----------------------------------\n");
    printf("挑战结果如下:\n");
    
    printf("*****记忆时长：%d 秒\n", remembertime);
    printf("*****记忆之后的间隔时间：%d 秒\n", z);
    printf("*****挑战从%d张牌中找出之前记忆过的%d张\n", w, x);
    printf("*****正确率：%d/%d\n", j, x);

    printf("----------------------------------\n");
    /*show the right result*/
    printf("正确结果：\n");
    for (i = 0; i < 13; i++)
        for (j = 0; j < 4; j++) {
            if (pocket[i][j] == RIGHTPOCKER) {
                printf("数字:%d\t", i + 1);
                switch (j) {
                case 0:
                    printf("花色:黑桃\n");
                    break;
                case 1:
                    printf("花色：梅花\n");
                    break;
                case 2:
                    printf("花色：红桃\n");
                    break;
                case 3:
                    printf("花色：方块\n");
                    break;
                default:
                    break;
                }
            }
        }
    /*end*/
    system("pause");
    return 0;
}
