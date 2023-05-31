// XianglongGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "global.h"

struct Node {   //节点结构体
  //Node* prior;
    int player;
    int round;
    int gst;
    Node* next;
};

int gstok[60], ql = 1, qr;    //机器可用操作列表
unsigned long long ran;    //随机数

mt19937_64 random(std::random_device{}()); //随机数
//manager xlgame; //管理类
char buffer[50000];



int rounds = 0;    //回合计数
int Gst0, Gst1;   //操作类型
int pt0, pt1;     //降龙积攒个数
int finished = 0; //游戏结束判定
int row11, row12, row21, row22; //连续扛/大扛个数


int cpu_types[] = { -1,0,1,2,3,4,5,6 };   //机器AI号库，-1为测试模式开关
int cpu_type;         //人机对战机器AI号
int cpu_type1, cpu_type2; //机器对打机器AI号
int testing_mode = 0;   //测试模式（机器对打并记录），0关/1开
int test_count;         //测试模式下自动对战次数
int test_win1, test_win2; //测试模式下双方获胜次数

Node memo0 = { 0,0,0,0 };
Node memo1 = { 1,0,0,0 };

//链表长度函数 （摘自OI wiki）
int size(Node* head) {
    int size = 0;
    for (Node* p = head; p != nullptr; p = (p->next)) size++;
    return size;
}

//链表插入函数
void insertNode(int player, int round, int gst, Node* p) {
    Node* t = p;
    Node* node = (Node*)malloc(sizeof(Node));
    node->player = player;
    node->round = round;
    node->gst = gst;
    node->next = nullptr;
    while (t->next != nullptr) {
        t = t->next;
    }
    t->next = node;
}

//链表删除函数
void deleteNode(Node* p) {
    p->player = p->next->player;
    p->round = p->next->round;
    p->gst = p->next->gst;
    Node* t = p->next;
    p->next = p->next->next;
    free(t);
}

//链表销毁函数
void destroyNode(Node* head) {
    Node* p;
    while (head->next != nullptr) {
        p = head->next;
        head->next = p->next;
        free(p);
    }
}

//打印游戏规则
void print_GameRule() {
    printf("====================降龙·拍手游戏规则====================\n");
    printf("每回合，玩家拍手一次之后同时出手势操作：\n");
    printf("各操作效果如下：\n");
    printf("《降龙》：积攒1个降龙，用于攻击；\n");
    printf("《单掌》：消耗1个降龙，对目标造成1点伤害；\n");
    printf("《双掌》：消耗2个降龙，对目标造成2点伤害；\n");
    printf("《三连》：消耗3个降龙，对目标造成3点伤害；\n");
    printf("《全发》：消耗5个降龙，对目标造成5点伤害；\n");
    printf("《六脉》：消耗6个降龙，对目标造成6点伤害；\n");
    printf("《九阴》：消耗9个降龙，对目标造成9点伤害；\n");
    printf("《降龙十八掌》：消耗18个降龙，秒杀目标；\n");
    printf("《 防 》：抵御受到的攻击，无法防御等级为《全发》以上的伤害；\n");
    printf("《 扛 》：防御，无法防御等级为《九阴》及以上的伤害，且不能连续出5次；\n");
    printf("《大扛》：防御，无法防御等级为《降龙十八掌》及以上的伤害，且不能连续出4次；\n");
    printf("有玩家攻击时：\n");
    printf("若被攻方未防守或防御级别不够则出局；\n");
    printf("两方互相攻击对方时，伤害低者出局，伤害相同则无事发生；\n");
    printf("《赖死判定》：若攻击时没有足够的降龙/连续同种防御超过指定次数，\n");
    printf("则直接以“赖死”为由被淘汰出局。\n");
    printf("=============================================================\n");
}

