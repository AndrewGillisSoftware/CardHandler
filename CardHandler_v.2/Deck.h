#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Card.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <ctime>

using json = nlohmann::json;
using namespace sf;
using namespace std;

class Deck : public Sprite
{
public:
	Deck();
	~Deck();
	Deck(string data);

	Card drawCard();
	void discardCard(Card);
	void shuffle();

private:
	json record;

	vector<Card> drawable;
	vector<Card> discard;
	vector<Card> inAHand;
};

