#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

/*
	Class that act as game engine
*/

using namespace std;

class Game
{
private:

	sf::RenderWindow* window;
	sf::Event ev;
	Paddle paddle;
	vector<Ball*> ligma;
	vector<Brick*> brick;
	vector<BuffBall*> buff;

	void initVar();
	void initWindow();

public:
	// constructoe and destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;

	// function
	void pollevent();

	void spawmBall();
	void updateBall();
	void renderBall();

	void spawnBrick();
	void updateBrick();
	void renderBrick();

	void getBuffFromBrick(); // have done in update brick
	void updateBuff(); // make buff move and take buff effect
	void renderBuff();

	void CheckBallBrickCollision();

	void update();
	void render();
};

