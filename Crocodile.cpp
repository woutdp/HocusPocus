//---------------------------
// Includes
//---------------------------
#include "Crocodile.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------

Bitmap* Crocodile::m_BmpEnemyPtr = 0;

Crocodile::Crocodile(HitRegion * HitLevel, bool direction):
			Enemy(HitLevel,direction),m_Agressive(false),m_Backward(false),m_PosBolt(0,0),m_FireDirection(false), m_Firing(false)
				,m_CurrentAnimationBolt(0)
{
	m_HitEnemyPtr = new HitRegion();
	m_HitEnemyPtr->CreateFromRect(0,0,15,48);

	if (m_BmpEnemyPtr == 0)
	{
		m_BmpEnemyPtr = new Bitmap("./Resources/Crocodile.png");
		m_BmpEnemyPtr->SetTransparencyColor(255,0,255);
	}

	m_HitBoltPtr = new HitRegion();
	m_HitBoltPtr->CreateFromRect(0,0,28,10);

	DOUBLE2 pos;
	pos.x = 0;
	pos.y = 0;

	m_ExplosionPtr = new SmallExplosion(pos);

	m_Height = 55;
	m_Width = 65;

	m_Health = 4;

	m_Type = 1;
}

Crocodile::~Crocodile()
{
	delete m_HitEnemyPtr;
	m_HitEnemyPtr = 0;

	delete m_BmpEnemyPtr;
	m_BmpEnemyPtr = 0;

	delete m_HitBoltPtr;
	m_HitBoltPtr = 0;
}


void Crocodile::Tick(double deltaTime, DOUBLE2 posHero)
{

	/*//Set the maximum velocities
	if (m_HeroVelocity.y > 400 && (m_State == STATEJUMPING || m_State == STATEWALKING)) m_HeroVelocity.y = 400;
	if (m_State == STATEFALLING) m_HeroVelocity.y = 620;
	
	//Do the physics
	m_Pos = m_Pos + m_HeroVelocity*dTime;
	m_HeroVelocity = m_HeroVelocity + m_Gravity*dTime;
	//Make sure the position is not a double.
	m_Pos.x = (int)m_Pos.x;
	m_Pos.y = (int)m_Pos.y;*/

	//adjust the hitregions to the position of the bitmap
	

	if (m_Agressive == false)
	{
		if (m_Backward == false)
		{
			++m_CurrentAnimationStep;
		}
		else
		{
			--m_CurrentAnimationStep;
		}

		if(m_Backward == true && m_CurrentAnimationStep <= 0)
		{
			m_Backward = false;
		}

		if(m_Backward == false && m_CurrentAnimationStep >= 5)
		{
			m_Backward = true;
		}
	}
	else
	{
		++m_CurrentAnimationStep;
	}

	
	--m_GettingHit;

	if (m_SpawnTime > 0)
	{
		--m_SpawnTime;
	}
	

	AgressiveAI(posHero);

	if (m_CurrentAnimationStep > 8)
	{
		m_CurrentAnimationStep = 0;
		m_Agressive = false;
	}

	if (m_GettingHit <= 0)
	{
		m_GettingHit = 0;
	}

	if (m_SpawnTime == 0)
	{
		m_SpawnTime = 0;
		m_Alive = true;
	}
	else
	{
		m_Alive = false;
	}

	CollisionDetection();

	if (m_Health <= 0)
	{
		m_Alive = false;
	}

	if (m_Alive)
	{
		if (m_Direction)
		{
			if (m_Agressive && m_CurrentAnimationStep >= 8)
			{
				FireBolt();
			}
			else if (m_Agressive == false)
			{
				m_Pos.x -=4;
			}
		}
		else
		{
			if (m_Agressive && m_CurrentAnimationStep >= 8)
			{
				FireBolt();
			}
			else if (m_Agressive == false)
			{
				m_Pos.x +=4;
			}
		}
	}

	m_HitEnemyPtr->SetPos(m_Pos.x+20,m_Pos.y);	
	TickBolt(deltaTime);
	m_ExplosionPtr->Tick(deltaTime);
}


void Crocodile::Paint(MATRIX3X2 matview)
{
	PaintBolt(matview);
	
	MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale;
	matView = matview;
	RECT rect;

	if (m_Alive)
	{
		//SET BOUNDS RECT
		rect.top = 0 +(m_Height*2*(m_GettingHit%2));
		rect.bottom = rect.top+m_Height;
		rect.left = (m_Width*(((int)(m_CurrentAnimationStep/2))));
		rect.right = rect.left+m_Width;

		if (m_Agressive == true)
		{
			rect.top = m_Height +(m_Height*2*(m_GettingHit%2));
			rect.bottom = rect.top+m_Height;
			rect.left = (m_Width*(m_CurrentAnimationStep%8/4));
			rect.right = rect.left+m_Width;
		}
		
		matCenter.SetAsTranslate(-m_Width/2,0);

		if (m_Direction == true)
		{
			matScale.SetAsScale(-1,1);
		}

		matTranslate.SetAsTranslate(m_Pos);
		GAME_ENGINE->SetTransformMatrix(matCenter*matScale*matCenter.Inverse()*matTranslate*matView);
		GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr,0,0,rect);

		/*GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->FillHitRegion(m_HitEnemyPtr);*/
	}

	m_ExplosionPtr->Paint(matView);
	
}

