#include "xlplayer.h"
#include <conio.h>
#include <iostream>

using namespace std;

int _player::jud_cheat(int gst) {
	if (gst == -2) row_def1++;
	if (gst == -3) row_def2++;
	if (row_def1 >= 5 || row_def2 >= 4) return 1;
	if (gst > pt) return 1;
	return 0;
}

int player::getgesture(int ai = 0) {
	
	return 0;
}

string getinput() {
	char password[100];
	int index = 0;
	while (1)
	{
		char ch;
		ch = getch();
		if (ch == 8) //ÍË¸ñ¼ü
		{
			if (index != 0)
			{
				cout << char(8) << " " << char(8);
				index--;
			}
		}
		else if (ch == '\r') //»Ø³µ¼ü
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