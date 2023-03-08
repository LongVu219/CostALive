#include "pch.h"
#include "Game.h"
using namespace std;

void Game::initVar()
{
	this->window = nullptr;
	
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "gaming", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(90);
}

//constructor
Game::Game()
{
	this->initVar();
	this->initWindow();
}

//destructor
Game:: ~Game()
{
	delete this->window;
}

//acessor
const bool Game::running() const
{
	return this->window->isOpen();
}

//function
void Game::pollevent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

Ball* RandABall(Ball *sourceBall) {

	Ball *cur1 = new Ball(sourceBall->getShape().getPosition(), 0);
	float y = rand() % 5 + 1; y *= -1;
	float x = sqrt(30 - y * y);
	//cout << rand() % 2;
	if ((rand() % 2) == 0) x *= -1;

	//cout << "Ball " << x << "\n";
	cur1->modifySpeed(x, y);
	return cur1;
}

void Game::spawmBall()
{
	//cout << this->ligma.size() << endl;
	if (this->ligma.size() >= 1) return;
	if (this->ligma.empty())
	{
		Ball* ptr = new Ball(this->paddle.getShape().getPosition(), 1);
		this->ligma.push_back(ptr);
	}
	else 
	{
		//cout << "?";
		
		
	}

}

void Game::updateBall()
{
	this->spawmBall();
	for (int i = 0;i < this->ligma.size();i++)
	{
		this->ligma[i]->update(this->paddle.getShape().getPosition(), sf::Keyboard::isKeyPressed(sf::Keyboard::Space), this->paddle);
		if (!this->ligma[i]->inGame()) this->ligma.erase(this->ligma.begin() + i);
	}
}

void Game::renderBall()
{
	for (int i = 0; i < this->ligma.size(); i++)
		this->ligma[i]->render(this->window);
}

void Game::spawnBrick()
{
	//cout << this->brick.size() << endl;
	if (this->brick.size() >= 1) return;
	int redBrick = 10;
	int GreenBrick = 10;
	for (int i = 0; i < 10; i++)
	{
		int type = 1;
		int rd = rand() % 3;
		if (redBrick && rd == 1) type = 2, redBrick--;
		else if (GreenBrick && rd == 2) type = 3, GreenBrick--;
		Brick *tmp = new Brick(sf::Vector2f(100.f + 55*i, 100.f), type);
		this->brick.push_back(tmp);

		type = 1;
		rd = rand() % 2;
		if (redBrick && rd == 1) type = 2, redBrick--;
		else if (GreenBrick && rd == 2) type = 3, GreenBrick--;
		Brick *tmp2 = new Brick(sf::Vector2f(100.f + 55 * i, 130.f), type);
		this->brick.push_back(tmp2);

		type = 3;
		Brick *tmp3 = new Brick(sf::Vector2f(100.f + 55 * i, 250.f), type);
		this->brick.push_back(tmp3);
	}
	
}

void Game::updateBrick()
{
	for (int i = 0;i < this->brick.size();i++)
	{
		this->brick[i]->update();
		if (this->brick[i]->getHealth() <= 0)
		{
			if (this->brick[i]->getBuff() != nullptr)
				buff.push_back(this->brick[i]->getBuff());
			this->brick.erase(this->brick.begin() + i);
		}
	}
}

void Game::renderBrick()
{
	this->spawnBrick();
	for (int i = 0; i < this->brick.size(); i++)
	{
		if (this->brick[i]->getHealth() > 0) this->brick[i]->render(this->window);
	}
}

void Game::updateBuff()
{
	for (int i = 0; i < this->buff.size(); i++)
	{
		this->buff[i]->update();
		int type = this->buff[i]->getType();
		sf::Vector2f pos = this->buff[i]->getShape().getPosition();

		if (this->paddle.getShape().getGlobalBounds().contains(pos))
		{
			if (type == 1) // Add 1 extra ball base on already existed shooted ball (ligma[0])
			{
				if (!ligma.empty())
				{
					if (this->ligma[0]->isShooted()) {
						//Ball* ptr = &RandABall(cur);
						this->ligma.push_back(RandABall(this->ligma[0]));
						//this->ligma.push_back(RandABall(cur));
					}
				}
			}
			this->buff.erase(this->buff.begin() + i);
		}

		if (pos.y >= 600) this->buff.erase(this->buff.begin() + i);
	}
		
}

void Game::renderBuff()
{
	for (int i = 0; i < this->buff.size(); i++)
		this->buff[i]->render(this->window);
}

bool LineIntersect(float lf1, float rg1, float lf2, float rg2)
{
	return ((lf1 <= lf2 && lf2 <= rg1) || (lf2 <= lf1 && lf1 <= rg2));
}

void Game::CheckBallBrickCollision()
{
	for (int i = 0;i < this->ligma.size();i++) 
	{
		bool collided = 0;
		for (int j = 0;j < this->brick.size();j++)
		{
			if (collided) break;
			if (!this->brick[j]->getHealth()) continue;
			sf::Vector2f posBall = this->ligma[i]->getShape().getPosition();
			sf::Vector2f UpperBrick = this->brick[j]->getShape().getPosition();
			sf::Vector2f LowerBrick = 
				sf::Vector2f (UpperBrick.x + this->brick[j]->getShape().getSize().x, UpperBrick.y + this->brick[j]->getShape().getSize().y);
			float upperBall = posBall.y - this->ligma[i]->getShape().getRadius();
			float lowerBall = posBall.y + this->ligma[i]->getShape().getRadius();
			float leftBall = posBall.x - this->ligma[i]->getShape().getRadius();
			float rightBall = posBall.x + this->ligma[i]->getShape().getRadius();



			bool changed = 0;

			if (LineIntersect(UpperBrick.x,LowerBrick.x,leftBall,rightBall))
			{
				//cout << "1 " << upperBall << " " << LowerBrick.y << " x " << lowerBall << " " << UpperBrick.y << "\n";
				if (abs(upperBall - LowerBrick.y) <= 8.0 || abs(lowerBall - UpperBrick.y) <= 8.0) 
				{
					//exit(0);
					changed = 1;
					this->ligma[i]->changeSpeed(1, -1), this->brick[j]->decreaseHealth(); collided = 1;
				}
					
			}

			if (LineIntersect(UpperBrick.y,LowerBrick.y,upperBall,lowerBall))
			{
				//cout << "2 " << rightBall << " " << UpperBrick.x << " x " << leftBall << " " << LowerBrick.x << "\n";
				if (abs(rightBall - UpperBrick.x) <= 8.0 || abs(leftBall - LowerBrick.x) <= 8.0)
				{
					//cout << "?\n";
					this->ligma[i]->changeSpeed(-1, 1), this->brick[j]->decreaseHealth(); collided = 1;
				}
					
			}

		}
	}
}


void Game::update()
{
	
	this->pollevent();
	this->CheckBallBrickCollision();
	this->paddle.update(this->window);
	this->updateBall();
	this->updateBrick();
	this->updateBuff();
}


void Game::render()
{
	this->window->clear();

	//Draw game object
	this->paddle.render(this->window);
	this->renderBall();
	this->renderBrick();
	this->renderBuff();

	this->window->display();
}

