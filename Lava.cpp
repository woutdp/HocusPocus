//---------------------------
// Includes
//---------------------------
#include "Lava.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Lava::m_BmpLavaPtr = 0;
Lava::Lava(int posX, int posY, int currentAnimation):m_CurrentAnimation(currentAnimation),m_Pos(posX,posY)
{
	if (m_BmpLavaPtr == 0)
	{
		m_BmpLavaPtr = new Bitmap("./Resources/Lava.png");
		m_BmpLavaPtr->SetTransparencyColor(255,0,255);
	}

	m_HitLavaPtr = new HitRegion();
	m_HitLavaPtr->CreateFromRect(0,1,32,31);
	m_HitLavaPtr->SetPos(m_Pos);
}

Lava::~Lava()
{
	delete m_BmpLavaPtr;
	m_BmpLavaPtr = 0;

	delete m_HitLavaPtr;
	m_HitLavaPtr = 0;
}

void Lava::Tick(double deltaTime)
{
	++m_CurrentAnimation;
}

void Lava::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT r;

	r.top = 0;
	r.bottom = 32;
	r.left = 32*(m_CurrentAnimation%16/2);
	r.right = r.left + 32;

	matTranslate.SetAsTranslate(m_Pos);
	GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
	GAME_ENGINE->DrawBitmap(m_BmpLavaPtr,0,0,r);
}

HitRegion * Lava::GetHitRegion()
{
	return m_HitLavaPtr;
}