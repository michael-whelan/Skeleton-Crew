#include "CrowsNest.h"


CrowsNest::CrowsNest(float x,float y, float r, Texture* mtexture, Station* station):Job(x,y,r,station)
{
	texture = mtexture;
}


CrowsNest::CrowsNest(float x,float y, float r, Texture* mtexture, Station* station,Entity* control):Job(x,y,r,station,control)
{
	texture = mtexture;
}


CrowsNest::~CrowsNest(void)
{
}

void CrowsNest::setUpgrade(float f)
{
}

void CrowsNest::movement(float timeElapsed)
{
}

void CrowsNest::AIControl(float timeElapsed,vector<Entity*> *nightmares)
{
}
void CrowsNest::crewControl(float timeElapsed,vector<Entity*> *nightmares)
{
}

void CrowsNest::action(float timeElapsed)
{
}


void CrowsNest::update(float timeElapsed)
{
}


void CrowsNest::draw(SDL_Renderer* renderer,Vector2f offset,float scale)
{
	posRec->x = (myStation->getPos().x)*scale + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->y = (myStation->getPos().y)*scale + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->w = radius*scale;//length;
	posRec->h = radius*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->circle->getTexture(),nullptr,posRec,myStation->getRotation(),nullptr,SDL_FLIP_NONE);

}
void CrowsNest::drawTop(SDL_Renderer* renderer,Vector2f offset,float scale)
{
	posRec->x = (myStation->getPos().x)*scale + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(51/2))*scale;
	posRec->y = (myStation->getPos().y)*scale + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(324/2))*scale;
	posRec->w = 51*scale;//length;
	posRec->h = 324*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,myStation->getRotation(),nullptr,SDL_FLIP_NONE);
	if(controller != nullptr)
	{
		controller->draw(renderer,scale,offset);
	}
}