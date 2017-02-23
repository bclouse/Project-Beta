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
	int n = 20;
	int iter = 1000;
	int sr = 30;
	int *info = new int[iter]();
	FILE *learning;

	cout << "How large (6-20) do you want the square grid? ";
	cin >> n;
	cout << "How many Statisical Runs (1-30)? ";
	cin >> sr;

	int size[2] = {n,n};
	int goal[2] = {n-2,n-2};
	GridWorld grid(size[0],size[1],goal[0],goal[1]);
	Agent Dexter(size[0]*size[1], 0.1, 0.1, 0.9, &grid);
	int results[4] = {0};

	Dexter.set_state(2*n+2);

	for (int j = 0; j < sr; j++) {
		for (int i = 0; i < 1000; i++) {
			info[i] += Dexter.action(n);
		}
		Dexter.reset();
	}

	learning = fopen("Learning.txt", "w+");
	for (int i = 0; i < 1000; i++) {
		fprintf(learning, "%d\t%.3f\n", i, (float)info[i]/sr);
	}

	Dexter.display();

	fclose(learning);
	grid.clear();
	Dexter.clear();
	delete info;
	return 0;
}