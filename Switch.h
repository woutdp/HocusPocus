#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Switch Class									
//-----------------------------------------------------
class Switch
{
public:
	Switch(int posX, int posY);				// Constructor
	virtual ~Switch();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(HitRegion * hero,double deltaTime);
	void Paint(MATRIX3X2 matView);

	bool GetOn();

	void Reset();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_Pos;
	bool m_On;
	static Bitmap * m_BmpSwitchPtr;
	HitRegion * m_HitSwitchPtr;
	bool m_DoubleClick;


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Switch(const Switch& yRef);									
	Switch& operator=(const Switch& yRef);	
};

 
