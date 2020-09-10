#include "pch.h"
#include "Deck.h"


Deck::Deck()
{
}


Deck::~Deck()
{
}

Deck::Deck(string data)
{
	srand(time(NULL));

	Texture* temp;
	Card fill;
	//loads file into json
	ifstream card_file(data, ifstream::binary); card_file >> record;
	float scale = record["DIMENSIONS"]["scale"];

	for (int i = 0; i < record["CARDS"].size(); i++)
	{
		drawable.push_back(fill);
		drawable.at(i).setSpec(record["CARDS"][i]["spec"]);
		temp = new Texture;
		temp->loadFromFile(record["CARDS"][i]["image"]);
		temp->setSmooth(true);
		drawable.at(i).setTexture(*temp);
		drawable.at(i).setScale(scale, scale);
		drawable.at(i).setPosition(Vector2f(i * 20, 10));

	}
}

Card Deck::drawCard()
{
	Card drawn;

	inAHand.push_back(drawable.back());
	drawn = drawable.back();
	drawable.pop_back();

	return drawn;
}

void Deck::discardCard(Card c)
{
	if (inAHand.size() > 0)
	{
		for (int i = 0; i < inAHand.size(); i++)
		{
			if (c.getSpec() == inAHand.at(i).getSpec())
			{
				discard.push_back(inAHand.at(i));
				inAHand.erase(inAHand.begin() + i);
			}
		}
	}
}

void Deck::shuffle()
{
	vector<Card> newDrawable;
	int r;
	//shuffle the deck with no discard
	if (discard.size() == 0)
	{
		while (0 < drawable.size())
		{
			r = rand() % drawable.size();
			newDrawable.push_back(drawable.at(r));
			drawable.erase(drawable.begin() + (r));
		}
		drawable = newDrawable;
	}
	//shuffle the drawable and discard to one deck
	else
	{
		//puts discard into drawable
		for (int i = 0; i < discard.size(); i++)
		{
			drawable.push_back(discard.at(i));
		}
		discard = newDrawable;
		//restarts function to complete action
		shuffle();
	}
}