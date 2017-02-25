#include "Classes.h"

//===============================
//	GridWorld Class
//===============================

GridWorld::GridWorld(int sx, int sy, int gx, int gy) {
	sizeX = sx; sizeY = sy;
	goalX = gx-1; goalY = gy-1;
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

int GridWorld::new_state(int agent_state, int direction) {
	switch (direction) {
		case 0: 				//UP
			if (agent_state/sizeX != 0) {
				agent_state -= sizeX;
			}
			break;
		case 1: 				//RIGHT
			if (agent_state%sizeX != sizeX-1) {
				agent_state++;
			}
			break;
		case 2: 				//DOWN
			if (agent_state/sizeX != sizeY-1) {
				agent_state += sizeX;
			}
			break;
		case 3: 				//LEFT
			if (agent_state%sizeX != 0) {
				agent_state--;
			}
			break;
	}
	return agent_state;
}

int GridWorld::get_reward(int agent_state) {
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
	if (goal_state == agent_state) {
		return true;
	} else {
		return false;
	}
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
	time = 0;
}

void Agent::set_state(int s) {
	origin = state = s;
}

void Agent::clear() {
	delete[] Q_Table;
}

void Agent::display() {
	cout << "GRID INFO\n";
	world->display(state);
	cout << "\nAGENT INFO\n";
	cout << "Epsilon: " << e << "\nAlpha: " << a << "\nGamma: " << g << endl;
	/*
	cout << "Q_Table info:\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%9f\t",Q_Table[i][j]);
		}
		cout << endl;
	}//*/
}

int Agent::action(int sizeX) {
	int direction;
	int testing = 0;
	int nstate;

	while (!(world->found_goal(state))) {

		direction = decide();
		nstate = world->new_state(state,direction);
		update(nstate,direction);
		testing++;
	}
	state = origin;
	return testing;
}

int Agent::decide() {
	if (ZERO_TO_ONE >= e) {
		return rand_maximum(Q_Table[state], 4);
	} else {
		return (int)rand()%4;
	}
}

void Agent::update(int nstate, int dir) {
	int reward = world->get_reward(nstate);
	int Qmax = Q_Table[nstate][rand_maximum(Q_Table[nstate],4)];

	Q_Table[state][dir] += a*(reward + g*Qmax - Q_Table[state][dir]);
	state = nstate;
}

void Agent::reset() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < size; i++) {
			Q_Table[i][j] = 0;
		}
	}
}

void Agent::TestD() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			assert(Q_Table[i][j] <= 100);
		}
	}
}

void Agent::TestE() {
	assert(state == origin);
}

void Agent::TestF(int min,float val) {
	float range = min*0.5;
	assert(val >= min-range && val <= min+range);
}

void Agent::TestG() {
	
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

int rand_maximum(float arr[], int n) {
	vector<int> max;

	max.push_back(0);
	for (int i = 1; i < n; i++) {
		if (arr[max[0]] < arr[i]) {
			max.clear();
			max.push_back(i);
		} else if (arr[max[0]] == arr[i]) {
			max.push_back(i);
		}
	}
	return max[rand()%max.size()];
}