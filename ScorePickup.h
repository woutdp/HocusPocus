#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"
#include "Pickup.h"

//-----------------------------------------------------
// ScorePickup Class									
//-----------------------------------------------------
class ScorePickup : public Pickup
{
public:
	ScorePickup(int posX, int posY,int scoreType);
	ScorePickup(DOUBLE2 pos,int scoreType);// Constructor
	virtual ~ScorePickup();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Destroy(DOUBLE2 posHero);

	//void Construct();

private: 
	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Construct();
	
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	bool m_Shine;
	int m_ScoreType;
	static Bitmap * m_BmpScorePtr;
	bool m_Backward;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ScorePickup(const ScorePickup& yRef);									
	ScorePickup& operator=(const ScorePickup& yRef);	
};

 
