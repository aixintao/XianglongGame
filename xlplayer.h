#pragma once

#include "global.h"

class _player {
	friend class manager;
protected:
	string name; //the name of player shown to players
	int pt; //��������
	gesture gst; //����
	int row_def1; //����������
	int row_def2; //�����󿸴��� 
	int died; //�Ƿ��ѳ���
	int ai; //AI����
public:
	bool jud_cheat(); //�ж�����
	bool rename(string str);
	virtual int setgesture() = 0;
};

class player : public _player {
	friend class manager;
	int setgesture();
public:
	player();
};

class cpu : public _player {
	friend class manager;
	int setgesture();
public:
	cpu(int ai);
};

//string getinput();