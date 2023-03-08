#include "pch.h"
#include "Brick.h"

/*
	Brick type 1 : blue 1 hit
	Brick type 2 : red 2 hit
	Brick type 3 : Green 1 hit buffMoreBall
*/

void Brick::initShape(int type)
{
	this->shape.setSize(sf::Vector2f(50.f, 20.f));
	if (type == 1)
		this->shape.setFillColor(sf::Color::Blue);
	else if (type == 2)
		this->shape.setFillColor(sf::Color::Red);
	else
	{
		this->shape.setFillColor(sf::Color::Green);
	}
	
}

void Brick::initVar(int type)
{
	this->type = type; buffBall = nullptr;
	if (type == 1) this->health = 1;
	else if (type == 2) this->health = 2;
	else if (type == 3)
	{
		this->health = 1;
		sf::Vector2f pos = this->shape.getPosition();
		sf::Vector2f sz = this->shape.getSize(); sz.x /= 2; sz.y /= 2;
		pos.x += sz.x; pos.y += sz.y;
		buffBall = new BuffBall(pos,1);
	}
}

void Brick::initPos(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

Brick::Brick(sf::Vector2f pos,int health)
{
	this->initShape(health);
	this->initPos(pos);
	this->initVar(health);
}

Brick::~Brick()
{
}

sf::RectangleShape Brick::getShape()
{
	return this->shape;
}

int Brick::getHealth()
{
	return this->health;
}

BuffBall* Brick::getBuff()
{
	return this->buffBall;
}

void Brick::decreaseHealth()
{
	this->health--;
}

void Brick::update()
{
	//this->health--;
	if (this->health == 1 && this->type == 2)
		this->shape.setFillColor(sf::Color::Blue);
	
}

void Brick::render(sf::RenderTarget* window)
{
	window->draw(this->shape);
}
