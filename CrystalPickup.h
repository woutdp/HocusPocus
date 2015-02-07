#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Pickup.h"

//-----------------------------------------------------
// CrystalPickup Class									
//-----------------------------------------------------
class CrystalPickup : public Pickup
{
public:
	CrystalPickup(int posX, int posY);				// Constructor
	CrystalPickup(DOUBLE2 pos);
	virtual ~CrystalPickup();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy(DOUBLE2 posHero);

private: 
	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Construct();

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap * m_BmpCrystalPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	CrystalPickup(const CrystalPickup& yRef);									
	CrystalPickup& operator=(const CrystalPickup& yRef);	
};

 
