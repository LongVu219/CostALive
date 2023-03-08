#include "BuffBall.h"

#pragma once
class Brick
{
private:
	//private variable
	sf::RectangleShape shape;
	int type;
	int health;
	BuffBall* buffBall;

	//private function
	void initShape(int type);
	void initVar(int type);
	void initPos(sf::Vector2f pos);

public:
	//constructor / destructor
	Brick(sf::Vector2f pos,int type);
	virtual ~Brick();
	
	//accessor
	
	sf::RectangleShape getShape();
	int getHealth();
	BuffBall* getBuff();

	//function
	void decreaseHealth();
	void update();
	void render(sf::RenderTarget *window);

};

