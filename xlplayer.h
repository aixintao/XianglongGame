#pragma once
class _player {
protected:
	int pt; //��������
	int row_def1; //����������
	int row_def2; //�����󿸴��� 
	int died; //�Ƿ��ѳ���
	int ai; //AI����
public:
	int jud_cheat(int gst); //�ж�����
	virtual int getgesture(int) = 0;
};

class player : public _player {
	int getgesture(int);
};

class cpu : public _player {
	int getgesture(int);
};