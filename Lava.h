#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Lava Class									
//-----------------------------------------------------
class Lava
{
public:
	Lava(int posX, int posY, int currentAnimation);				// Constructor
	virtual ~Lava();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);

	HitRegion * GetHitRegion();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_Pos;
	int m_CurrentAnimation;
	HitRegion * m_HitLavaPtr;
	static Bitmap * m_BmpLavaPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Lava(const Lava& yRef);									
	Lava& operator=(const Lava& yRef);	
};

 