//开始游戏
int Gamestart() {
    int cpu_type,bad = 1;
    if (test_count == 0) {
        do {
            printf("===开始游戏！===\n");
            Gst0 = 0;
            Gst1 = 0;
            pt0 = 0;
            pt1 = 0;
            rounds = 0;
            finished = 0;
            row11 = row12 = row21 = row22 = 0;
            destroyNode(&memo0);
            destroyNode(&memo1);
            printf("请输入机器出手类型（对应序号的数字）：\n");
            printf("0) 随机出手·全 随 机（难度：★☆☆☆☆） \n");
            printf("1) 随机出手·进 攻 型（难度：★★☆☆☆） \n");
            printf("2) 随机出手·防 御 型（难度：★★☆☆☆） \n");
            printf("3) 随机出手·速 攻 型（难度：★★★☆☆） \n");
            printf("4) 随机出手·极 速 型（难度：★★★☆☆） \n");
            printf("5) 随机出手·大道至简（难度：★★★☆☆） \n");
            printf("6) 随机出手·好事成双（难度：★★★☆☆） \n");
            scanf_s("%d", &cpu_type);
            for (int i = 0; i < (sizeof(cpu_types) / sizeof(int)); i++) {
                if (cpu_type == cpu_types[i]) bad = 0;
            }
            while (getchar() != '\n') { bad = 1; continue; }
            if (bad == 1) printf("请输入正确的数字代码：");
        } while (bad != 0);
    } else {
        printf("======机器对打·第 %d 局======\n", test_win1 + test_win2 + 1);
        Gst0 = 0;
        Gst1 = 0;
        pt0 = 0;
        pt1 = 0;
        rounds = 0;
        finished = 0;
        row11 = row12 = row21 = row22 = 0;
        destroyNode(&memo0);
        destroyNode(&memo1);
        cpu_type = -1;
    }

    srand((unsigned)(time(NULL) + ran));
    ran = rand();    //生成随机数
    return cpu_type;
}

//打印技能名
void print_gst(int gesture) {
    switch (gesture) {
    case 0:
        printf("《降龙》");
        break;
    case 1:
        printf("《单掌》");
        break;
    case 2:
        printf("《双掌》");
        break;
    case 3:
        printf("《三连》");
        break;
    case 5:
        printf("《全发》");
        break;
    case 6:
        printf("《六脉》");
        break;
    case 9:
        printf("《九阴》");
        break;
    case 18:
        printf("《降龙十八掌》");
        break;
    case 36:
        printf("《三十六掌》");
        break;
    case 72:
        printf("《七十二掌》");
        break;
    case -1:
        printf("《 防 》");
        break;
    case -2:
        printf("《 扛 》");
        break;
    case -3:
        printf("《大扛》");
        break;
    case -4:
        printf("《超级扛》");
        break;
    case -5:
        printf("《终极扛》");
        break;
    default:
        printf("《未知》");
        break;
    }
}

//打印技能名到文件
void fprint_gst(int gesture,FILE* filep) {
    switch (gesture) {
    case 0:
        fputs("《降龙》", filep);
        break;
    case 1:
        fputs("《单掌》", filep);
        break;
    case 2:
        fputs("《双掌》", filep);
        break;
    case 3:
        fputs("《三连》", filep);
        break;
    case 5:
        fputs("《全发》", filep);
        break;
    case 6:
        fputs("《六脉》", filep);
        break;
    case 9:
        fputs("《九阴》", filep);
        break;
    case 18:
        fputs("《降龙十八掌》", filep);
        break;
    case 36:
        fputs("《三十六掌》", filep);
        break;
    case 72:
        fputs("《七十二掌》", filep);
        break;
    case -1:
        fputs("《 防 》", filep);
        break;
    case -2:
        fputs("《 扛 》", filep);
        break;
    case -3:
        fputs("《大扛》", filep);
        break;
    case -4:
        fputs("《超级扛》", filep);
        break;
    case -5:
        fputs("《终极扛》", filep);
        break;
    default:
        fputs("《未知》", filep);
        break;
    }
}


