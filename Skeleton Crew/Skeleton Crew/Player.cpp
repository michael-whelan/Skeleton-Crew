#include "Player.h"


Player::Player(void):Notoriety(0.0f), gold(5000)
{
}


Player::~Player(void)
{
}

void Player::update(float timeElapsed)
{
	Notoriety -= 1.0f * timeElapsed;
	if(Notoriety < 0)
		Notoriety = 0;
	if(Notoriety > 100)
		Notoriety = 100;
}
