#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Explosion Class									
//-----------------------------------------------------
class Explosion
{
public:
	Explosion(DOUBLE2 pos);				// Constructor
	virtual ~Explosion();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime)=0;
	virtual void Paint(MATRIX3X2 matview)=0;
	virtual void Start(DOUBLE2 pos)=0;
	virtual bool GetRunning()=0;

protected:
	DOUBLE2 m_Pos;
	int m_CurrentAnimationStep;

	static const int NR_ANIMATIONS =16;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Explosion(const Explosion& yRef);									
	Explosion& operator=(const Explosion& yRef);	
};

 
