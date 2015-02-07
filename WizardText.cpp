//---------------------------
// Includes
//---------------------------
#include "WizardText.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Bitmap * WizardText::m_BmpWizardTextPtr = 0;

WizardText::WizardText():m_Pos(0,0),m_Input(""),m_Active(false),m_ActivePressed(false)
{
	if (m_BmpWizardTextPtr == 0)
	{
		m_BmpWizardTextPtr = new Bitmap("./Resources/WizardText.png");
		m_BmpWizardTextPtr->SetTransparencyColor(255,0,255);
	}

	m_HitWizardTextPtr = new HitRegion();
	m_HitWizardTextPtr->CreateFromRect(-16,0,88,64);
}

WizardText::~WizardText()
{
	delete m_BmpWizardTextPtr;
	m_BmpWizardTextPtr = 0;

	delete m_HitWizardTextPtr;
	m_HitWizardTextPtr = 0;
}

void WizardText::Tick(double deltaTime, Hero * hero)
{
	if (GAME_ENGINE->IsKeyDown(VK_UP) && m_ActivePressed == false && hero->GetHitRegion()->HitTest(m_HitWizardTextPtr))
	{
		m_Active = !m_Active;
		m_ActivePressed = true;
	}
	else
	{
		m_ActivePressed = false;
	}

	//if (m_Active) GAME_ENGINE->MessageBox("hit");

}

