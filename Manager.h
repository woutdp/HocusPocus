#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
//#include "GameEngine.h"

#include "HocusPocus.h"

//-----------------------------------------------------
// Manager Class									
//-----------------------------------------------------
class Manager
{
public:
	Manager();				// Constructor
	virtual ~Manager();		// Destructor

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
	Manager(const Manager& yRef);									
	Manager& operator=(const Manager& yRef);	
};

 
