#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Stars Class									
//-----------------------------------------------------
class Stars
{
public:
	Stars();				// Constructor
	virtual ~Stars();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matview);

	void SpawnBrownStar(DOUBLE2 pos);
	void SpawnBrownStar(int posX , int posY);
	
	void SpawnSilverStar(DOUBLE2 pos);
	void SpawnSilverStar(int posX , int posY);

	bool GetShine();



private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 m_Pos;
	bool m_Shine;
	bool m_Colour; // 0 = brown 1 = silver
	bool m_Backward;
	int m_AnimationState;


	static Bitmap * m_BmpStarPtr;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Stars(const Stars& yRef);									
	Stars& operator=(const Stars& yRef);	
};

 
