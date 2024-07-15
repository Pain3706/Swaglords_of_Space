#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x + 47.f, pos_y - 30.f);
	this->shape.scale(0.05f, 0.05f);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movemnetSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//Movement
	this->shape.move(this->movemnetSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
