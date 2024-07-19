#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	//Private functions
	void initVariables();
	void intiTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();

	//Functions
	void move(const float dirX, const float dirY);

	//Accessor
	const sf::Vector2f& getPos() const;
	const bool canAttack();
	const sf::FloatRect getBounds() const;

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

