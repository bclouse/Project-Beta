#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

#define ZERO_TO_ONE (double)rand()/RAND_MAX

#ifndef CLASSES_H
#define CLASSES_H

//==============================
//	GridWorld Class
//===============================

class GridWorld {
private:
	int sizeX, sizeY;
	int goalX, goalY;
	int goal_state;
	int **state_list;
public:
	GridWorld(int, int, int, int);
	int new_state(int,int);
	int give_reward(int);
	void display(int);
	bool found_goal(int);
	void clear();
};

//*==============================
//	Agent Class
//===============================

class Agent{
private:
	float **Q_Table;
	GridWorld *world;
	double e, a, g;	//Epsilon, Alpha, and Gamma
	int size;
	int state;
public:
	Agent(int,double,double,double,GridWorld*);
	void set_state(int);
	// int greedy();
	// void update(int);
	// void decide();
	// void action();
	void clear();
};//*/

//===============================
//	Functions
//===============================

void state2coord(int*,int,int);
int coord2state(int,int,int);

#endif