#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "astar.h"
#include"node.h"
using namespace std;



int main() {
	//MAP GENERATING
	vector<vector<node>>map= mapCreate();
	print(map);

	//start defining
	node start;
	start.entity = '@';

	cout << "Enter start point x,y :\t";
	cin >> start.x;
	cin >> start.y;
	/*start.x = 1;
	start.y = 1;*/
	start.isVisited = true;
	map[start.y][start.x] = start;

	//end defining
	node end;
	end.entity = 'X';
	cout << "Enter end point x,y :\t";
	/*end.x = 7;
	end.y = 1;*/
	cin >> end.x;
	cin >> end.y;
	map[end.y][end.x] = end;

	vector<node> output= A_star(&map, &start, &end);
	print_output(output, &end, &map);
	print(map);

	return 0;
}