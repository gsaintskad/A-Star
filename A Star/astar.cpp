#include "astar.h"
#include"node.h"
#include <vector>
using namespace std;
#define INF 9999


vector<vector<node>>mapCreate()
{
	//MAP GENERATING
	vector<vector<node>>map = { {},{},{},{},{},{},{},{},{} };

	node n;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map.size(); j++) {
			map[i].push_back(n);
			map[i][j].x = j;
			map[i][j].y = i;
		}
	}
	//wall defining
	node wall;
	wall.entity = '#';
	wall.weight = INF;
	wall.isVisited = true;
	wall.isChecked = true;

	//Wall installation
	map[2][7] = wall;
	map[2][6] = wall;
	map[6][6] = wall;
	map[3][6] = wall;
	map[3][5] = wall;
	map[4][5] = wall;
	map[5][5] = wall;
	map[5][6] = wall;
	map[2][3] = wall;
	map[3][3] = wall;
	map[4][3] = wall;
	map[5][3] = wall;
	map[6][3] = wall;
	map[7][3] = wall;
	map[7][4] = wall;

	int sz = map.size() - 1;
	for (int i = 0; i < map.size(); i++) {
		map[0][i] = wall;
		map[i][0] = wall;
		map[sz][i] = wall;;
		map[i][sz] = wall;
	}
	return map;
}
void print(vector<vector<node>> m)
{
	cout << "    X   ";
	for (int i = 1; i < m.size() - 1; i++) {
		cout << i << "   ";
	}
	cout << endl;
	for (int i = 0; i < m.size(); i++) {
		if (i == 0) {
			cout << "Y   ";
		}
		else if (i < 8) {
			cout << i << "   ";
		}
		else { cout << "    "; }
		for (int j = 0; j < m[i].size(); j++) {
			cout << m[i][j].entity << "   ";
		}
		cout << endl << endl;
	}
}

void print_output(vector<node>& output, node* end, vector<vector<node>>* map)
{
	cout << endl << endl << "\t\t PATH , YOU NEED TO WALK TO GET THE TARGET : " << "\n\n\n" << "START : ";
	for (int i = output.size() - 1; i > -1; i--) {

		cout << "[" << output[i].y << " , " << output[i].x << "] ";
		if (i != 0)
			cout << " -> ";
	}
	cout << " FINISH !!!" << endl;
	*end = output[0];

	cout << "\t \n TOTAL DISTANCE :" << end->dwalked << endl;


}
double dset(node a, node b)
{
	double n = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

	return n;
}

double eset(node a, node b)
{
	double n = abs(a.x - b.x) + abs(a.y - b.y);
	return n;
}

void sortv(vector<node>* q)
{
	for (int i = 0; i < q->size(); i++) {
		for (int j = 0; j < q->size(); j++) {
			if ((*q)[i].weight < (*q)[j].weight) {
				node t = (*q)[i];
				(*q)[i] = (*q)[j];
				(*q)[j] = t;
			}
		}
	}
}

node takeprv(vector<vector<node>>* m, node* s, node* n, node* e, vector<node>* op)
{
	node a = (*(&((*m)[n->previous[1]])))[n->previous[0]];
	if (a.x == s->x && a.y == s->y) {
		op->push_back(a);
		return a;
	}
	else {

		op->push_back(a);
		return takeprv(m, s, &a, e, op);
	}
}

bool endcheck(node* n, node* e)
{
	return n->distend == 0;
}

void neighbourcheck(vector<vector<node>>* m, vector<node>* q, node* n, node* e, vector<node>* o, node* s)
{
	if (!endcheck(n, e)) {
		n->isVisited = true;
		n->isChecked = true;
		//checking the neighbour cells in radius of 1 cell
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				node* N = &(*(&((*m)[n->y + i])))[n->x + j];
				if (N->entity != '#' && !N->isVisited) {
					N->distend = eset(*N, *e);
					if (!N->isChecked) {
						for (int k = 0; k < 2; k++) {
							if (k == 0)N->previous[k] = n->x;
							else N->previous[k] = n->y;
						}
						N->distprev = dset(*N, (*(&((*m)[n->y])))[n->x]);
						N->dwalked = (*(&((*m)[n->y])))[n->x].dwalked + N->distprev;
						N->weight = N->dwalked + N->distend;
						N->isVisited = true;

						q->push_back(*N);
						n = &(*q)[0];

					}
					else
					{
						cout << endl;
					}



				}
			}
		}
		q->erase(q->begin());
		sortv(q);
	}
	else {
		cout << "found!";
		o->push_back(*n);
		o->push_back(takeprv(m, s, n, e, o));
		o->erase(o->end() - 1);
		q->clear();
	}
}
vector<node> A_star(vector<vector<node>>* map, node* start, node* end)
{
	//Queue defining 
	vector<node>Q;
	Q.push_back(*start);


	//Output defining
	vector<node> output;

	while (Q.size()) {
		neighbourcheck(map, &Q, &Q[0], end, &output, start);
	}

	for (int i = output.size() - 2; i > 0; i--) {
		(*map)[output[i].y][output[i].x].entity = '*';
	}
	return output;
}