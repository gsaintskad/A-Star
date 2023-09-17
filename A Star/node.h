#pragma once
class node
{
public:
	int x, y;

	int previous[2];
	char entity;
	bool isVisited;
	bool isChecked;
	double weight;
	double dwalked;
	double distend;
	double distprev;
	node();
};

