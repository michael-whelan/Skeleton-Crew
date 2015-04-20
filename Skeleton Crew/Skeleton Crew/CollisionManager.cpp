#include "CollisionManager.h"

CollisionManager* CollisionManager::me;

CollisionManager* CollisionManager::getManager()
{
	if(!me)
	{
		me=new CollisionManager();
	}
	return me;
}

CollisionManager::CollisionManager(void)
{
}


CollisionManager::~CollisionManager(void)
{
}

void CollisionManager::update(float timeElapsed)
{
	checkAllCollisions();
}

void CollisionManager::checkAllCollisions()
{
	for(int i = 0; i <ObjectManager::getManager()->crew->size();i++)
	{
		Unit* crew = ObjectManager::getManager()->crew->at(i);
		if(crew->getGrapple())
		{
			Projectile* ball = crew->getGrapple();

			for(int k = 0; k < ObjectManager::getManager()->stations->size(); k++)
			{
				Station* ship2 = ObjectManager::getManager()->stations->at(k);
				if(ship2!=crew->getStation())
				{
					if(collisionStationProjectile(ship2,ball))
					{
						if(crew->getStation())
						{
							vector<Entity*>::iterator entityIter = ((Station*)crew->getStation())->getAssignedCrew()->begin();
							for(; entityIter != ((Station*)crew->getStation())->getAssignedCrew()->end();)
							{
								if(*entityIter==crew)
								{
									entityIter = ((Station*)crew->getStation())->getAssignedCrew()->erase(entityIter);
								}
								else
								{
									++entityIter;
								}
							}
						}
						ObjectManager::getManager()->crew->at(i)->setStation(ship2);
						ObjectManager::getManager()->crew->at(i)->grapplePoint(ball->getPos());
						ship2->getAssignedCrew()->push_back(ObjectManager::getManager()->crew->at(i));
						break;
					}
				}
			}
		}
	}
	for(int i = 0; i <ObjectManager::getManager()->units->size();i++)
	{
		Unit* crew = ObjectManager::getManager()->units->at(i);
		if(crew->getGrapple())
		{
			Projectile* ball = crew->getGrapple();

			for(int k = 0; k < ObjectManager::getManager()->stations->size(); k++)
			{
				Station* ship2 = ObjectManager::getManager()->stations->at(k);
				if(ship2!=crew->getStation())
				{
					if(collisionStationProjectile(ship2,ball))
					{
						if(crew->getStation())
						{
							vector<Entity*>::iterator entityIter = ((Station*)crew->getStation())->getAssignedUnits()->begin();
							for(; entityIter != ((Station*)crew->getStation())->getAssignedUnits()->end();)
							{
								if(*entityIter==crew)
								{
									entityIter = ((Station*)crew->getStation())->getAssignedUnits()->erase(entityIter);
								}
								else
								{
									++entityIter;
								}
							}
						}
						ObjectManager::getManager()->units->at(i)->setStation(ship2);
						ObjectManager::getManager()->units->at(i)->grapplePoint(ball->getPos());
						ship2->getAssignedUnits()->push_back(ObjectManager::getManager()->units->at(i));
						break;
					}
				}
			}
		}
	}
	for(int i =0; i < ObjectManager::getManager()->stations->size(); i++)
	{
		Station* ship1 = ObjectManager::getManager()->stations->at(i);
		for(int j = 0; j < ObjectManager::getManager()->stations->at(i)->getCannonBalls()->size(); j++)
		{
			if(ObjectManager::getManager()->stations->at(i)->getCannonBalls()->at(j))
			{
				Projectile* ball = ObjectManager::getManager()->stations->at(i)->getCannonBalls()->at(j);

				for(int k = 0; k < ObjectManager::getManager()->stations->size(); k++)
				{
					if(i!=k)
					{
						Station* ship2 = ObjectManager::getManager()->stations->at(k);
						if(collisionStationProjectile(ship2,ball))
						{
							ball->applyAction(ship1,ship2);
							delete ObjectManager::getManager()->stations->at(i)->getCannonBalls()->at(j);
							ObjectManager::getManager()->stations->at(i)->getCannonBalls()->erase(ObjectManager::getManager()->stations->at(i)->getCannonBalls()->begin()+j);
							break;
						}
					}
				}
			}
		}
		for(int j = i; j < ObjectManager::getManager()->stations->size(); j++)
		{
			if(j!=i)
			{
				Station* ship2 = ObjectManager::getManager()->stations->at(j);
				if(ship1->getVelocity().length()!=0||ship2->getVelocity().length()!=0)
				{
					if(collisionStationStaion(ship1,ship2))
					{
						collisionResponse(ship1,ship2);
						if(ObjectManager::getManager()->selected)
						{
							if(ObjectManager::getManager()->selected->getStation() )
							{	
								if(ObjectManager::getManager()->selected->getStation()==ship1||ObjectManager::getManager()->selected->getStation()==ship2)
								{
									if(ship1->getEntity()&Entity::bank||ship2->getEntity()&Entity::bank)
									{
										GUIManager::getManager()->getBank()->setMenu(true);
									}
									else if(ship1->getEntity()&Entity::shipyard||ship2->getEntity()&Entity::shipyard)
									{
										GUIManager::getManager()->getShop()->setAlive(true);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



bool CollisionManager::checkDistance(Vector2f c1, float r1, Vector2f c2, float r2)
{
	return ( ( ( (c1.x - c2.x) * (c1.x - c2.x) ) + ( (c1.y - c2.y) * (c1.y - c2.y) ) ) < (r1 + r2)*(r1 + r2));
}


void CollisionManager::collisionResponse(Station* ship1, Station* ship2)
{
	Vector2f pos1;
	pos1.x = ship1->getPos().x;
	pos1.y = ship1->getPos().y;
	Vector2f pos2;
	pos2.x = ship2->getPos().x;
	pos2.y = ship2->getPos().y;
	Vector2f vel1 = ship1->getVelocity();
	Vector2f vel2 = ship2->getVelocity();
	bool v1N = false;
	bool v2N = false;
	if(vel1.length()==0)
	{
		vel1.x=pos2.x-pos1.x;
		vel1.y=pos2.y-pos1.y;
		v1N = true;
	}
	if(vel2.length()==0)
	{
		vel2.x=pos1.x-pos2.x;
		vel2.y=pos1.y-pos2.y;
		v2N = true;
	}
	float m1 = ship1->getMass();
	float m2 = ship2->getMass();
	Vector2f mirror = (vel1/vel1.length())+(vel2/vel2.length());
	if(mirror.length()==0)
	{
		mirror = Vector2f(-vel1.y,vel1.x);
	}
	float ang = acos(((vel1.x*vel2.x)+(vel1.y*vel2.y))/(vel1.length()*vel2.length()));
	ang = ang * 180/M_PI;
	ang/=2;
	float angF1 = ang;
	float angF2 = ang;
	angF1 = angF1*((vel1.length()*m1)/((vel1.length()*m1)+(vel2.length()*m2)));
	angF1 = angF2*((vel2.length()*m2)/((vel1.length()*m1)+(vel2.length()*m2)));
	Vector2f mirrorF;
	mirrorF.x = (mirror.x*cos(angF1)) - (mirror.y*sin(angF1));
	mirrorF.y = (mirror.x*sin(angF1)) + (mirror.y*cos(angF1));
	mirrorF.x = (mirror.x*cos(-angF2)) - (mirror.y*sin(-angF2));
	mirrorF.y = (mirror.x*sin(-angF2)) + (mirror.y*cos(-angF2));

	Vector2f perp = Vector2f(-mirror.y,mirror.x);
	perp = perp/perp.length();
	Vector2f vel1F = vel1 - (perp*( (2*((perp.x*vel1.x)+(perp.y*vel1.y)))/(perp.length()*perp.length()) ));
	vel1F = vel1F/vel1F.length();
	vel1F = vel1F*vel1.length();
	Vector2f vel2F = vel2 - (perp*( (2*((perp.x*vel2.x)+(perp.y*vel2.y)))/(perp.length()*perp.length()) ));
	vel2F = vel2F/vel2F.length();
	vel2F = vel2F*vel2.length();
	Vector2f dir1;
	Vector2f dir2;
	dir2.x=pos2.x-pos1.x;
	dir2.y=pos2.y-pos1.y;
	dir1.x=pos1.x-pos2.x;
	dir1.y=pos1.y-pos2.y;

	dir1=dir1/dir1.length();
	dir2=dir2/dir2.length();
	dir1*=5;
	dir2*=5;
	dir1 = dir1*(m2/(m1+m2));
	dir2 = dir2*(m1/(m1+m2));
	vel1F = vel1F*((vel2.length()*m2*2)/((m1*vel1.length())+(m2*vel2.length())))*0.8f;
	vel2F = vel2F*((vel1.length()*m1*2)/((m1*vel1.length())+(m2*vel2.length())))*0.8f;
	vel2F.x=pos2.x-pos1.x;
	vel2F.y=pos2.y-pos1.y;
	vel1F.x=pos1.x-pos2.x;
	vel1F.y=pos1.y-pos2.y;
	vel1F/=vel1F.length();
	vel2F/=vel2F.length();
	vel1F*=vel1.length();
	vel2F*=vel2.length();
	if(v1N)
	{
		vel1*=-1;
	}
	if(v2N)
	{
		vel2*=-1;
	}
	ship1->changePosition(dir1);
	ship2->changePosition(dir2);
	ship1->setVelocity(vel1+(vel1F*1.5f));
	ship2->setVelocity(vel2+(vel2F*1.5f));
}



float CollisionManager::CheckForCollisionSAT(vector<Vector2f> corners1, vector<Vector2f> corners2)
{
	Vector2f axis;
	float tmp;
	float minA;
	float maxA;
	float minB;
	float maxB;
	int side;
	int i;
	float overlap=LONG_MAX;
	int length = corners1.size();
	if (length%2 == 0)
	{
		length / 2;
	}
	for(side = 0; side < length; side++)
	{
		if(side == 0)
		{
			axis.x = corners1[corners1.size()-1].y - corners1[0].y;
			axis.y = corners1[0].x - corners1[corners1.size()-1].x;
		}
		else
		{
			axis.x = corners1[side - 1].y - corners1[side].y;
			axis.y = corners1[side].x - corners1[side - 1].x;
		}
		tmp = sqrt((axis.x * axis.x) + (axis.y*axis.y));
		axis.x /= tmp;
		axis.y /= tmp;
		minA = maxA = corners1[0].x*axis.x + corners1[0].y*axis.y;
		for (i = 1; i < corners1.size(); i++)
		{
			tmp = corners1[i].x*axis.x+corners1[i].y*axis.y;
			if(tmp>maxA)
			{
				maxA = tmp;
			}
			else if(tmp<minA)
			{
				minA = tmp;
			}
		}
		/*
		tmp = a.position.x*axis.x+a.position.y*axis.y;
		minA += tmp
		maxA += tmp;
		*/

		minB = maxB = corners2[0].x*axis.x + corners2[0].y*axis.y;
		for (i = 1; i < corners2.size(); i++)
		{
			tmp = corners2[i].x*axis.x+corners2[i].y*axis.y;
			if(tmp>maxB)
			{
				maxB = tmp;
			}
			else if(tmp<minB)
			{
				minB = tmp;
			}
		}
		/*
		tmp = b.position.x*axis.x+b.position.y*axis.y;
		minB += tmp;
		maxB += tmp;
		*/

		if(maxA < minB || minA > maxB)
		{
			corners1.empty();
			corners2.empty();
			return 0;
		}
		overlap = min(overlap,min(maxA-minB,maxB-minA));
	}


	length = corners2.size();
	if (length%2 == 0)
	{
		length / 2;
	}
	for(side = 0; side < length; side++)
	{
		if(side == 0)
		{
			axis.x = corners2[corners2.size()-1].y - corners2[0].y;
			axis.y = corners2[0].x - corners2[corners2.size()-1].x;
		}
		else
		{
			axis.x = corners2[side - 1].y - corners2[side].y;
			axis.y = corners2[side].x - corners2[side - 1].x;
		}
		tmp = sqrt((axis.x * axis.x) + (axis.y*axis.y));
		axis.x /= tmp;
		axis.y /= tmp;
		minB = maxB = corners2[0].x*axis.x + corners2[0].y*axis.y;
		for (i = 1; i < corners2.size(); i++)
		{
			tmp = corners2[i].x*axis.x+corners2[i].y*axis.y;
			if(tmp>maxB)
			{
				maxB = tmp;
			}
			else if(tmp<minB)
			{
				minB = tmp;
			}
		}
		/*
		tmp = b.position.x*axis.x+b.position.y*axis.y;
		minB += tmp;
		maxB += tmp;
		*/

		minA = maxA = corners1[0].x*axis.x + corners1[0].y*axis.y;
		for (i = 1; i < corners1.size(); i++)
		{
			tmp = corners1[i].x*axis.x+corners1[i].y*axis.y;
			if(tmp>maxA)
			{
				maxA = tmp;
			}
			else if(tmp<minA)
			{
				minA = tmp;
			}
		}
		/*
		tmp = a.position.x*axis.x+a.position.y*axis.y;
		minA += tmp;
		maxA += tmp;
		*/

		if(maxA < minB || minA > maxB)
		{
			corners1.empty();
			corners2.empty();
			return 0;
		}
		overlap = min(overlap,min(maxA-minB,maxB-minA));
	}

	corners1.empty();
	corners2.empty();
	return overlap;
}


bool CollisionManager::perPixel(Texture* tex1, Texture* tex2, Vector2f pos1, Vector2f pos2, Vector2f size1, Vector2f size2, float rot1, float rot2)
{
	Vector2f tex1Size = tex1->getSize();
	Vector2f tex2Size = tex2->getSize();
	SDL_Surface* surface1 = tex1->getSurface();
	SDL_Surface* surface2 = tex2->getSurface();
	Vector2f ratio1 = Vector2f((1/size1.x)*tex1Size.x,(1/size1.y)*tex1Size.y);
	Vector2f ratio2 = Vector2f((1/size2.x)*tex2Size.x,(1/size2.y)*tex2Size.y);
	Vector2f point1;
	Vector2f point2;
	Uint32 *pixels1 = (Uint32 *)surface1->pixels;
	Uint32 *pixels2 = (Uint32 *)surface2->pixels;
	Uint32 pixel1;
	Uint32 pixel2;
	int pixelPoint;
	float rot1Cos=cos(rot1*M_PI/180);
	float rot1Sin=sin(rot1*M_PI/180);
	float nrot2Cos=cos((-rot2)*M_PI/180);
	float nrot2Sin=sin((-rot2)*M_PI/180);
	for(int i =0; i < size1.x; i++)
	{
		for(int j = 0; j < size1.y; j++)
		{
			point1.x = i;
			point1.y = j;
			pixelPoint = (((int)(j*ratio1.y)) * surface1->w ) + ((int)(i*ratio1.x));
			if(pixelPoint>=0&&pixelPoint<tex1Size.x*tex1Size.y)
			{
				//pixel1 = tex1->get_pixel32(((int)(i*ratio1.x)),((int)(j*ratio1.y)));
				pixel1 = pixels1[(((int)(j*ratio1.y)) * surface1->w ) + ((int)(i*ratio1.x)) ];
				if(pixel1!=Texture::transparent&&pixel1!=0)
				{
					point1 = pos1;
					point1.x += ((rot1Cos*(i-(size1.x/2)))-(rot1Sin*(j-(size1.y/2))));
					point1.y += ((rot1Sin*(i-(size1.x/2)))+(rot1Cos*(j-(size1.y/2))));

					point2.x = ((nrot2Cos*((point1.x - pos2.x)))-(nrot2Sin*((point1.y - pos2.y))));
					point2.y = ((nrot2Sin*((point1.x - pos2.x)))+(nrot2Cos*((point1.y - pos2.y))));
					point2.x += size2.x/2;
					point2.y += size2.y/2;
					if(point2.x*ratio2.x>=0&&point2.x*ratio2.x<tex2Size.x&&point2.y*ratio2.y>=0&&point2.y*ratio2.y<tex2Size.y)
					{
						pixelPoint = (((int)(point2.y*ratio2.y)) * surface2->w ) + ((int)(point2.x*ratio2.x));
						if(pixelPoint>=0&&pixelPoint<tex2Size.x*tex2Size.y)
						{
							//pixel2 = tex2->get_pixel32(((int)(point2.x*ratio2.x)),((int)(point2.y*ratio2.y)));
							pixel2 = pixels2[(((int)(point2.y*ratio2.y)) * surface2->w ) + ((int)(point2.x*ratio2.x)) ];
							if(pixel1!=Texture::transparent&&pixel2!=Texture::transparent&&pixel1!=0&&pixel2!=0)
							{
								if(pixel1!=Texture::transparent&&pixel2!=Texture::transparent&&pixel1!=0&&pixel2!=0)
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}


void CollisionManager::checkCollision()
{
}




bool CollisionManager::collisionStationProjectile(Station* ship, Projectile* ball)
{
	Vector2f pos1;
	pos1.x = ball->getPos().x;
	pos1.y = ball->getPos().y;
	float radius1 =  sqrt(((ball->getSize().x/2)*(ball->getSize().x/2))+((ball->getSize().y/2)*(ball->getSize().y/2)));
	Vector2f pos2;
	pos2.x = ship->getPos().x;
	pos2.y = ship->getPos().y;
	float radius2 =  sqrt(((ship->getSize().x/2)*(ship->getSize().x/2))+((ship->getSize().y/2)*(ship->getSize().y/2)));
	if(checkDistance(pos1,radius1,pos2,radius2))
	{
		Vector2f dist1;
		dist1.x = pos1.x - CameraManager::getManager()->getOffsetNScale().x;
		dist1.y = pos1.y - CameraManager::getManager()->getOffsetNScale().y;
		Vector2f dist2;
		dist2.x = pos2.x - CameraManager::getManager()->getOffsetNScale().x;
		dist2.y = pos2.y - CameraManager::getManager()->getOffsetNScale().y;
		if(dist1.length()>3840&&dist2.length()>3840)
		{
			return true;
		}
		else
		{
			float rot = ball->getRotation();
			Vector2f size = ball->getSize();
			//Vector2f scale = Vector2f((1/size.x)*ball->getTexture()->getSize().x,(1/size.y)*ball->getTexture()->getSize().y);
			Vector2f scale = Vector2f((1/ball->getTexture()->getSize().x)*size.x,(1/ball->getTexture()->getSize().y)*size.y);
			vector<Vector2f> corners1 = vector<Vector2f>();
			float cosRot=cos(rot*M_PI/180);
			float sinRot=sin(rot*M_PI/180);
			if(ball->getTexture()->isSAT())
			{
				vector<Vector2f> temp = ball->getTexture()->getSAT();
				Vector2f corner;
				for(int i = 0; i < temp.size(); i++)
				{
					corner= pos1 + Vector2f(((cosRot*((temp.at(i).x*scale.x)-(size.x/2)))-(sinRot*((temp.at(i).y*scale.y)-(size.y/2)))),
						((sinRot*((temp.at(i).x*scale.x)-(size.x/2)))+(cosRot*((temp.at(i).y*scale.y)-(size.y/2)))));
					corners1.push_back(corner);
				}
			}
			else
			{
				Vector2f corner = pos1 + Vector2f(((cosRot*(-size.x/2))-(sinRot*(-size.y/2))),((sinRot*(-size.x/2))+(cosRot*(-size.y/2))));
				corners1.push_back(corner);
				corner = pos1 + Vector2f(((cosRot*(size.x/2))-(sinRot*(-size.y/2))),((sinRot*(size.x/2))+(cosRot*(-size.y/2))));
				corners1.push_back(corner);
				corner = pos1 + Vector2f(((cosRot*(size.x/2))-(sinRot*(size.y/2))),((sinRot*(size.x/2))+(cosRot*(size.y/2))));
				corners1.push_back(corner);
				corner = pos1 + Vector2f(((cosRot*(-size.x/2))-(sinRot*(size.y/2))),((sinRot*(-size.x/2))+(cosRot*(size.y/2))));
				corners1.push_back(corner);
			}

			rot = ship->getRotation();
			size = ship->getSize();
			//scale = Vector2f((1/size.x)*ship->getTexture()->getSize().x,(1/size.y)*ship->getTexture()->getSize().y);
			scale = Vector2f((1/ship->getTexture()->getSize().x)*size.x,(1/ship->getTexture()->getSize().y)*size.y);
			vector<Vector2f> corners2 = vector<Vector2f>();
			cosRot=cos(rot*M_PI/180);
			sinRot=sin(rot*M_PI/180);
			if(ship->getTexture()->isSAT())
			{
				vector<Vector2f> temp = ship->getTexture()->getSAT();
				Vector2f corner;
				for(int i = 0; i < temp.size(); i++)
				{
					corner= pos2 + Vector2f(((cosRot*((temp.at(i).x*scale.x)-(size.x/2)))-(sinRot*((temp.at(i).y*scale.y)-(size.y/2)))),
						((sinRot*((temp.at(i).x*scale.x)-(size.x/2)))+(cosRot*((temp.at(i).y*scale.y)-(size.y/2)))));
					corners2.push_back(corner);
				}
			}
			else
			{
				Vector2f corner = pos2 + Vector2f(((cosRot*(-size.x/2))-(sinRot*(-size.y/2))),((sinRot*(-size.x/2))+(cosRot*(-size.y/2))));
				corners2.push_back(corner);
				corner = pos2 + Vector2f(((cosRot*(size.x/2))-(sinRot*(-size.y/2))),((sinRot*(size.x/2))+(cosRot*(-size.y/2))));
				corners2.push_back(corner);
				corner = pos2 + Vector2f(((cosRot*(size.x/2))-(sinRot*(size.y/2))),((sinRot*(size.x/2))+(cosRot*(size.y/2))));
				corners2.push_back(corner);
				corner = pos2 + Vector2f(((cosRot*(-size.x/2))-(sinRot*(size.y/2))),((sinRot*(-size.x/2))+(cosRot*(size.y/2))));
				corners2.push_back(corner);
			}
			float overlap = CheckForCollisionSAT(corners1,corners2);
			if(overlap!=0)
			{
				if(perPixel(ball->getTexture(),ship->getTexture(),pos1,pos2,ball->getSize(),ship->getSize(),ball->getRotation(),ship->getRotation()))
				{
					corners1.clear();
					corners2.clear();
					return true;
				}
			}
			corners1.clear();
			corners2.clear();
		}
	}
	return false;
}

bool CollisionManager::collisionStationStaion(Station* ship1, Station* ship2)
{
	if(ship1->getVelocity().length()!=0||ship2->getVelocity().length()!=0)
	{
		Vector2f pos1;
		pos1.x = ship1->getPos().x;
		pos1.y = ship1->getPos().y;
		float radius1 =  sqrt(((ship1->getSize().x/2)*(ship1->getSize().x/2))+((ship1->getSize().y/2)*(ship1->getSize().y/2)));
		Vector2f pos2;
		pos2.x = ship2->getPos().x;
		pos2.y = ship2->getPos().y;
		float radius2 =  sqrt(((ship2->getSize().x/2)*(ship2->getSize().x/2))+((ship2->getSize().y/2)*(ship2->getSize().y/2)));
		if(checkDistance(pos1,radius1,pos2,radius2))
		{
			Vector2f dist1;
			dist1.x = pos1.x - CameraManager::getManager()->getOffsetNScale().x;
			dist1.y = pos1.y - CameraManager::getManager()->getOffsetNScale().y;
			Vector2f dist2;
			dist2.x = pos2.x - CameraManager::getManager()->getOffsetNScale().x;
			dist2.y = pos2.y - CameraManager::getManager()->getOffsetNScale().y;
			if(dist1.length()>3840&&dist2.length()>3840)
			{
				return true;
			}
			else
			{
				float rot = ship1->getRotation();
				Vector2f size = ship1->getSize();
				Vector2f scale = Vector2f((1/ship1->getTexture()->getSize().x)*size.x,(1/ship1->getTexture()->getSize().y)*size.y);
				vector<Vector2f> corners1 = vector<Vector2f>();
				float cosRot=cos(rot*M_PI/180);
				float sinRot=sin(rot*M_PI/180);
				if(ship1->getTexture()->isSAT())
				{
					vector<Vector2f> temp = ship1->getTexture()->getSAT();
					Vector2f corner;
					for(int i = 0; i < temp.size(); i++)
					{
						corner = pos1 + Vector2f(((cosRot*((temp.at(i).x*scale.x)-(size.x/2)))-(sinRot*((temp.at(i).y*scale.y)-(size.y/2)))),
							((sinRot*((temp.at(i).x*scale.x)-(size.x/2)))+(cosRot*((temp.at(i).y*scale.y)-(size.y/2)))));
						corners1.push_back(corner);
					}
				}
				else
				{
					Vector2f corner = pos1 + Vector2f(((cos(rot*M_PI/180)*(-size.x/2))-(sin(rot*M_PI/180)*(-size.y/2))),((sin(rot*M_PI/180)*(-size.x/2))+(cos(rot*M_PI/180)*(-size.y/2))));
					corners1.push_back(corner);
					corner = pos1 + Vector2f(((cos(rot*M_PI/180)*(size.x/2))-(sin(rot*M_PI/180)*(-size.y/2))),((sin(rot*M_PI/180)*(size.x/2))+(cos(rot*M_PI/180)*(-size.y/2))));
					corners1.push_back(corner);
					corner = pos1 + Vector2f(((cos(rot*M_PI/180)*(size.x/2))-(sin(rot*M_PI/180)*(size.y/2))),((sin(rot*M_PI/180)*(size.x/2))+(cos(rot*M_PI/180)*(size.y/2))));
					corners1.push_back(corner);
					corner = pos1 + Vector2f(((cos(rot*M_PI/180)*(-size.x/2))-(sin(rot*M_PI/180)*(size.y/2))),((sin(rot*M_PI/180)*(-size.x/2))+(cos(rot*M_PI/180)*(size.y/2))));
					corners1.push_back(corner);
				}

				rot = ship2->getRotation();
				size = ship2->getSize();
				scale = Vector2f((1/ship2->getTexture()->getSize().x)*size.x,(1/ship2->getTexture()->getSize().y)*size.y);
				//scale = Vector2f((1/size.x)*ship2->getTexture()->getSize().x,(1/size.y)*ship2->getTexture()->getSize().y);
				vector<Vector2f> corners2 = vector<Vector2f>();
				cosRot=cos(rot*M_PI/180);
				sinRot=sin(rot*M_PI/180);
				if(ship2->getTexture()->isSAT())
				{
					vector<Vector2f> temp = ship2->getTexture()->getSAT();
					Vector2f corner;
					for(int i = 0; i < temp.size(); i++)
					{
						corner= pos2 + Vector2f(((cosRot*((temp.at(i).x*scale.x)-(size.x/2)))-(sinRot*((temp.at(i).y*scale.y)-(size.y/2)))),
							((sinRot*((temp.at(i).x*scale.x)-(size.x/2)))+(cosRot*((temp.at(i).y*scale.y)-(size.y/2)))));
						corners2.push_back(corner);
					}
				}
				else
				{
					Vector2f corner = pos2 + Vector2f(((cos(rot*M_PI/180)*(-size.x/2))-(sin(rot*M_PI/180)*(-size.y/2))),((sin(rot*M_PI/180)*(-size.x/2))+(cos(rot*M_PI/180)*(-size.y/2))));
					corners2.push_back(corner);
					corner = pos2 + Vector2f(((cos(rot*M_PI/180)*(size.x/2))-(sin(rot*M_PI/180)*(-size.y/2))),((sin(rot*M_PI/180)*(size.x/2))+(cos(rot*M_PI/180)*(-size.y/2))));
					corners2.push_back(corner);
					corner = pos2 + Vector2f(((cos(rot*M_PI/180)*(size.x/2))-(sin(rot*M_PI/180)*(size.y/2))),((sin(rot*M_PI/180)*(size.x/2))+(cos(rot*M_PI/180)*(size.y/2))));
					corners2.push_back(corner);
					corner = pos2 + Vector2f(((cos(rot*M_PI/180)*(-size.x/2))-(sin(rot*M_PI/180)*(size.y/2))),((sin(rot*M_PI/180)*(-size.x/2))+(cos(rot*M_PI/180)*(size.y/2))));
					corners2.push_back(corner);
				}
				float overlap = CheckForCollisionSAT(corners1,corners2);
				if(overlap!=0)
				{
					bool response = false;
					if(ship1->getTexture()->getSize().length()<ship2->getTexture()->getSize().length())
					{
						response = perPixel(ship1->getTexture(),ship2->getTexture(),pos1,pos2,ship1->getSize(),ship2->getSize(),ship1->getRotation(),ship2->getRotation());
					}
					else
					{
						response = perPixel(ship2->getTexture(),ship1->getTexture(),pos2,pos1,ship2->getSize(),ship1->getSize(),ship2->getRotation(),ship1->getRotation());
					}
					if(response)
					{
						corners1.clear();
						corners2.clear();
						return true;
					}
				}
				corners1.clear();
				corners2.clear();
			}
		}
	}
	return false;
}