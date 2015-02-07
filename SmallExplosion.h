#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Explosion.h"

//-----------------------------------------------------
// SmallExplosion Class									
//-----------------------------------------------------
class SmallExplosion  : public Explosion
{
public:
	SmallExplosion(DOUBLE2 pos);				// Constructor
	virtual ~SmallExplosion();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matview);
	bool GetRunning();

protected:

	void Start(DOUBLE2 pos);




private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int WIDTH = 400, HEIGHT = 200;
	static Bitmap* m_BmpExplosionPtr;
	bool m_Running;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	SmallExplosion(const SmallExplosion& yRef);									
	SmallExplosion& operator=(const SmallExplosion& yRef);	
};

 
