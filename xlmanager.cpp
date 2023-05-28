#include "global.h"

bool manager::savelog(){


	return false;
}

bool manager::settotal(){
	cout << "Get the number of players: ";
	int tot = 0;
	cin >> tot;
	total = tot;
	return false;
}

bool manager::setplayer(){
	list.resize(total);
	int index = 0;
	int type = 0;
	for (auto& x : list) {
		index++;
		cout << "Type Intro" << endl;
		cout << "Input the type of player " << index << ": ";
		cin >> type;
		if (!type) {
			x = player();
		} else {
			x = cpu(type);
		}
	}
	return false;
}

bool manager::setgesture(){
	cout << "Enter your gestures!" << endl;
	for (auto& x : list) {
		if (!x.died) x.setgesture();
	}
	return false;
}

bool manager::judgeround(){
	vector<_player&> death;
	//judge cheat
	cout << "Judging cheating..." << endl;
	for (auto& x : list) {
		if (x.died) continue;
		bool cheat = x.jud_cheat();
		if (cheat) {
			death.push_back(x);
		}
	}
	//judge gesture
	cout << "Judging gestures..." << endl;
	for (auto& x : list) {
		if (x.died) continue;
		if (x.gst > 0) {
			for (auto& p : x.gst.target) {
				if (!candefend(x.gst, p.gst)) {
					if (find(death.begin(), death.end(), x) == death.end()) {
						death.push_back(x);
					}
				}
			}
		}


	}
	return false;
}

bool manager::gameover(){


	return false;
}

bool gesture::setgesture(){


	return false;
}

bool gesture::judge(){


	return false;
}

int operator-=(int& x, gesture g) {
	x -= g.gesture * g.target.size();
}
