#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Pickup.h"

//-----------------------------------------------------
// KeyPickup Class									
//-----------------------------------------------------
class KeyPickup : public Pickup
{
public:
	KeyPickup(int posX, int posY, int keyType);				// Constructor
	KeyPickup(DOUBLE2 pos, int keyType);
	virtual ~KeyPickup();		// Destructor

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
	static const int SILVERKEY = 0;
	static const int GOLDKEY = 1;

	static Bitmap * m_BmpKeyPickupPtr;

	int m_KeyType;
	bool m_Shine;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	KeyPickup(const KeyPickup& yRef);									
	KeyPickup& operator=(const KeyPickup& yRef);	
};

 
