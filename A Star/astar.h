#pragma once
#include <iostream>
#include <vector>
#include"node.h"

using namespace std;
	double dset(node a, node b);
	double eset(node a, node b);
	void sortv(vector<node>* q);
	node takeprv(vector<vector<node>>* m, node* s, node* n, node* e, vector<node>* op);
	bool endcheck(node* n, node* e);
	void neighbourcheck(vector<vector<node>>* m, vector<node>* q, node* n, node* e, vector<node>* o, node* s);
	vector<vector<node>>mapCreate();
	void print(vector<vector<node>>m);
	vector<node> A_star(vector<vector<node>>* map, node* start, node* end);
	void print_output(vector<node>& output, node* end, vector<vector<node>>* map);

