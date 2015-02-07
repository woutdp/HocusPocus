#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Stars.h"

//-----------------------------------------------------
// Block Class									
//-----------------------------------------------------
class Block
{
public:
	Block(int posX, int posY, int type, bool destructableBolt);				// Constructor
	virtual ~Block();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy(int timeUntilDeath);

	bool InitiateDeath();
	bool GetDestructable();
	HitRegion * GetHitregion();
	bool GetAlive();
	DOUBLE2 GetPos();
	void SetAlive(bool value);

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	
	DOUBLE2 m_Pos;
	int m_Type;
	bool m_Alive;
	bool m_InitiateDeath;
	bool m_Destructable;
	HitRegion * m_HitBlockPtr;
	static Bitmap * m_BmpBlockPtr;
	Stars * m_StarPtr;
	int m_TimeUntilDeath;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Block(const Block& yRef);									
	Block& operator=(const Block& yRef);	
};

 
