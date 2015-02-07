#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Effects Class									
//-----------------------------------------------------
class Effects
{
public:
	Effects();				// Constructor
	virtual ~Effects();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------


	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Effects(const Effects& yRef);									
	Effects& operator=(const Effects& yRef);	
};

 
