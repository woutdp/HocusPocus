//---------------------------
// Includes
//---------------------------
#include "Devil.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap* Devil::m_BmpEnemyPtr = 0;

Devil::Devil(HitRegion * HitLevel, bool direction):
			Enemy(HitLevel,direction),m_Agressive(false),m_Backward(false),m_PosBolt(0,0),m_FireDirection(false), m_Firing(false)
{
	m_HitEnemyPtr = new HitRegion();
	m_HitEnemyPtr->CreateFromRect(0,0,40,35);

	if (m_BmpEnemyPtr == 0)
	{
		m_BmpEnemyPtr = new Bitmap("./Resources/Devil.png");
		m_BmpEnemyPtr->SetTransparencyColor(255,0,255);
	}

	m_HitBoltPtr = new HitRegion();
	m_HitBoltPtr->CreateFromRect(0,0,12,36);

	DOUBLE2 pos;
	pos.x = 0;
	pos.y = 0;

	m_ExplosionPtr = new SmallExplosion(pos);

	m_Height = 50;
	m_Width = 80;

	m_Health = 4;

	m_Type = 2;
}

Devil::~Devil()
{
	delete m_HitEnemyPtr;
	m_HitEnemyPtr = 0;

	delete m_BmpEnemyPtr;
	m_BmpEnemyPtr = 0;

	delete m_HitBoltPtr;
	m_HitBoltPtr = 0;
}


void Devil::Tick(double deltaTime, DOUBLE2 posHero)
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

	if (m_CurrentAnimationStep > 2)
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

	RECT2 rectEnemy = m_HitEnemyPtr->GetBounds();

	m_HitLevelPtr->HitTest(rectEnemy.right+2,rectEnemy.top+8);

	if (m_Alive)
	{
		if (m_Direction)
		{
			if (m_Agressive && m_CurrentAnimationStep >= 2)
			{
				FireBolt();
			}
			else if (m_Agressive == false && m_CurrentAnimationStep%2 == 0)
			{
				switch (rand()%4)
				{
					case 0:
						if (m_HitLevelPtr->HitTest(rectEnemy.right+2,rectEnemy.bottom+8) == false)
						{
							m_Pos.x+=2;
							m_Pos.y+=8;
						}
						break;

					case 1:
						if (m_HitLevelPtr->HitTest(rectEnemy.left-8,rectEnemy.bottom+8) == false)
						{
							m_Pos.x-=8;
							m_Pos.y+=8;
						}
						break;

					case 2:
						if (m_HitLevelPtr->HitTest(rectEnemy.right+2,rectEnemy.top-8) == false)
						{
							m_Pos.x+=2;
							m_Pos.y-=8;
						}
						break;

					case 3:
						if (m_HitLevelPtr->HitTest(rectEnemy.left-8,rectEnemy.top-8) == false)
						{
							m_Pos.x-=8;
							m_Pos.y-=8;
						}
						break;
				}
			}
		}
		else
		{
			if (m_Agressive && m_CurrentAnimationStep >= 2)
			{
				FireBolt();
			}
			else if (m_Agressive == false && m_CurrentAnimationStep%2 == 0)
			{
				switch (rand()%4)
				{
					case 0:
						if (m_HitLevelPtr->HitTest(rectEnemy.right+8,rectEnemy.bottom+8) == false)
						{
							m_Pos.x+=8;
							m_Pos.y+=8;
						}
						break;

					case 1:
						if (m_HitLevelPtr->HitTest(rectEnemy.left-2,rectEnemy.bottom+8) == false)
						{
							m_Pos.x-=2;
							m_Pos.y+=8;
						}
						break;

					case 2:
						if (m_HitLevelPtr->HitTest(rectEnemy.right+8,rectEnemy.top-8) == false)
						{
							m_Pos.x+=8;
							m_Pos.y-=8;
						}
						break;

					case 3:
						if (m_HitLevelPtr->HitTest(rectEnemy.left-2,rectEnemy.top-8) == false)
						{
							m_Pos.x-=2;
							m_Pos.y-=8;
						}
						break;
				}
			}
		}
	}

	m_HitEnemyPtr->SetPos(m_Pos.x+20,m_Pos.y);	
	TickBolt(deltaTime);
	m_ExplosionPtr->Tick(deltaTime);
}


