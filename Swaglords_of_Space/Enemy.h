#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<iostream>
#include<vector>
#include<ctime>

class Enemy
{
private:
	sf::Sprite shape;
public:
	Enemy();
	virtual ~Enemy();

	//Accessor
	const sf::FloatRect getBounds() const;
};

