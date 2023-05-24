#pragma once
class _player {
protected:
	int pt; //降龙个数
	int row_def1; //连续扛次数
	int row_def2; //连续大扛次数 
	int died; //是否已出局
	int ai; //AI号码
public:
	int jud_cheat(int gst); //判定赖死
	virtual int getgesture(int) = 0;
};

class player : public _player {
	int getgesture(int);
};

class cpu : public _player {
	int getgesture(int);
};