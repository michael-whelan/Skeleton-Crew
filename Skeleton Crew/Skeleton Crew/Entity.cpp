#include "Entity.h"

int Entity::entityCount=0;

SDL_Rect* Entity::posRec;

Entity::Entity(float x,float y):position(x,y),rotation(0),size(0,0),velocity(0,0),texture(0),alive(true),health(100)
{
	if(!posRec)
	{
		posRec = new SDL_Rect();
	}
	attached = new vector<pair<Entity*,pair<Vector2f,Vector2f>>>(0);
	myEntity = entityType::entity;
}

Entity::~Entity(void)
{
	vector<pair<Entity*,pair<Vector2f,Vector2f>>>::iterator attachedIter = attached->begin();
	for(;attachedIter!=attached->end();)
	{
		vector<pair<Entity*,pair<Vector2f,Vector2f>>>::iterator attachedOtherIter = (*attachedIter).first->getAttached()->begin();
		for(;attachedOtherIter != (*attachedIter).first->getAttached()->end();)
		{
			if((*attachedOtherIter).first==this)
			{
				attachedOtherIter = (*attachedIter).first->getAttached()->erase(attachedOtherIter);
			}
			else
			{
				++attachedOtherIter;
			}
		}
		attachedIter=attached->erase(attachedIter);
	}
	delete attached;
}

void Entity::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	if(texture)
	{
		posRec->x = (position.x-(size.x/2))*scale;
		posRec->y = (position.y-(size.y/2))*scale;
		posRec->w = size.x*scale;
		posRec->h = size.y*scale;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		float angle =  rotation*M_PI/180;
		SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
	}
}

void Entity::drawTop(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	if(textureTop)
	{
		posRec->x = (position.x-(size.x/2))*scale;
		posRec->y = (position.y-(size.y/2))*scale;
		posRec->w = size.x*scale;
		posRec->h = size.y*scale;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		float angle =  rotation*M_PI/180;
		SDL_RenderCopyEx(renderer,textureTop->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
	}
}

void Entity::drawBottom(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	if(textureBottom)
	{
		posRec->x = (position.x-(size.x/2))*scale;
		posRec->y = (position.y-(size.y/2))*scale;
		posRec->w = size.x*scale;
		posRec->h = size.y*scale;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		float angle =  rotation*M_PI/180;
		SDL_RenderCopyEx(renderer,textureBottom->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
	}
}

void Entity::movement(float timeElapsed)
{
}

void Entity::update(float timeElapsed)
{
}

void Entity::AIControl(float timeElapsed, vector<Entity*> *nightmares)
{

}

void Entity::destroyAllAttachments()
{
	vector<pair<Entity*,pair<Vector2f,Vector2f>>>::iterator attachedIter = attached->begin();
	for(;attachedIter!=attached->end();)
	{
		vector<pair<Entity*,pair<Vector2f,Vector2f>>>::iterator attachedOtherIter = (*attachedIter).first->getAttached()->begin();
		for(;attachedOtherIter != (*attachedIter).first->getAttached()->end();)
		{
			if((*attachedOtherIter).first==this)
			{
				attachedOtherIter = (*attachedIter).first->getAttached()->erase(attachedOtherIter);
			}
			else
			{
				++attachedOtherIter;
			}
		}
		attachedIter=attached->erase(attachedIter);
	}
}