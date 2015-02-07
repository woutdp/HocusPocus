//---------------------------
// Includes
//---------------------------
#include "Stars.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Stars::m_BmpStarPtr= 0;

Stars::Stars():m_Pos(0,0), m_Shine(false), m_AnimationState(0),m_Colour(0),m_Backward(false)
{
	if (m_BmpStarPtr == 0)
	{
		m_BmpStarPtr = new Bitmap("./Resources/Stars.png");
		m_BmpStarPtr->SetTransparencyColor(255,0,255);
	}
}

Stars::~Stars()
{
	delete m_BmpStarPtr;
	m_BmpStarPtr = 0;
}


void Stars::Tick(double deltaTime)
{
	if (m_Shine == true)
	{
		if (m_Backward == false)++m_AnimationState;
		if (m_Backward == true)--m_AnimationState;
	
		if (m_AnimationState >= 4) m_Backward = true;
		//if (m_AnimationState < 0) m_Backward = true;
	}

	if (m_AnimationState <= -1) m_Shine = false;
}

void Stars::Paint(MATRIX3X2 matview)
{
	if (m_Shine == true)
	{
		MATRIX3X2 matTranslate,matScale;
		RECT r;

		//SET DIMENSIONS
		int heightWidth = 30;

		r.top = heightWidth * m_Colour;
		r.bottom =  r.top + heightWidth;
		r.left = m_AnimationState*heightWidth;
		r.right = r.left + heightWidth;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matview);
		GAME_ENGINE->DrawBitmap(m_BmpStarPtr,0,0,r);
	}
}


void Stars::SpawnBrownStar(DOUBLE2 pos)
{
	m_Pos = pos;

	m_Shine = true;
	m_AnimationState = 0;

	m_Colour = false;
	m_Backward = false;
}

void Stars::SpawnBrownStar(int posX , int posY)
{
	m_Pos.x = posX;
	m_Pos.y = posY;

	m_Shine = true;
	m_AnimationState = 0;

	m_Colour = false;
	m_Backward = false;
}

	
void Stars::SpawnSilverStar(DOUBLE2 pos)
{
	m_Pos = pos;

	m_Shine = true;
	m_AnimationState = 0;

	m_Colour = true;
	m_Backward = false;
}

void Stars::SpawnSilverStar(int posX , int posY)
{
	m_Pos.x = posX;
	m_Pos.y = posY;

	m_Shine = true;
	m_AnimationState = 0;

	m_Colour = true;
	m_Backward = false;
}

bool Stars::GetShine()
{
	return m_Shine;
}