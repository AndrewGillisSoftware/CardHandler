#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Card.h"

#define M_PI 3.14159265358979323846

using namespace sf;
using namespace std;

class Hand : public RectangleShape
{
public:
	Hand();
	~Hand();
	Hand(Vector2f position, Vector2f smEquation, Vector2f lgEquation, Vector2f smSize, Vector2f lgSize, int rot);

	void addCard(Card);

	Card removeCard(int index);

	void display(RenderWindow*);

	void shiftSize();

	void setCards();

	//returns index of card mouse is on. If the mouse is not on a card it returns -1
	int pOnCards(Vector2f);

	string specOSC(int index);

private:
	Sprite mouse;

	vector<Card> hand;
	Vector2f smSize;
	Vector2f lgSize;
	Vector2f smEquation;
	Vector2f lgEquation;

	int hOCI;

	//given a list of cards and other ellipse info arange cards on ellipse
	//given an equation and x value return y
	double semi_ellipse(double x, double a, double b);
	//given an equation with num of cards return a list of pointers on the ellipse that are from -a to a split into chuncks based on card size
	vector<Vector2f> pointsList(double a, double b, int numOC);
	//uses the derivitive of equation to get slope at which it gets the angle of the tangent line at that point
	vector<double> getAngles(double a, double b, vector<double> slopes);

	vector<double> getSlope(double a, double b, vector<Vector2f> pointLs);
};

