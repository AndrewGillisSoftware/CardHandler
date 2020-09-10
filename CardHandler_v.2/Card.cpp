#include "pch.h"
#include "Card.h"


Card::Card()
{
}

Card::Card(string s, Vector2f p)
{
	spec = s;
	this->setPosition(p);
}


Card::~Card()
{
}

string Card::getSpec()
{
	return spec;
}

void Card::setSpec(string s)
{
	spec = s;
}
