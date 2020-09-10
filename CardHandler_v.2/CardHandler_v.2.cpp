
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Deck.h"
#include "Hand.h"
#include "Card.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(VideoMode(1200, 700), "Card Handeler v_2");

	Deck deck("regular.json");
	deck.shuffle();
	Hand hand(Vector2f(100, 100), Vector2f(300, 200), Vector2f(200, 300), Vector2f(.3, .3), Vector2f(.4, .4), 0);
	hand.setPosition(600, 600);

	Card card;

	for (int i = 0; i < 52; i++)
	{
		card = deck.drawCard();
		if (card.getSpec().compare("2D") == 0)
		{
			hand.addCard(card);
		}
	}

	hand.setCards();

	bool tog = true;
	int index;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMoved)
			{
				if (hand.pOnCards((Vector2f)Mouse::getPosition(window)) != -1 && tog == false)
				{
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				index = hand.pOnCards((Vector2f)Mouse::getPosition(window));
				if (index != -1)
				{
					cout << hand.specOSC(index) << endl;
				}
			}

		}

		window.clear();
		hand.display(&window);
		window.display();
	}

	return 0;
}