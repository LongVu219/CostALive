#pragma once



class BuffBall
{
private:
	//variable
	sf::RectangleShape shape;
	int type;

	//private funtion
	void initShape(int type);
	void initPos(sf::Vector2f pos);
	void initVar(int type);

public:
	//constructor / destructor
	BuffBall(sf::Vector2f pos,int type);
	virtual ~BuffBall();

	//accessor
	sf::RectangleShape getShape();
	int getType();

	//function
	
	void update();
	void render(sf::RenderTarget* window);

};