//机器方   0
int go_CPU(int type,int ptself,int ptoppo,int row1,int row2, Node* memoself, Node* memooppo) {    //CPUAI号，本方pt，对方pt
    int gst;
    int rt = rand();
    long long rtt = (1ll << 48);
    for (int i = 0; i < rt % 8; i++) {
        ran = (25214903917 * ran) % (rtt - 1) + rand();
    }
    /*  //测试用代码
    printf("%d\n", r);
    printf("%d\n", size(&memo0));
    */
    switch (type) {
    case 0: {
        if (rounds == 1) {
            gst = 0;
        } else if (ptself >= 18) {
            gst = 18;
        } else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 9) gstok[++qr] = 9;
            if (ptself >= 6) gstok[++qr] = 6;
            if (ptself >= 5) gstok[++qr] = 5;
            if (ptself >= 3) gstok[++qr] = 3;
            if (ptself >= 2) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 1: {
        if (rounds == 1) {
            gst = 0;
        }
        else if (ptself >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 9) gstok[++qr] = 9;
            if (ptself >= 6) gstok[++qr] = 6;
            if (ptself >= 5) gstok[++qr] = 5;
            if (ptself >= 3) gstok[++qr] = 3;
            if (ptself >= 2) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 9) gstok[++qr] = 9;
            if (ptself >= 6) gstok[++qr] = 6;
            if (ptself >= 5) gstok[++qr] = 5;
            if (ptself >= 3) gstok[++qr] = 3;
            if (ptself >= 2) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 2: {
        /*  原LYB型AI代码
        if (rounds == 1) {
            gst = 0;
        }
        else if (ptself >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 9 && ptself <= 16) gstok[++qr] = 9;
            if (ptself >= 9 && ptself <= 14) gstok[++qr] = 9;
            if (ptself >= 5 && ptself <= 8) gstok[++qr] = 5;
            if (ptself >= 3 && ptself <= 4) gstok[++qr] = 3;
            if (ptself >= 2 && ptself <= 3) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 3) gstok[++qr] = -1;
            if (ptoppo >= 2) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            Node* toppo = memoself;
            while (toppo->next != nullptr) {
                if (toppo->next->next != nullptr) {
                    if (toppo->next->next->next != nullptr) {
                        toppo = toppo->next;
                    }
                    else break;
                }
                else break;
            }
            if (toppo->next != nullptr) {
                if (toppo->next->next != nullptr) {
                    if (toppo->next->next->next != nullptr) {
                        if (toppo->gst == 0 && toppo->next->gst ==0 && toppo->next->next->gst == 0) {
                            if (ptself >= 9) gstok[++qr] = 9;
                            if (ptself >= 6) gstok[++qr] = 5;
                            if (ptself >= 2) gstok[++qr] = 2;
                            if (ptself >= 1) gstok[++qr] = 1;
                            if (ptself >= 1) gstok[++qr] = 1;
                            if (ptself >= 1) gstok[++qr] = 1;
                        }
                    }
                }
            }
            //if (ptoppo >= 5) gstok[++qr] = 0;

            if (ptoppo == 0) gstok[++qr] = 0;
            if (ptoppo == 0) gstok[++qr] = 0;
            if (ptoppo == 0) gstok[++qr] = 0;
            gstok[++qr] = 0;
            gst = gstok[(ran % qr)];
        }
        break;
        */
        {
            if (rounds == 1) {
                gst = 0;
            }
            else if (ptself >= 18) {
                gst = 18;
            }
            else {
                ql = 1; qr = 0;
                //进攻策略
                if (ptself >= 9) gstok[++qr] = 9;
                if (ptself >= 6) gstok[++qr] = 6;
                if (ptself >= 5) gstok[++qr] = 5;
                if (ptself >= 3) gstok[++qr] = 3;
                if (ptself >= 2) gstok[++qr] = 2;
                if (ptself >= 1) gstok[++qr] = 1;
                //防守策略
                if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
                if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
                if (ptoppo >= 1) gstok[++qr] = -1;
                if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
                if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
                if (ptoppo >= 1) gstok[++qr] = -1;
                //续航策略
                gstok[++qr] = 0;
                gst = gstok[(ran % qr) + ql];
            }
            break;
        }
    }
    case 3: {
        if (rounds == 1) {
            gst = 0;
        }
        else if (ptself >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            if (ptself <= 0) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 4: {
        if (rounds == 1) {
            gst = 0;
        }
        else if (ptself >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            if (ptself <= 0) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 5: {
        if (rounds == 1) {
            gst = 0;
        } else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 1) gstok[++qr] = 1;
            //防守策略
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            if (ptself <= 0) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 6: {
        if (rounds == 1) {
            gst = 0;
        }
        else {
            ql = 1; qr = 0;
            //进攻策略
            if (ptself >= 2) gstok[++qr] = 2;
            //防守策略
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //续航策略
            if (ptself <= 1) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    default:
        printf("机器出手程序异常！");
        return -127;
    }
    return gst;
}

//玩家方   1
int go_Player() {
    int bad = 1;
    int gst;
    char input;
    int inputs[] = { '0','1','2','3','5','6','9','q','w','e','k' };
    printf("*************************************\n");
    printf("操作列表：\n");
    printf("0) 降龙   q)  防    w)  扛    e) 大扛\n");
    printf("1) 单掌   2) 双掌   3) 三连   5) 全发\n");
    printf("6) 六脉   9) 九阴   k) 降龙十八掌\n");
    printf("输入一个数字/小写字母代表你的操作：");
    do {
        input = getchar();
        while (getchar() != '\n') { bad = 1; continue; }
        for (int i = 0; i < (sizeof(inputs) / sizeof(int)); i++) {
            if (input == inputs[i]) bad = 0;
        }
        if (bad == 1) printf("输入不正确，请重新输入：");
    } while (bad != 0);
    //处理输入
    switch (input) {
    case '0':
        gst = 0;
        break;
    case '1':
        gst = 1;
        break;
    case '2':
        gst = 2;
        break;
    case '3':
        gst = 3;
        break;
    case '5':
        gst = 5;
        break;
    case '6':
        gst = 6;
        break;
    case '9':
        gst = 9;
        break;
    case 'q':
        gst = -1;
        break;
    case 'w':
        gst = -2;
        break;
    case 'e':
        gst = -3;
        break;
    case 'k':
        gst = 18;
        break;
    default:
        gst = -127;
        break;
    }
    return gst;
}

//处理双方出手
int deal(int gesture1, int gesture2, int* pt1, int* pt2) {
    //记录回合
    insertNode(0, rounds, gesture1, &memo0);
    insertNode(1, rounds, gesture2, &memo1);
    //处理赖死
    {
        if (gesture1 == -2) row11++;
        if (gesture2 == -2) row12++;
        if (gesture1 == -3) row21++;
        if (gesture2 == -3) row22++;
        if (testing_mode == 1){
            if (gesture1 > *pt1) {
                printf("CPU1点数不够！赖死出局！");
                finished = 1;
                return -63;
            }
            if (gesture2 > *pt2) {
                printf("CPU2点数不够！赖死出局！");
                finished = -1;
                return -63;
            }
            if (row11 >= 5) {
                printf("CPU1连续扛5次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row12 >= 5) {
                printf("CPU2连续扛5次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row21 >= 4) {
                printf("CPU1连续大扛4次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row22 >= 4) {
                printf("CPU2连续大扛4次！赖死出局！");
                finished = 1;
                return -31;
            }
        } else {
            if (gesture1 > *pt1) {
                printf("机器点数不够！赖死出局！");
                finished = 1;
                return -63;
            }
            if (gesture2 > *pt2) {
                printf("玩家点数不够！赖死出局！");
                finished = -1;
                return -63;
            }
            if (row11 >= 5) {
                printf("机器连续扛5次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row12 >= 5) {
                printf("玩家连续扛5次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row21 >= 4) {
                printf("机器连续大扛4次！赖死出局！");
                finished = 1;
                return -31;
            }
            if (row22 >= 4) {
                printf("玩家连续大扛4次！赖死出局！");
                finished = 1;
                return -31;
            }
        }
        if (gesture1 != -2) row11 = 0;
        if (gesture2 != -2) row12 = 0;
        if (gesture1 != -3) row21 = 0;
        if (gesture2 != -3) row22 = 0;
    }
    //扣除降龙/积攒降龙
    {
        if (gesture1 > 0) {
            *pt1 -= gesture1;
        }
        if (gesture2 > 0) {
            *pt2 -= gesture2;
        }
        if (gesture1 == 0) {
            *pt1 += 1;
        }
        if (gesture2 == 0) {
            *pt2 += 1;
        }
    }
    finished = 0; //初始化
    if (gesture1 > 0 && gesture2 > 0) {     //两方攻击
        if (gesture1 > gesture2) finished = -1;
        if (gesture1 < gesture2) finished = 1;
        if (gesture1 == gesture2) finished = 0;
    }
    //仅一方攻击
    if (gesture1 * gesture2 <= 0) {
        if (gesture1 > 0 && gesture2 == 0) finished = -1;
        if (gesture1 == 0 && gesture2 > 0) finished = 1;
        if (gesture1 >= 5 && (gesture2 == -1)) finished = -1;
        if (gesture2 >= 5 && (gesture1 == -1)) finished = 1;
        if (gesture1 >= 9 && (gesture2 == -1 || gesture2 == -2)) finished = -1;
        if (gesture2 >= 9 && (gesture1 == -1 || gesture1 == -2)) finished = 1;
        if (gesture1 >= 18 && (gesture2 < 0 && gesture2 >= -3)) finished = -1;
        if (gesture2 >= 18 && (gesture1 < 0 && gesture1 >= -3)) finished = 1;
    }
    //两方均不攻击
    if (gesture1 < 0 && gesture2 < 0) finished = 0;

    return 0;
}

//输出游戏记录到文件
void output_progressing(FILE* filep, Node* head1, Node* head2) {
    Node* p1 = head1;
    Node* p2 = head2;
    p1 = p1->next;
    p2 = p2->next;
    while (NULL != p1) {
        if (testing_mode == 1)
        {
            fputs("\n ",filep);
            fprint_gst((*p1).gst, filep);
            fputs("  <==CPU1 ", filep);
            fputs("  CPU2==>  ", filep);
            fprint_gst((*p2).gst, filep);
            fputs("  \n", filep);
        }
        if (testing_mode != 1)
        {
            fputs("\n ", filep);
            fprint_gst((*p1).gst, filep);
            fputs("  <==机器 ", filep);
            fputs("  玩家==>  ", filep);
            fprint_gst((*p2).gst, filep);
            fputs("  \n", filep);
        }
        p1 = p1->next;
        p2 = p2->next;
    }
}

int continue_game() {
    int bad = 1;
    int opt;
    int opts[] = { 0,1 };
    //数据存储
    {
        FILE* f1p;
        fopen_s(&f1p, "record.txt", "a+");
        fputs("------------------------------------\n", f1p);
        fputs("游戏时间: ",f1p);
        //输出时间
        {
            time_t PTime = 0;
            time_t times;
            time(&times); // 时间戳，可以用time(&mytime);获取当前时间戳
            struct tm* timeP = (tm*)malloc(sizeof(tm));
            
            //char buffer[128];
            /*
            利用东八区（北京时间,其他国家，美国，英国等，需要相应的进行加或者减X小时），
            则真正的换算时间戳为
            */
            PTime = times + (0LL * 60 * 60);
            localtime_s(timeP,&PTime);    // 转换
            fprintf(f1p, "%d/%d/%d %d:%d:%d\n", 1900 + timeP->tm_year, 1 + timeP->tm_mon, timeP->tm_mday, timeP->tm_hour, timeP->tm_min, timeP->tm_sec);
        }
        if (testing_mode == 1) {
            fputs("模式：机器对打模式  ",f1p);
            fprintf(f1p, "AI: %d <=> AI: %d\n", cpu_type1, cpu_type2);
        } else {
            fputs("模式：人机对战模式  ", f1p);
            fprintf(f1p, "AI: %d <=> 玩家\n", cpu_type);
        }
        fputs("游戏回合流程: \n",f1p);
        output_progressing(f1p, &memo0, &memo1);
        if (testing_mode == 1) {
            if (finished == -1)
                fputs("CPU1获胜", f1p);
            if (finished == 1)
                fputs("CPU2获胜", f1p);
        } else {
            if (finished == -1)
                fputs("机器获胜", f1p);
            if (finished == 1)
                fputs("玩家获胜", f1p);
        }
        fprintf(f1p,"总回合数：%d\n", rounds);
        fprintf(f1p, "双方剩余降龙：[%2d]<==>[%2d]\n", pt0, pt1);
        if (test_count > 0) {
            test_count--;
            if (test_count == 0) {
                fprintf(f1p, "************************************\n");
                fprintf(f1p, "本次自动对局共 %d 次，双方战绩如下：\n", test_win1 + test_win2);
                fprintf(f1p, "[AI%d] vs [AI%d] == %d : %d\n", cpu_type1, cpu_type2, test_win1, test_win2);
                fprintf(f1p, "[AI%d]胜率：%.2lf%%\n", cpu_type1, (test_win1 / (double)(test_win1 + test_win2)) * 100);
                fprintf(f1p, "[AI%d]胜率：%.2lf%%\n", cpu_type2, (test_win2 / (double)(test_win1 + test_win2)) * 100);
                fprintf(f1p, "************************************\n");

                printf("************************************\n");
                printf("本次自动对局共 %d 次，双方战绩如下：\n", test_win1 + test_win2);
                printf("[AI%d] vs [AI%d] == %d : %d\n", cpu_type1, cpu_type2, test_win1, test_win2);
                printf("[AI%d]胜率：%.2lf%%\n", cpu_type1, (test_win1 / (double)(test_win1 + test_win2)) * 100);
                printf("[AI%d]胜率：%.2lf%%\n", cpu_type2, (test_win2 / (double)(test_win1 + test_win2)) * 100);
                printf("************************************\n");
            }
        }
        fclose(f1p);
    }
    if (test_count > 0) return 0;
    testing_mode = 0;
    test_win1 = test_win2 = 0;
    printf("***************************\n");
    printf("游戏结束！接下来的操作：\n");
    printf("0) 新的一局   1)看一遍规则再重来\n其他)退出游戏\n");
    printf("输入数字决定接下来的操作：");
    scanf_s("%d", &opt);
    for (int i = 0; i < (sizeof(opts) / sizeof(int)); i++) {
        if (opt == opts[i]) bad = 0;
    }
    while (getchar() != '\n') { bad = 1; continue; }
    if (bad == 1) printf("退出游戏！\n"), opt = 2;
    return opt;
}

//主函数
int main()
{
    printf("====谨此，纪念我的小学和中学时光====\n");
    printf("===降龙·拍手游戏===\n");
    printf("==Programmed by aixintao2022==\n");
    printf("version: v2.0.0-pre0\n");
    int opt;
    print_GameRule();
    do {
        cpu_type = Gamestart();
        if (cpu_type != -1) {   //常规模式
            do {
                rounds++;
                printf("《第 %d 回合》\n", rounds);
                Gst0 = go_CPU(cpu_type, pt0, pt1, row11, row21, &memo0, &memo1);    //机器出手
                Gst1 = go_Player();         //玩家出手
                //打印双方出手
                {
                    printf("\n ");
                    print_gst(Gst0);
                    printf("  <==机器 ");
                    printf("  玩家==>  ");
                    print_gst(Gst1);
                    printf("  \n\n");
                }
                deal(Gst0, Gst1, &pt0, &pt1);  //处理出手结果
            } while (finished == 0);
            switch (finished) {
            case -1:
                printf("机器获胜！\n");
                break;
            case 1:
                printf("玩家获胜！\n");
                break;
            default:
                printf("程序异常1！\n");
                break;
            }
            switch (opt = continue_game()) {    //游戏结束，决定是否退出或继续
            case 0:
                break;
            case 1:
                print_GameRule();
                break;
            case 2:
                break;
            default:
                printf("程序异常2！\n");
                break;
            }
        }
        else {    //机器对打模式
            testing_mode = 1;
            printf("请输入CPU1的AI号：");
            scanf_s("%d", &cpu_type1);
            printf("请输入CPU2的AI号：");
            scanf_s("%d", &cpu_type2);
            printf("请输入自动对战次数：");
            scanf_s("%d", &test_count);
            do {
                Gamestart();
                do {
                    rounds++;
                    Gst0 = go_CPU(cpu_type1, pt0, pt1, row11, row21, &memo0, &memo1);    //机器1出手
                    Gst1 = go_CPU(cpu_type2, pt1, pt0, row12, row22, &memo1, &memo0);    //机器2出手
                    printf("《第 %d 回合》\n", rounds);
                    //打印双方出手
                    {
                        printf("\n ");
                        print_gst(Gst0);
                        printf("  <==CPU1 ");
                        printf("  CPU2==>  ");
                        print_gst(Gst1);
                        printf("  \n\n");
                    }
                    deal(Gst0, Gst1, &pt0, &pt1);  //处理出手结果
                } while (finished == 0);
                switch (finished) {
                case -1:
                    printf("机器1获胜！\n");
                    test_win1++;
                    break;
                case 1:
                    printf("机器2获胜！\n");
                    test_win2++;
                    break;
                default:
                    printf("程序异常4！\n");
                    break;
                }
                switch (opt = continue_game()) {    //游戏结束，决定是否退出或继续
                case 0:
                    break;
                case 1:
                    print_GameRule();
                    break;
                case 2:
                    break;
                default:
                    printf("程序异常2！\n");
                    break;
                }
            } while (test_count > 0);
        }
    } while (opt != 2);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
