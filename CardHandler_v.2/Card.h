#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
#include <string>
using namespace sf;
using namespace std;

class Card : public Sprite
{
public:
	Card();
	Card(string spec, Vector2f pos);
	~Card();

	string getSpec();
	void setSpec(string);

private:
	string spec;
};

