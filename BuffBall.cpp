#include "pch.h"
#include "BuffBall.h"

/*
	type 1 : more ball
	type 2 : ligma ball
	type 3 : arabic ball
	type 4 : homelander
	type 5 : big mama ball
	extrem traumatic when it's more ligma arabic big mama ball
*/

void BuffBall::initShape(int type)
{
	if (type == 1)
	{
		this->shape.setSize(sf::Vector2f(30.f, 30.f));
		if (this->type == 1)
			this->shape.setFillColor(sf::Color::White);
	}
	sf::Vector2f sz = this->shape.getSize();
	this->shape.setOrigin(sz.x/2,sz.y/2);
}

void BuffBall::initPos(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

void BuffBall::initVar(int type)
{
	this->type = type;
}

BuffBall::BuffBall(sf::Vector2f pos,int type)
{
	this->initShape(type);
	this->initPos(pos);
	this->initVar(type);
}

BuffBall::~BuffBall()
{
}

sf::RectangleShape BuffBall::getShape()
{
	return this->shape;
}

int BuffBall::getType()
{
	return this->type;
}

void BuffBall::update()
{
	this->shape.move(0, 1);
}

void BuffBall::render(sf::RenderTarget* window)
{
	window->draw(this->shape);
}
