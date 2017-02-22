#include "Classes.h"

//===============================
//	GridWorld Class
//===============================

GridWorld::GridWorld(int sx, int sy, int gx, int gy) {
	sizeX = sx; sizeY = sy;
	goalX = gx; goalY = gy;
	goal_state = coord2state(goalX, goalY, sizeX);

	int count = 0;
	state_list = new int*[sx]();
	for (int i = 0; i < sx; i++) {
		state_list[i] = new int[sy]();
		for (int j = 0; j < sy; j++) {
			state_list[i][j] = count++;
		}
	}
}

int GridWorld::new_state(int,int) {

}

int GridWorld::give_reward(int agent_state) {
	int reward = 0;
	if (goal_state == agent_state) {
		reward += 100;
	}
	return reward-1;
}

void GridWorld::display(int agent_state) {
	int current_state;

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			current_state = i*sizeX+j;
			if (current_state == goal_state) {
				if (agent_state == goal_state) {
					cout << "O ";
				} else {
					cout << "G ";
				}
			} else if (current_state == agent_state) {
				cout << "A ";
			} else {
				cout << ". ";
			}
		}
		cout << endl;
	}
}

bool GridWorld::found_goal(int agent_state) {
	if (goal_state == agent_state)
		return true;
	return false;
}

void GridWorld::clear() {
	delete[] state_list;
}

//===============================
//	Agent Class
//===============================

Agent::Agent(int n, double ep, double alpha, double gamma, GridWorld* grid) {
	e = ep;
	a = alpha;
	g = gamma;
	world = grid;
	size = n;
	Q_Table = new float*[n]();
	for (int i = 0; i < n; i++) {
		Q_Table[i] = new float[4]();
	}
	state = 0;
}

void Agent::set_state(int s) {
	state = s;
}

void Agent::clear() {
	delete[] Q_Table;
}

//===============================
//	Functions
//===============================

void state2coord(int loc[2], int sizeX, int state) {
	loc[0] = state%sizeX;
	loc[1] = state/sizeX;
}

int coord2state(int x, int y, int xsize) {
	return y*xsize+x;	
}