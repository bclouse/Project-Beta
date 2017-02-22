//
//	Bryant Clouse
//	Grid-World
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>
#include "Classes.h"

using namespace std;

int main() {
	srand(time(NULL));
	int n = 10;
	int size[2] = {n,n};
	int goal[2] = {n-2,n-2};
	GridWorld grid(size[0],size[1],goal[0],goal[1]);
	Agent Dexter(size[0]*size[1], 0.1, 0.1, 0.9, &grid);
	int results[4] = {0};

	Dexter.set_state(2*n+2);

	cout << "TESTING INFO\n";
	for (int i = 0; i < 1000; i++) {
		Dexter.action(n,i);
	}

	Dexter.display();

	grid.clear();
	Dexter.clear();
	return 0;
}