#include "node.h"


node::node()
{
	this->previous[2];
	this->entity = 'o';
	this->isVisited = false;
	this->isChecked = false;
	this->weight = 0;
	this->dwalked = 0;
}
