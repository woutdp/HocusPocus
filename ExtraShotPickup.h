#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Pickup.h"

//-----------------------------------------------------
// ExtraShotPickup Class									
//-----------------------------------------------------
class ExtraShotPickup : public Pickup
{
public:
	ExtraShotPickup(int posX, int posY);
	ExtraShotPickup(DOUBLE2 pos);// Constructor
	virtual ~ExtraShotPickup();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy(DOUBLE2 posHero);



private: 

	void Construct();
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	bool m_Shine;
	static Bitmap * m_BmpExtraShotPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ExtraShotPickup(const ExtraShotPickup& yRef);									
	ExtraShotPickup& operator=(const ExtraShotPickup& yRef);	
};

 
