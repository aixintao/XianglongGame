#include "global.h"

bool candefend(gesture& sce, gesture& tgt) {
	//source is not attacking
	if (sce.gst <= 0) return true;
	//source is not aiming to target
	if (find(sce.target.begin(), sce.target.end(),
		tgt.source) == sce.target.end()) return true;

	//source is aiming to target
	if (tgt.gst >= sce.gst) return true;
	if (tgt.gst == -1 && sce.gst < 5) return true;
	if (tgt.gst == -2 && sce.gst < 9) return true;
	if (tgt.gst == -3 && sce.gst < 18) return true;
	return false;
}

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
		_itoa_s(index, buffer, 10);
		x = player("Player " + string(buffer), type);
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
	vector<player*> death;
	//judge cheat
	cout << "Judging cheating..." << endl;
	for (auto it = this->list.begin(); it != this->list.end(); it++) {
		if ((*it).died) continue;
		bool cheat = (*it).jud_cheat();
		if (cheat) {
			death.push_back(&(*it));
		}
	}
	
	//judge gesture
	cout << "Judging gestures..." << endl;
	for (auto it = this->list.begin(); it != this->list.end(); it++) {
		if ((*it).died) continue;
		if ((*it).gst > 0) {
			for (auto p = (*it).gst.target.begin(); p != (*it).gst.target.end(); p++) {
				if (!candefend((*it).gst, (*(*p)).gst)) {
					if (find(death.begin(), death.end(), *p) == death.end()) {
						death.push_back((*p));
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