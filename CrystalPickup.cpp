//---------------------------
// Includes
//---------------------------
#include "CrystalPickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * CrystalPickup::m_BmpCrystalPtr = 0;

CrystalPickup::CrystalPickup(int posX, int posY):
					Pickup(posX,posY)
{
	Construct();
}

CrystalPickup::CrystalPickup(DOUBLE2 pos):
					Pickup(pos)
{
	Construct();
}

CrystalPickup::~CrystalPickup()
{
	delete m_BmpCrystalPtr;
	m_BmpCrystalPtr = 0;
}


void CrystalPickup::Construct()
{
	m_Type = CRYSTALTYPE;
	
	if (m_BmpCrystalPtr == 0)
	{
		m_BmpCrystalPtr = new Bitmap("./Resources/Crystal.png");
		m_BmpCrystalPtr->SetTransparencyColor(255,0,255);
		
	}
	m_HitPickupPtr = new HitRegion();
	m_HitPickupPtr->CreateFromRect(m_Pos.x,m_Pos.y,30,22);
}

void CrystalPickup::Tick(double deltaTime)
{
	++m_CurrentAnimationLoop;
}

void CrystalPickup::Paint(MATRIX3X2 matView)
{
	if(m_Alive)
	{	
		MATRIX3X2 matTranslate;
		RECT rect;

		int height = 22;
		int width = 30;

		rect.top = 0;
		rect.bottom = height;
		rect.left = m_CurrentAnimationLoop%12/2 * width;
		rect.right = rect.left + width;

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpCrystalPtr,0,0,rect);
	}
}

void CrystalPickup::Destroy(DOUBLE2 posHero)
{
	m_Alive = false;
}