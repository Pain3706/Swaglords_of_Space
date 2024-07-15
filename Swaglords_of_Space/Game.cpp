#include "Game.h"


void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 1000), "Swaglords of Space", sf::Style::Resize | sf::Style::Titlebar);
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

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initSound();
	this->initWorld();
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
		this->update();
		this->render();
	}
}

void Game::updatePollEventS()
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

void Game::update()
{
	this->updatePollEventS();
	this->updateInput();
	this->player->update();
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

void Game::render()
{
	this->window->clear();

	//Draw world 
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}
	this->window->display();
}
