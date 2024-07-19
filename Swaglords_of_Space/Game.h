#pragma once

#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;
	
	//Font
	sf::Font font;
	sf::Text gameOverText;
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
	int points;

	std::vector<sf::Sprite> enemies;
	sf::Texture text1, text2, text3;

	//Private Functions
	void initVariables();
	void initWindow();
	void initTextures();
	void initPlayer();
	void initSound();
	void initWorld();
	void initFont();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void spawnEnemy();
	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void update();
	void updateSound();
	void renderWorld();
	void renderEnemies();
	void render();
};

