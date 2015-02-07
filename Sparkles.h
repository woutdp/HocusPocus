#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Sparkles Class									
//-----------------------------------------------------
class Sparkles
{
public:
	Sparkles();				// Constructor
	virtual ~Sparkles();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(MATRIX3X2 matView);
	void Spawn(DOUBLE2 pos);
	void Destroy();

	bool GetAlive();


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static Bitmap * m_BmpSparklesPtr;
	DOUBLE2 m_Pos;
	bool m_Alive;
	int m_CurrentAnimation;
	int m_Random;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Sparkles(const Sparkles& yRef);									
	Sparkles& operator=(const Sparkles& yRef);	
};

 
