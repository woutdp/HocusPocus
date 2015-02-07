//---------------------------
// Includes
//---------------------------
#include "Switch.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Switch::m_BmpSwitchPtr = 0;
Switch::Switch(int posX, int posY):m_Pos(posX,posY),m_On(false)
{
	if (m_BmpSwitchPtr == 0)
	{
		m_BmpSwitchPtr = new Bitmap("./Resources/Switch.png");
		m_BmpSwitchPtr->SetTransparencyColor(255,0,255);
	}

	m_HitSwitchPtr = new HitRegion();
	m_HitSwitchPtr->CreateFromRect(0,0,32,32);
	m_HitSwitchPtr->SetPos(m_Pos);
}

Switch::~Switch()
{
	delete m_BmpSwitchPtr;
	m_BmpSwitchPtr = 0;

	delete m_HitSwitchPtr;
	m_HitSwitchPtr = 0;
}

void Switch::Tick(HitRegion * hero,double deltaTime)
{
	if (GAME_ENGINE->IsKeyDown(VK_UP) == false)
	{
		m_DoubleClick = false;
	}
	
	if (m_HitSwitchPtr->HitTest(hero) && GAME_ENGINE->IsKeyDown(VK_UP) && m_DoubleClick == false)
	{
		m_On = !m_On;
		m_DoubleClick = true;
	}
}

void Switch::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT r;

	r.top =0;
	r.bottom = r.top + 32;
	r.left = m_On * 32;
	r.right = r.left + 32;

	matTranslate.SetAsTranslate(m_Pos);
	GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
	GAME_ENGINE->DrawBitmap(m_BmpSwitchPtr,0,0,r);
}

bool Switch::GetOn()
{
	return m_On;
}

void Switch::Reset()
{
	m_On = false;
}