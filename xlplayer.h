#pragma once

#include "global.h"


class player;

//�����ࣨ�����ࣩ
class gesture {
public:
	int gst;
	player* source;
	vector<player*> target;
	bool setgesture();
	bool judge();
	bool operator >(int x) { return (gst > x); }
	bool operator <(int x) { return (gst < x); }
	bool operator ==(int x) { return (gst == x); }
	friend int operator-=(int x, class gesture g) {
		return x - (g.gst * int(g.target.size()));
	}
	gesture() {
		gst = 0;
		source = 0;
		target.resize(0);
	}
	gesture(const gesture & g){
		gst = g.gst;
		source = g.source;
		target = g.target;
	}
	gesture(player& sce, int total) {
		gst = 0;
		source = &sce;
		target.resize(total);
	}
};

class player {
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
	bool setgesture();
	player() = default;
	player(const player& p) {
		name = p.name;
		pt = p.pt;
		gst = p.gst;
		row_def1 = p.row_def1;
		row_def2 = p.row_def2;;
		died = p.died;;
		ai = p.ai;
	};
	player(const string str, int ai) {
		name = str;
		pt = 0;
		gst = gesture();
		row_def1 = 0;
		row_def2 = 0;
		died = 0;
		ai = ai;
	}
};

//string getinput();