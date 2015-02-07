#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Pickup Class									
//-----------------------------------------------------
class Pickup
{
public:
	Pickup(int posX, int posY);
	Pickup(DOUBLE2 pos);// Constructor
	virtual ~Pickup();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	virtual void Tick(double deltaTime) = 0;
	virtual void Paint(MATRIX3X2 matView) = 0;
	virtual void Destroy(DOUBLE2 posHero) = 0;


	int GetScore();
	int GetType();
	int GetHealth();
	bool GetAlive();

	void SetAlive(bool value);
	HitRegion * GetHitregion();

protected:

	static const int SCORETYPE = 0;
	static const int HEALTHTYPE = 1;
	static const int CRYSTALTYPE = 2;
	static const int KEYSILVER = 3;
	static const int KEYGOLD = 4;
	static const int EXTRASHOT = 5;

	DOUBLE2 m_StartPos;
	DOUBLE2 m_Pos;
	bool m_Alive;
	int m_Type; // 0 = Score // 1 = Health // 2 = Crystal // 3 = KeySilver // 4 = KeyGold // 5 = ExtraShot
	int m_Score;
	int m_CurrentAnimationLoop;
	HitRegion * m_HitPickupPtr; 
	int m_Health;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Pickup(const Pickup& yRef);									
	Pickup& operator=(const Pickup& yRef);	
};

 
