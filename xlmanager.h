#pragma once

//手势类（操作类）
class gesture {
protected:
public:
	int gesture;
	_player& source;
	vector<_player&> target;
	bool setgesture();
	bool judge();
	bool operator >(int x)	{ return (gesture > x);		}
	bool operator <(int x)	{ return (gesture < x);		}
	bool operator ==(int x)	{ return (gesture == x);	}
	friend int operator-=(int& x, class gesture g);
};

//游戏管理类
class manager {
protected:
	int total; //number of players in this game
	int round; //round counting
	vector<_player> list; //the list of the players
	//vector<gesture> gestures;
	int over; //is the game over
	string log; //logs
	bool savelog();
public:
	bool settotal();
	bool setplayer();
	bool setgesture();
	bool judgeround();
	bool gameover();
	friend class _player;
	friend class player;
	friend class cpu;
};
