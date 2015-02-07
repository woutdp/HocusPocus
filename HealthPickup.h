#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Pickup.h"

//-----------------------------------------------------
// HealthPickup Class									
//-----------------------------------------------------
class HealthPickup : public Pickup 
{
public:
	HealthPickup(int posX, int posY);
	HealthPickup(DOUBLE2 pos);// Constructor
		// Constructor
	virtual ~HealthPickup();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy(DOUBLE2 posHero);

	void Construct();

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap * m_BmpHealthPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	HealthPickup(const HealthPickup& yRef);									
	HealthPickup& operator=(const HealthPickup& yRef);	
};

 
