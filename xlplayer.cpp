#include "global.h"

using namespace std;

bool _player::jud_cheat() {
    if (gst > 0) pt -= gst;
    if (gst == -2) row_def1++;
    if (gst == -3) row_def2++;
    bool cheat = false;
    //judging conditions
    {
        if (row_def1 > maxrow1) cheat = true;
        if (row_def2 > maxrow2) cheat = true;
        if (pt < 0) cheat = true;
    }
    return cheat;
}

bool _player::rename(string str){
    name = str;

    return false;
}

int player::setgesture() {
    int bad = 1;
    int gst;
    char input;
    int inputs[] = { '0','1','2','3','5','6','9','q','w','e','k' };
    printf("*************************************\n");
    printf("�����б�\n");
    printf("0) ����   q)  ��    w)  ��    e) ��\n");
    printf("1) ����   2) ˫��   3) ����   5) ȫ��\n");
    printf("6) ����   9) ����   k) ����ʮ����\n");
    printf("����һ������/Сд��ĸ������Ĳ�����");
    do {
        input = getchar();
        while (getchar() != '\n') { bad = 1; continue; }
        for (int i = 0; i < (sizeof(inputs) / sizeof(int)); i++) {
            if (input == inputs[i]) bad = 0;
        }
        if (bad == 1) printf("���벻��ȷ�����������룺");
    } while (bad != 0);
    //��������
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

int cpu::setgesture() {    //CPUAI��
    int gst;

    switch (ai) {
    case 0: {
        if (xlgame.round == 1) {
            gst = 0;
        }
        else if (pt >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //��������
            if (ptself >= 9) gstok[++qr] = 9;
            if (ptself >= 6) gstok[++qr] = 6;
            if (ptself >= 5) gstok[++qr] = 5;
            if (ptself >= 3) gstok[++qr] = 3;
            if (ptself >= 2) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            //���ز���
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
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
            //��������
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
            //���ز���
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
            gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 2: {
        /*  ԭLYB��AI����
        if (rounds == 1) {
            gst = 0;
        }
        else if (ptself >= 18) {
            gst = 18;
        }
        else {
            ql = 1; qr = 0;
            //��������
            if (ptself >= 9 && ptself <= 16) gstok[++qr] = 9;
            if (ptself >= 9 && ptself <= 14) gstok[++qr] = 9;
            if (ptself >= 5 && ptself <= 8) gstok[++qr] = 5;
            if (ptself >= 3 && ptself <= 4) gstok[++qr] = 3;
            if (ptself >= 2 && ptself <= 3) gstok[++qr] = 2;
            if (ptself >= 1) gstok[++qr] = 1;
            //���ز���
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
            //��������
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
                //��������
                if (ptself >= 9) gstok[++qr] = 9;
                if (ptself >= 6) gstok[++qr] = 6;
                if (ptself >= 5) gstok[++qr] = 5;
                if (ptself >= 3) gstok[++qr] = 3;
                if (ptself >= 2) gstok[++qr] = 2;
                if (ptself >= 1) gstok[++qr] = 1;
                //���ز���
                if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
                if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
                if (ptoppo >= 1) gstok[++qr] = -1;
                if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
                if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
                if (ptoppo >= 1) gstok[++qr] = -1;
                //��������
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
            //��������
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            //���ز���
            if (ptoppo >= 9 && row2 < 4) gstok[++qr] = -3;
            if (ptoppo >= 5 && row1 < 5) gstok[++qr] = -2;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
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
            //��������
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            if (ptself >= 1) gstok[++qr] = 1;
            //���ز���
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
            if (ptself <= 0) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    case 5: {
        if (rounds == 1) {
            gst = 0;
        }
        else {
            ql = 1; qr = 0;
            //��������
            if (ptself >= 1) gstok[++qr] = 1;
            //���ز���
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
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
            //��������
            if (ptself >= 2) gstok[++qr] = 2;
            //���ز���
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            if (ptoppo >= 1) gstok[++qr] = -1;
            //��������
            if (ptself <= 1) gstok[++qr] = 0;
            gst = gstok[(ran % qr) + ql];
        }
        break;
    }
    default:
        printf("�������ֳ����쳣��");
        return -127;
    }
    return gst;
}

cpu::cpu(int ai){
    this->ai = ai;
    this->pt = 0;
}

string getinput() {
	string password;
	int index = 0;
	while (1)
	{
		char ch;
		ch = getch();
		if (ch == 8) //�˸��
		{
			if (index != 0)
			{
				cout << char(8) << " " << char(8);
				index--;
			}
		}
		else if (ch == '\r') //�س���
		{
			password[index] = '\0';
			cout << endl;
			break;
		}
		else
		{
			cout << "*";
			password[index++] = ch;
		}
	}
	return password;
}
