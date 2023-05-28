#pragma once

#include "global.h"

class _player {
	friend class manager;
protected:
	string name; //the name of player shown to players
	int pt; //降龙个数
	gesture gst; //手势
	int row_def1; //连续扛次数
	int row_def2; //连续大扛次数 
	int died; //是否已出局
	int ai; //AI号码
public:
	bool jud_cheat(); //判定赖死
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