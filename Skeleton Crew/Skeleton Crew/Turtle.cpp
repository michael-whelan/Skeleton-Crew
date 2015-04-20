#include "Turtle.h"

Turtle::Turtle(float X,float Y, float mRotation):MobileStation(X,Y)
{

	position.x = X;
	position.y = Y;
	velocity = Vector2f(10,10);
	rotation = mRotation;
	texture = TextureManager::getManager()->turtle;
	size= Vector2f(628,590);

}


Turtle::~Turtle(void)
{
}
void Turtle::encounterSounds(Vector2f offset){
	int random = rand() % 6000;
	//if the turtle is in range of the player
	if(getPos().x - offset.x > -3840 &&
			getPos().x - offset.x < 5120 && 
			getPos().y - offset.y > -2160 && 
			getPos().y - offset.y < 2880)
		{
			if (random == 1)
			{
				SoundManager::getManager()->startSound(SoundManager::getManager()->turtleSound, position);
			}
	}
}
