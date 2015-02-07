#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Hero.h"

#include "Sparkles.h"

//-----------------------------------------------------
// Bolt Class									
//-----------------------------------------------------
class Bolt
{
public:
	Bolt();				// Constructor
	virtual ~Bolt();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime, Hero * hero);
	void Paint(MATRIX3X2 matview);
	void Fire(DOUBLE2 pos,bool direction);
	void Destroy();

	bool CreateSparkles(DOUBLE2 pos);

	//GETS
	DOUBLE2 GetPos();
	bool GetFiring();
	HitRegion * GetHitRegion();

	//SETS
	void SetAllowedToFire(int amount);
	void PlusOneAllowedToFire();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static int m_AllowedToFire,m_AmountInAir;
	static const int MAXSPARKLES = 16;
	static Bitmap * m_BmpBoltPtr;
	HitRegion * m_HitBoltPtr;
	Sparkles * m_SparklesPtr[MAXSPARKLES];
	DOUBLE2 m_Pos;
	bool m_Firing;
	bool m_Direction;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bolt(const Bolt& yRef);									
	Bolt& operator=(const Bolt& yRef);	
};

 