void Devil::Paint(MATRIX3X2 matview)
{
	PaintBolt(matview);
	
	MATRIX3X2 matTranslate,matView,matIdentity, matCenter,matScale;
	matView = matview;
	RECT rect;

	if (m_Alive)
	{
		//SET BOUNDS RECT
		rect.top = m_Height*(m_GettingHit%2);
		rect.bottom = rect.top+m_Height;
		rect.left = m_Width*(((int)(m_CurrentAnimationStep/2)));
		rect.right = rect.left+m_Width;

		if (m_Agressive == true)
		{
			rect.top = m_Height*(m_GettingHit%2);
			rect.bottom = rect.top+m_Height;
			rect.left = 3*m_Width;
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

void Devil::Spawn(int posX,int posY)
{
	m_Health = 4;
	m_Pos.x = posX;
	m_Pos.y = posY;
	m_Alive = false;
	//m_Direction = false;
	m_SpawnTime = 20;
}

void Devil::Hit(int amountOfDamage)
{
	m_GettingHit = 10;
	--m_Health;
}

void Devil::Destroy(bool brutally)
{
	m_Alive = false;
	m_Pos.x = 0;
	m_Pos.y = 0;
}

void Devil::CollisionDetection()
{
	/*RECT2 rect = m_HitEnemyPtr->GetBounds();
	
	if (m_Alive)
	{	
		if (m_Direction == false)
		{
			if (((m_HitLevelPtr->HitTest(rect.right+1,rect.top)|| m_HitLevelPtr->HitTest(rect.right+2,rect.bottom) == false)))
			{
				//m_Direction = !m_Direction;
			}
		}
		else
		{
			if (((m_HitLevelPtr->HitTest(rect.left-1,rect.top)|| m_HitLevelPtr->HitTest(rect.left-2,rect.bottom) == false)))
			{
				//m_Direction = !m_Direction;
			}
		}
	}*/

	//CHECK COLLSION BOLT WITH LEVEL
	if (m_HitBoltPtr->HitTest(m_HitLevelPtr))
	{
		DestroyBolt();
		m_ExplosionPtr->Start(m_PosBolt);
	}
}

void Devil::AgressiveAI(DOUBLE2 posHero)
{
	if ((posHero.y+22-100 <= m_Pos.y && posHero.y+22+100 >= m_Pos.y) && rand()%20 == 0 && -400 < posHero.x - m_Pos.x && 400 > posHero.x - m_Pos.x && m_Agressive == false && m_Firing == false && m_Alive == true)
	{
		m_CurrentAnimationStep = 0;

		m_Agressive = true;

	}

	if ((posHero.y+22-200 <= m_Pos.y && posHero.y+22+200 >= m_Pos.y) && rand()%40 == 0 && -500 < posHero.x - m_Pos.x && 500 > posHero.x - m_Pos.x && m_Agressive == false && m_Firing == false && m_Alive == true)
	{

		if (posHero.x <= m_Pos.x)
		{
			m_Direction = true;
		}
		else
		{
			m_Direction = false;
		}
	}
}

void Devil::TickBolt(double deltaTime)
{
	if (m_Firing == true)
	{
		m_PosBolt.y += 16;
		//m_PosBolt.x -= 6;
		DOUBLE2 pos = m_PosBolt;
		//pos.x -= 6;
		m_HitBoltPtr->SetPos(pos);
	}
}

void Devil::PaintBolt(MATRIX3X2 matView)
{
	if (m_Firing == true)
	{
		MATRIX3X2 matTranslate;
		RECT r;

		r.top = 0;
		r.bottom = r.top + m_Height;
		r.left = m_Width*4;
		r.right = r.left + m_Width;

		matTranslate.SetAsTranslate(m_PosBolt);
		GAME_ENGINE->SetTransformMatrix(matTranslate * matView);
		GAME_ENGINE->DrawBitmap(m_BmpEnemyPtr,0,0,r);

		/*GAME_ENGINE->SetColor(255,0,0,100);
		GAME_ENGINE->SetTransformMatrix(matView);
		GAME_ENGINE->FillHitRegion(m_HitBoltPtr);*/
	}
}

void Devil::FireBolt()
{
	//m_FireDirection = m_Direction;
	m_PosBolt.y = m_Pos.y+10;
	m_PosBolt.x = m_Pos.x+40;
	m_Firing = true;
}

HitRegion * Devil::GetBoltHitRegion()
{
	return m_HitBoltPtr;
}

void Devil::DestroyBolt()
{
	m_HitBoltPtr->SetPos(0,0);
	m_Firing = false;
}