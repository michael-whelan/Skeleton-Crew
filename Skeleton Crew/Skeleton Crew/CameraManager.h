#pragma once
#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include <stdio.h>
#include "KeyManager.h"
using namespace std;
///
///handles current view point
///
class CameraManager
{
private:
	static CameraManager* me;///static pointer to camera manager
	float scale;///the current zoom
	Vector2f offSet;///the offest for drawing
	Vector2f destination;
public:
	CameraManager(void);///creates the camera manager
	~CameraManager(void);///deconstructs the camera manager
	void update(float timeElapsed,Vector2f playerPos, float sightIncrease);///updates the zooming and view point
	Vector2f getOffSet();///returns the current offset
	float getScale();///returns the current zoom
	Vector2f getOffsetNScale(){return offSet;};
	static CameraManager* getManager();///returns the camera manager, if it doesn't exist it creates it
	void setTransition(Vector2f playerPos);
	enum cameraStates///states that the camera can be in
	{
		none,
		transition
	};
	cameraStates currentState;///current state of the camera
};
#endif
