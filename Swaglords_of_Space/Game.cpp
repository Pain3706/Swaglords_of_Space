#include "Game.h"


void Game::initVariables()
{
	this->enemiesSpawnTimerMax = 10.f;
	this->enemiesSpawnTimer = this->enemiesSpawnTimerMax;
	this->maxEnemies = 3;
	this->speed = 100.f;
	this->hp = 5;
	this->points = 0;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1500, 1000), "Swaglords of Space", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures\\bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initSound()
{
	if (!this->buffer.loadFromFile("Sound\\laser.wav")) {
		std::cout << "Error: Could not open sound file" << std::endl;
	}

	if (!this->music.openFromFile("Sound\\lofi.ogg")) {
		std::cout << "Error: Could not open sound file" << std::endl;
	}

	music.setLoop(true);
	music.play();
}

void Game::initWorld()
{
	if(!this->worldBackgroundText.loadFromFile("Textures\\background.jpg")) {
		std::cout << "Error: Could not load background texture";
	}
	this->worldBackground.setTexture(this->worldBackgroundText);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Font\\font.ttf")) {
		std::cout << "Error loading font\n";
	}

	// Create Game Over text
	this->gameOverText.setFont(font);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setPosition(500.f, 400.f);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initSound();
	this->initWorld();
	this->initFont();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Remove textures
	for(auto &i : this->textures)
		delete i.second;

	//Delete Bullets
	for (auto* i : this->bullets)
		delete i;
}

//Functions
void Game::run()
{
	while (this->window->isOpen()) {
		this->updatePollEvents();
		if(this->hp > 0)
		{
			this->update();
			this->render();
		}
		else {
			this->window->draw(this->gameOverText);
		}
	}
}

void Game::spawnEnemy()
{
	int type = rand() % 3;
	if (!text1.loadFromFile("Textures\\ship6.png")) {
		std::cout << "Error" << "\n";
	}
	if (!text2.loadFromFile("Textures\\ship5.png")) {
		std::cout << "Error" << "\n";
	}
	if (!text3.loadFromFile("Textures\\ship4.png")) {
		std::cout << "Error" << "\n";
	}

	sf::Sprite sprite;
	if (type == 0) {
		sprite.setTexture(text1);
		sprite.setScale(0.3f, 0.3f);
	}
	if (type == 1) {
		sprite.setTexture(text2);
		sprite.setScale(0.2f, 0.2f);
	}
	if (type == 2) {
		sprite.setTexture(text3);
		sprite.setScale(0.5f, 0.5f);
	}

	float randomX = static_cast<float>(rand() % 1300);
	sprite.setPosition(randomX, -100.f);
	this->enemies.push_back(sprite);
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
		this->updateSound();
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for(auto* bullet : this->bullets) {
		bullet->update();

		//Bullet culling(top of screen) 
		if(bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}


}

void Game::updateEnemies()
{
	//Spawn enemies
	if (this->enemies.size() < maxEnemies) {
		if (this->enemiesSpawnTimer >= this->enemiesSpawnTimerMax) {
			this->spawnEnemy();
			this->enemiesSpawnTimer = 0.f;
		}
		else this->enemiesSpawnTimer += 1.f;
	}

	//Move downward
	for (int i = 0; i < enemies.size(); i++) {
		this->enemies[i].move(0.f, 4.f);
		bool enemyRemoved = false;
		for (int k = 0; k < this->bullets.size(); k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i].getGlobalBounds())) {
				this->enemies.erase(this->enemies.begin() + i);
				this->bullets.erase(this->bullets.begin() + k);
				enemyRemoved = true;
				this->points++;
				std::cout << "Points: " << points << ' ' << "\n";
				break;
			}
		}

		if (!enemyRemoved && this->player->getBounds().intersects(this->enemies[i].getGlobalBounds())) {
			this->enemies.erase(this->enemies.begin() + i);
			this->hp--;
			std::cout << "HP: " << this->hp << "\n";
			enemyRemoved = true;
		}

		if (!enemyRemoved && this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->hp--;
			std::cout << "HP: " << this->hp << "\n";
		}
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateEnemies();
	this->updateBullets();
}

void Game::updateSound()
{
	this->sound.setBuffer(buffer);
	this->sound.play();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderEnemies()
{
	for (auto& e : enemies) {
		this->window->draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	//Draw world 
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);
	this->renderEnemies();
	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}
	if (this->hp <= 0)
		this->window->draw(this->gameOverText);
	this->window->display();
}
