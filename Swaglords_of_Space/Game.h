#pragma once

#include<map>
#include"Player.h"
#include"Bullet.h"

class Game
{
private:
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;	

	//World
	sf::Texture worldBackgroundText;
	sf::Sprite worldBackground;

	//Sound
	sf::Music music;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//Player
	Player* player;

	//Private Functions
	void initWindow();
	void initTextures();
	void initPlayer();
	void initSound();
	void initWorld();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEventS();
	void updateInput();
	void updateBullets();
	void update();
	void updateSound();
	void renderWorld();
	void render();
};

