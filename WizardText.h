#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

#include "Hero.h"

//-----------------------------------------------------
// WizardText Class									
//-----------------------------------------------------
class WizardText
{
public:
	WizardText();				// Constructor
	virtual ~WizardText();		// Destructor

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick(double deltaTime, Hero * hero);
	void Paint(MATRIX3X2 matView);

	void Create(String input, int posX,int posY);

	bool GetActive();
	bool GetActivePressed();
	void SetActive(bool value);


private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	static const int HEIGHT = 20;
	static const int WIDTH = 20;

	DOUBLE2 m_Pos;
	String m_Input;

	bool m_Active,m_ActivePressed;

	HitRegion * m_HitWizardTextPtr;
	static Bitmap * m_BmpWizardTextPtr; 

	// -------------------------
	// Disabling default copWizardText constructor and default 
	// assignment operator.
	// -------------------------
	WizardText(const WizardText& WizardTextRef);									
	WizardText& operator=(const WizardText& WizardTextRef);	
};

 