void Crocodile::Spawn(int posX,int posY)
{
	m_Health = 4;
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Alive = false;
	//m_Direction = false;
	m_SpawnTime = 20;
}

void Crocodile::Hit(int amountOfDamage)
{
	m_GettingHit = 10;
	--m_Health;
}

void Crocodile::Destroy(bool brutally)
{
	m_Alive = false;
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_SpawnTime = -1;
}

void Crocodile::CollisionDetection()
{
	RECT2 rect = m_HitEnemyPtr->GetBounds();
	
	if (m_Alive)
	{	
		if (m_Direction == false)
		{
			if (m_HitLevelPtr->HitTest(rect.right+1,rect.top)|| m_HitLevelPtr->HitTest(rect.right+2,rect.bottom) == false || m_HitLevelPtr->HitTest(rect.right+1,rect.top+30))
			{
				m_Direction = !m_Direction;
			}
		}
		else
		{
			if (m_HitLevelPtr->HitTest(rect.left-1,rect.top)|| m_HitLevelPtr->HitTest(rect.left-2,rect.bottom) == false || m_HitLevelPtr->HitTest(rect.left-1,rect.top+30))
			{
				m_Direction = !m_Direction;
			}
		}
	}

	//CHECK COLLSION BOLT WITH LEVEL
	if (m_HitBoltPtr->HitTest(m_HitLevelPtr))
	{
		DestroyBolt();
		m_ExplosionPtr->Start(m_PosBolt);
	}
}

void Crocodile::AgressiveAI(DOUBLE2 posHero)
{
	if ((posHero.y+22-100 <= m_Pos.y && posHero.y+22+100 >= m_Pos.y) && rand()%50 == 0 && -400 < posHero.x - m_Pos.x && 400 > posHero.x - m_Pos.x && m_Agressive == false && m_Firing == false && m_Alive == true)
	{
		m_CurrentAnimationStep = 0;

		m_Agressive = true;

		if (posHero.x <= m_Pos.x)
		{
			m_Direction = true;
		}
		else
		{
			m_Direction = false;
		}
	}
	/*else
	{
		if (rand()%70 == 0)
		{
			m_Agressive = false;
		}
	}*/
}

void Crocodile::TickBolt(double deltaTime)
{
	if (m_Firing == true)
	{
		++m_CurrentAnimationBolt;

		if (m_FireDirection  == true)
		{	
			DOUBLE2 pos = m_PosBolt;
			pos.x -= 44;
			m_HitBoltPtr->SetPos(pos);
			m_PosBolt.x -= 16;
		}
		else
		{
			DOUBLE2 pos = m_PosBolt;
			pos.x += 16;
			m_HitBoltPtr->SetPos(pos);
			m_PosBolt.x += 16;
		}
	
	}
}

void Crocodile::PaintBolt(MATRIX3X2 matView)
{
	if (m_Firing == true)
	{
		
		MATRIX3X2 matTranslate,matScale;
		RECT r;
		DOUBLE2 tempPos = m_PosBolt;

		if ((m_CurrentAnimationBolt/2) %2 == 0) tempPos.y +=2;

		matScale.SetAsScale(1,1);
		if (m_FireDirection == true)
		{
			matScale.SetAsScale(-1,1);
		}

		r.top = m_Height;
		r.bottom = r.top + m_Height;
		r.left = m_Width*2;
		r.right = r.left + m_Width;

		matTranslate.SetAsTranslate(tempPos);
		GAME_ENGINE->SetTransformMatrix(matScale * matTranslate * matView);
		GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr,0,0,r);

		/*GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->FillHitRegion(m_HitBoltPtr);*/
	}
}

void Crocodile::FireBolt()
{
	m_FireDirection = m_Direction;
	m_PosBolt.y = m_Pos.y+4;
	m_PosBolt.x = m_Pos.x+40;
	m_Firing = true;
	m_CurrentAnimationBolt = 0;
}

HitRegion * Crocodile::GetBoltHitRegion()
{
	return m_HitBoltPtr;
}

void Crocodile::DestroyBolt()
{
	m_HitBoltPtr->SetPos(0,0);
	m_Firing = false;
}