#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Explosion.h"

//-----------------------------------------------------
// BigExplosion Class									
//-----------------------------------------------------
class BigExplosion  : public Explosion
{
public:
	BigExplosion(DOUBLE2 pos);				// Constructor
	virtual ~BigExplosion();		// Destructor

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
	static const int WIDTH = 500, HEIGHT = 214;
	static Bitmap* m_BmpExplosionPtr;
	bool m_Running;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BigExplosion(const BigExplosion& yRef);									
	BigExplosion& operator=(const BigExplosion& yRef);	
};

 
