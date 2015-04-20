#pragma once
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
public:
	///
	///constructor method for Player class
	///
	Player(void);

	///
	///destructor method for Player class
	///
	~Player(void);

	void update(float timeElapsed);

	///
	///used to determine AI reaction to player
	///
	float Notoriety;
	int gold;///used to store player's gold
};
#endif