void WizardText::Paint(MATRIX3X2 matView)
{
	if (m_Active)
	{
		//MAKE VARIABLES
		MATRIX3X2 matTranslate,matIdentity; //matrix
		matIdentity.SetAsIdentity();
		RECT2 r; //rect for bitmap
		int amountOfEnters = 0;
		int widthWidestSentence=0;

		DOUBLE2 startSentencePos;
		startSentencePos.x=0;
		startSentencePos.y=0;
		
		//GET THE length OF THE STRING
		int lengthInput = m_Input.GetLength();

		//SET POSITION 
		DOUBLE2 pos(320,134);
		//pos.x += widthBox/2;
		//pos.x -= (lengthInput*16)/2;
		//pos.y += 2;
		
		//CALCULATE AMOUNT OF ENTERS IN THE STRING
		for (int i = 0; i < lengthInput; ++i)
		{
			if(m_Input.CharAt(i) == '\n') ++amountOfEnters;
		}

		pos.y -= amountOfEnters*HEIGHT;

		int currentCharNr = 0;

		for (int i = 0; i < amountOfEnters+1 ; ++i)
		{

			int lengthSentence=5;
			int characterSpace = 14; //space of each letter
			
			for (int j = currentCharNr; j < lengthInput;++j)
			{

				switch (m_Input.CharAt(j))
				{
					case 'i':
						characterSpace = 8;
						break;

					case 'j':
						characterSpace = 12;
						break;

					case 'l':
						characterSpace = 8;
						break;

					case 'm':
						characterSpace = 16;
						break;

					case 'w':
						characterSpace = 16;
						break;

					case 'B':
						characterSpace = 14;
						break;

					case 'I':
						characterSpace = 8;
						break;

					case 'Y':
						characterSpace = 16;
						break;

					case '!':
						characterSpace = 8;
						break;

					case '.':
						characterSpace = 6;
						break;

					case '\'':
						characterSpace = 8;
						break;

					case '\n':
						j = lengthInput;
						break;

					case ' ':
						characterSpace = 8;
						break;

					default: 
						characterSpace = 14;
						break;
				}


				lengthSentence += characterSpace;
			}

			if (lengthSentence >= widthWidestSentence) widthWidestSentence = lengthSentence;
		}	

		pos.x-= widthWidestSentence/2;

		startSentencePos.x = pos.x;

		for (int i = 0; i < lengthInput; ++i)
		{
			int row =0;
			int nextCharacter = 14;

			switch (m_Input.CharAt(i))
			{
				case 'a':
					r.left = WIDTH*0;
					r.right = r.left + WIDTH;
					break;

				case 'b':
					r.left = WIDTH*1;
					r.right = r.left + WIDTH;
					break;

				case 'c':
					r.left = WIDTH*2;
					r.right = r.left + WIDTH;
					break;

				case 'd':
					r.left = WIDTH*3;
					r.right = r.left + WIDTH;
					break;

				case 'e':
					r.left = WIDTH*4;
					r.right = r.left + WIDTH;
					break;

				case 'f':
					r.left = WIDTH*5;
					r.right = r.left + WIDTH;
					break;

				case 'g':
					r.left = WIDTH*6;
					r.right = r.left + WIDTH;
					break;

				case 'h':
					r.left = WIDTH*7;
					r.right = r.left + WIDTH;
					break;

				case 'i':
					r.left = WIDTH*8;
					r.right = r.left + WIDTH;
					nextCharacter = 8;
					break;

				case 'j':
					r.left = WIDTH*9;
					r.right = r.left + WIDTH;
					nextCharacter = 12;
					break;

				case 'k':
					r.left = WIDTH*10;
					r.right = r.left + WIDTH;
					break;

				case 'l':
					r.left = WIDTH*11;
					r.right = r.left + WIDTH;
					nextCharacter = 8;
					break;

				case 'm':
					r.left = WIDTH*12;
					r.right = r.left + WIDTH;
					nextCharacter = 16;
					break;

				case 'n':
					r.left = WIDTH*13;
					r.right = r.left + WIDTH;
					break;

				case 'o':
					r.left = WIDTH*14;
					r.right = r.left + WIDTH;
					break;

				case 'p':
					r.left = WIDTH*15;
					r.right = r.left + WIDTH;
					break;

				case 'q':
					r.left = WIDTH*16;
					r.right = r.left + WIDTH;
					break;

				case 'r':
					r.left = WIDTH*17;
					r.right = r.left + WIDTH;
					break;

				case 's':
					r.left = WIDTH*18;
					r.right = r.left + WIDTH;
					break;

				case 't':
					r.left = WIDTH*19;
					r.right = r.left + WIDTH;
					break;

				case 'u':
					r.left = WIDTH*20;
					r.right = r.left + WIDTH;
					break;

				case 'v':
					r.left = WIDTH*21;
					r.right = r.left + WIDTH;
					break;

				case 'w':
					r.left = WIDTH*22;
					r.right = r.left + WIDTH;
					nextCharacter = 16;
					break;

				case 'x':
					r.left = WIDTH*23;
					r.right = r.left + WIDTH;
					break;

				case 'y':
					r.left = WIDTH*24;
					r.right = r.left + WIDTH;
					break;

				case 'z':
					r.left = WIDTH*25;
					r.right = r.left + WIDTH;
					break;

				case 'A':
					r.left = WIDTH*0;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'B':
					r.left = WIDTH*1;
					r.right = r.left + WIDTH;
					nextCharacter = 14;
					row = 1;
					break;

				case 'C':
					r.left = WIDTH*2;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'D':
					r.left = WIDTH*3;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'E':
					r.left = WIDTH*4;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'F':
					r.left = WIDTH*5;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'G':
					r.left = WIDTH*6;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'H':
					r.left = WIDTH*7;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'I':
					r.left = WIDTH*8;
					r.right = r.left + WIDTH;
					row = 1;
					nextCharacter = 8;
					break;

				case 'J':
					r.left = WIDTH*9;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'K':
					r.left = WIDTH*10;
					r.right = r.left + WIDTH;
					row = 1;
				
					break;
				case 'L':
					r.left = WIDTH*11;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'M':
					r.left = WIDTH*12;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'N':
					r.left = WIDTH*13;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'O':
					r.left = WIDTH*14;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'P':
					r.left = WIDTH*15;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'Q':
					r.left = WIDTH*16;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'R':
					r.left = WIDTH*17;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'S':
					r.left = WIDTH*18;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'T':
					r.left = WIDTH*19;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'U':
					r.left = WIDTH*20;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'V':
					r.left = WIDTH*21;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'W':
					r.left = WIDTH*22;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'X':
					r.left = WIDTH*23;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case 'Y':
					r.left = WIDTH*24;
					r.right = r.left + WIDTH;
					row = 1;
					nextCharacter = 16;
					break;

				case 'Z':
					r.left = WIDTH*25;
					r.right = r.left + WIDTH;
					row = 1;
					break;

				case '!':
					r.left = WIDTH*0;
					r.right = r.left + WIDTH;
					row = 2;
					nextCharacter = 8;
					break;

				case '.':
					r.left = WIDTH*1;
					r.right = r.left + WIDTH;
					row = 2;
					nextCharacter = 6;
					break;

				case '\'':
					r.left = WIDTH*2;
					r.right = r.left + WIDTH;
					row = 2;
					nextCharacter = 8;
					break;

				case '\n':
					r.left = 0;
					r.right = 0;
					row = 2;
					nextCharacter = 0;
					pos.x = startSentencePos.x;
					pos.y+= HEIGHT;
					break;

				case ' ':
					r.left = 0;
					r.right = 0;
					row = 2;
					nextCharacter = 8;
					break;
			}

			r.top = row*HEIGHT;
			r.bottom = r.top + HEIGHT;

			matTranslate.SetAsTranslate(pos);
			GAME_ENGINE->SetTransformMatrix(matTranslate*matIdentity);
			GAME_ENGINE->DrawBitmap(m_BmpWizardTextPtr,0,0,r);

			pos.x+= nextCharacter;
		}
	}
}

void WizardText::Create(String input, int posX,int posY)
{
	m_Input = input;
	m_Pos.x = posX;
	m_Pos.y = posY;

	m_HitWizardTextPtr->SetPos(m_Pos);
}

bool WizardText::GetActive()
{
	return m_Active;
}

bool WizardText::GetActivePressed()
{
	return m_ActivePressed;
}

void WizardText::SetActive(bool value)
{
	m_Active = value;
}


