#include "global.h"

using namespace std;

bool player::jud_cheat() {
    if (this->gst > 0) pt -= this->gst;
    if (this->gst == -2) row_def1++;
    if (this->gst == -3) row_def2++;
    bool cheat = false;
    //judging conditions
    {
        if (row_def1 > maxrow1) cheat = true;
        if (row_def2 > maxrow2) cheat = true;
        if (pt < 0) cheat = true;
    }
    return cheat;
}

bool player::rename(string str){
    name = str;
    return false;
}

bool player::setgesture() {
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
    return false;
}

string getinput() {
	string password;
	int index = 0;
	while (1)
	{
		char ch;
		ch = _getch();
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


