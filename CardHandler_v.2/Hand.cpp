#include "pch.h"
#include "Hand.h"
#include "Collision.hpp"
#include "Collision.cpp"

Hand::Hand()
{
}


Hand::~Hand()
{
}

Hand::Hand(Vector2f position, Vector2f se, Vector2f le, Vector2f smS, Vector2f lgS, int rot)
{
	Texture *t = new Texture;
	t->loadFromFile("Mouse.png");
	mouse.setTexture(*t);
	this->setPosition(position);
	mouse.setTextureRect(sf::IntRect(0, 0, 2, 2));
	smSize = smS;
	lgSize = lgS;
	this->setSize((Vector2f)smSize);
	this->setOrigin(Vector2f(smSize.x / 2, smSize.y));
	smEquation = se;
	lgEquation = le;
	this->setRotation(rot);
}

void Hand::addCard(Card c)
{
	c.setScale(smSize.x, smSize.y);
	hand.push_back(c);
}

Card Hand::removeCard(int index)
{
	Card r;
	r = hand.at(index);
	hand.erase(hand.begin() + index);
	this->setCards();
	return r;
}

void Hand::display(RenderWindow *win)
{
	win->draw(*this);
	for (int i = 0; i < hand.size(); i++)
	{
		if (i != hOCI)
		{
			win->draw(hand.at(i));
		}
	}
	if (hOCI != -1)
	{
		win->draw(hand.at(hOCI));
	}
}

void Hand::shiftSize()
{
	if (this->getScale() == (Vector2f)smSize)
	{
		this->setScale((Vector2f)lgSize);
		for (int i = 0; i < hand.size(); i++)
		{
			hand.at(i).setScale((Vector2f)lgSize);
		}
	}
	else
	{
		this->setScale((Vector2f)smSize);
		for (int i = 0; i < hand.size(); i++)
		{
			hand.at(i).setScale((Vector2f)smSize);
		}
		this->setCards();
	}
}

void Hand::setCards()
{
	double a, b;

	//change equation based on size
	if (this->getScale() == (Vector2f)lgSize)
	{
		a = lgEquation.x;
		b = lgEquation.x;
	}
	else
	{
		a = smEquation.x;
		b = smEquation.y;
	}

	vector<double> angle = getAngles(a, b, getSlope(a, b, pointsList(a, b, hand.size())));
	vector<Vector2f> points = pointsList(a, b, hand.size());
	vector<double> temp = getSlope(a, b, pointsList(a, b, hand.size()));
	for (int i = 0; i < hand.size(); i++)
	{
		hand.at(i).setOrigin(hand.at(i).getTexture()->getSize().x / 2, hand.at(i).getTexture()->getSize().x);
		hand.at(i).setPosition(points.at(i).x + this->getPosition().x, -(points.at(i).y) + this->getPosition().y);
		hand.at(i).setRotation(angle.at(i));
	}
	hOCI = hand.size() - 1;
}

int Hand::pOnCards(Vector2f m)
{
	mouse.setPosition(m);
	int index = -1;
	for (int i = 0; i < hand.size(); i++)
	{
		if(hand.at(i).getGlobalBounds().contains(m))
		{
			if (Collision::PixelPerfectTest(mouse, hand.at(i)))
			{
				index = i;
				hOCI = i;
			}
		}
	}
	if (index == -1)
	{
		hOCI = hand.size() - 1;
	}
	return index;
}

string Hand::specOSC(int index)
{
	return hand.at(index).getSpec();
}

double Hand::semi_ellipse(double x, double a, double b)
{
	return sqrt((1 - (pow(x, 2) / pow(a, 2)))*pow(b, 2));
}

vector<Vector2f> Hand::pointsList(double a, double b, int numOC)
{
	vector<Vector2f> temp;
	numOC++;
	for (int i = 1; i < numOC; i++)
	{
		temp.push_back(Vector2f(0, 0));
		temp.at(i - 1).x = (-a) + ((((2 * a) / numOC))*i);
		temp.at(i - 1).y = semi_ellipse(temp.at(i - 1).x, a, b);

	}

	return temp;
}

vector<double> Hand::getAngles(double a, double b, vector<double> slopes)
{
	vector<double> temp;
	double slope;
	for (int i = 0; i < slopes.size(); i++)
	{
		slope = slopes.at(i);
		temp.push_back(-((atan(slope)*(180 / M_PI))));
	}
	return temp;
}

vector<double> Hand::getSlope(double a, double b, vector<Vector2f> pointLs)
{
	vector<double> temp;
	int x;
	for (int i = 0; i < pointLs.size(); i++)
	{
		x = pointLs.at(i).x;
		temp.push_back(-((pow(b, 2)*x) / (pow(a, 2)*sqrt(pow(b, 2)*(1 - (pow(x, 2) / pow(a, 2)))))));
	}
	return temp;
}