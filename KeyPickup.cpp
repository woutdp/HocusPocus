//---------------------------
// Includes
//---------------------------
#include "KeyPickup.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * KeyPickup::m_BmpKeyPickupPtr = 0;
KeyPickup::KeyPickup(int posX, int posY, int keyType):
				Pickup(posX,posY), m_KeyType(keyType),m_Shine(false)
{
	Construct();
}

KeyPickup::KeyPickup(DOUBLE2 pos, int keyType):
				Pickup(pos), m_KeyType(keyType),m_Shine(false)
{
	Construct();
}

KeyPickup::~KeyPickup()
{
	
}

void KeyPickup::Construct()
{
	if (m_KeyType == SILVERKEY) m_Type = KEYSILVER;//SILVERKEY
	if (m_KeyType == GOLDKEY) m_Type = KEYGOLD; //GOLDKEY

	
	if (m_BmpKeyPickupPtr == 0)
	{
		m_BmpKeyPickupPtr = new Bitmap("./Resources/KeyPickup.png");
		m_BmpKeyPickupPtr->SetTransparencyColor(255,0,255);
	}

	m_HitPickupPtr = new HitRegion();
	m_HitPickupPtr->CreateFromRect(m_Pos.x, m_Pos.y,12,22);

}

void KeyPickup::Tick(double deltaTime)
{
	if (m_Alive)
	{
		if (rand()%30 == 0)
		{
			m_Shine = true;
		}
	}
	else if( m_CurrentAnimationLoop < 18)
	{
		++m_CurrentAnimationLoop;
	}
}

void KeyPickup::Paint(MATRIX3X2 matView)
{
	MATRIX3X2 matTranslate;
	RECT rect;

	int height = 22;
	int width = 12;

	rect.top = 0;
	rect.bottom = rect.top + height;

	if (m_Alive)
	{
		if (m_Shine == true)
		{
			rect.left = width*2;
			rect.right = rect.left + width;
		}
		else
		{
			rect.left = width*m_KeyType;
			rect.right = rect.left + width;
		}
	}
	else if (m_CurrentAnimationLoop < 17)
	{
		rect.left = width*3;
		rect.right = rect.left + 46;
	}

	DOUBLE2 pos;
	pos = m_Pos;
	pos.y -= m_CurrentAnimationLoop*4;

	matTranslate.SetAsTranslate(pos);
	GAME_ENGINE->SetTransformMatrix(matTranslate*matView);
	GAME_ENGINE->DrawBitmap(m_BmpKeyPickupPtr,0,0,rect);

	m_Shine = false;
}

void KeyPickup::Destroy(DOUBLE2 posHero)
{
	posHero.y -= 15;
	m_Pos = posHero;
	m_Alive = false;
	m_CurrentAnimationLoop = 0;
	m_Shine = false;
}

