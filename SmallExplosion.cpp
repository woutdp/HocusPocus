//---------------------------
// Includes
//---------------------------
#include "SmallExplosion.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Bitmap* SmallExplosion::m_BmpExplosionPtr = 0;


SmallExplosion::SmallExplosion(DOUBLE2 pos):
		Explosion(pos), m_Running(false)
{
	if (m_BmpExplosionPtr == 0)
	{
		m_BmpExplosionPtr= new Bitmap("./Resources/SmallExplosion.png");
		m_BmpExplosionPtr->SetTransparencyColor(255,0,255);
	}
}

SmallExplosion::~SmallExplosion()
{
	delete m_BmpExplosionPtr;
	m_BmpExplosionPtr = 0;
}

void SmallExplosion::Tick(double deltaTime)
{
	if (m_CurrentAnimationStep > NR_ANIMATIONS)
	{
		m_Running = false;
	}
	else
	{
		++m_CurrentAnimationStep;
	}
}

void SmallExplosion::Paint(MATRIX3X2 matview)
{
	if(m_Running == true)
	{
		//MAKE MATRICES
		MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale;
		matView = matview;

		//MAKE RECT
		RECT rect;
		rect.left = WIDTH*m_CurrentAnimationStep;
		rect.right=rect.left + WIDTH;
		rect.top = 0;
		rect.bottom = HEIGHT;

		matCenter.SetAsTranslate(-(WIDTH/2),-(HEIGHT/2));
		matScale.SetAsScale(1,1);


		//SET TRANSFORMMATRIX
		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matTranslate*matView);

		//DRAW BITMAP

		GAME_ENGINE->DrawBitmap(m_BmpExplosionPtr,0,0,rect);
	}
}
void SmallExplosion::Start(DOUBLE2 pos)
{	
	m_CurrentAnimationStep = 0;
	m_Running = true;
	m_Pos.x = pos.x+70;
	m_Pos.y = pos.y;
}


bool SmallExplosion::GetRunning()
{
	return m_Running;
}