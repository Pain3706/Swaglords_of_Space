#pragma once

#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

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

	//Enemy
	float enemiesSpawnTimerMax;
	float enemiesSpawnTimer;
	float speed;
	int maxEnemies;
	int hp;

	std::vector<sf::Sprite> enemies;
	sf::Texture text1, text2, text3;

	//Private Functions
	void initVariables();
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

	void spawnEnemy();
	void updatePollEventS();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void update();
	void updateSound();
	void renderWorld();
	void renderEnemies();
	void render();
};

