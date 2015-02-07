#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Lock Class									
//-----------------------------------------------------
class Lock
{
public:
	Lock(DOUBLE2 pos,int type);
	Lock(int posX, int posY,int type);	
	virtual ~Lock();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy();

	int GetType();
	bool GetAlive();

	void SetAlive(bool value);
	HitRegion * GetHitregion();
	DOUBLE2 GetPos();

private: 
	void Construct();

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int SILVER = 0;
	static const int GOLD = 1;
	
	DOUBLE2 m_Pos;
	bool m_Alive,m_Shine;
	static Bitmap * m_BmpLockPtr;
	HitRegion * m_HitLockPtr;
	int m_Type;
	

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Lock(const Lock& yRef);									
	Lock& operator=(const Lock& yRef);	
};

 
