#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 4.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::intiTexture()
{
	//Load the texture from file
	if (!this->texture.loadFromFile("Textures\\ship.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << "\n"; 
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.1f, 0.1f);
	this->sprite.setPosition(0.f, 0.f);
}

Player::Player()
{
	this->initVariables();
	this->intiTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const sf::Vector2f& Player::getPos() const
{
	// TODO: insert return statement here
	return this->sprite.getPosition();
}

const bool Player::canAttack()
{
	if(this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

const sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;

}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
