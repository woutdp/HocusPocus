//---------------------------
// Includes
//---------------------------
#include "Sparkles.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * Sparkles::m_BmpSparklesPtr = 0;
Sparkles::Sparkles():m_Pos(0,0),m_Alive(false),m_CurrentAnimation(0),m_Random(0)
{
	if(m_BmpSparklesPtr == 0)
	{
		m_BmpSparklesPtr = new Bitmap("./Resources/Sparkles.png");
		m_BmpSparklesPtr->SetTransparencyColor(255,0,255);
	}
}

Sparkles::~Sparkles()
{
	delete m_BmpSparklesPtr;
	m_BmpSparklesPtr = 0;
}

void Sparkles::Tick(double deltaTime)
{
	if (m_Alive)
	{
		m_Random = rand()%4;

		++m_CurrentAnimation;

		if (m_CurrentAnimation >= 16)
		{
			Destroy();
		}
	}
}

void Sparkles::Paint(MATRIX3X2 matView)
{
	if (m_Alive && m_Random == 0)
	{
		MATRIX3X2 matTranslate,matIdentity;
		RECT2 r;

		r.top = 0;
		r.bottom = r.top + 40;
		r.left = 40*m_CurrentAnimation;
		r.right = r.left + 40;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
		GAME_ENGINE->DrawBitmap(m_BmpSparklesPtr,0,0,r);
	}
}

void Sparkles::Spawn(DOUBLE2 pos)
{
	m_Pos = pos;
	m_CurrentAnimation = 0;
	m_Alive = true;
}

void Sparkles::Destroy()
{
	m_Alive = false;
}

bool Sparkles::GetAlive()
{
	return m_Alive;
}