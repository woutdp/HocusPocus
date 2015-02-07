#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// ScoreText Class									
//-----------------------------------------------------
class ScoreText
{
public:
	ScoreText();				// Constructor
	virtual ~ScoreText();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime);
	void Paint(String input, int posX,int posY,MATRIX3X2 matView, int widthBox);



private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int HEIGHT = 16;
	static const int WIDTH = 20;

	DOUBLE2 m_Pos;

	static Bitmap * m_BmpScoreTextPtr; 

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ScoreText(const ScoreText& yRef);									
	ScoreText& operator=(const ScoreText& yRef);	
};

 
