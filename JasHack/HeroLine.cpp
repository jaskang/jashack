#include "stdafx.h"
#include "HeroLine.h"


list<Line> HeroLines;

DWORD addrW3Minimap;

DWORD addrMinimapDrawHook;
DWORD addrMinimapDrawJMP;

DWORD addrConvertCoord1;
DWORD addrConvertCoord2;

DWORD _BigAssFloat;
DWORD _MmapOffset;
DWORD _W3XConversion;





float Distance(Location one, Location two)
{
	float A = (one.X - two.X);
	float B = (one.Y - two.Y);
	float C = (one.Z - two.Z);
	return sqrtf(A * A + B * B + C * C);
}
DWORD Distance(MmapLoc one, MmapLoc two)
{
	float A = ((float)one.X - (float)two.X);
	float B = ((float)one.Y - (float)two.Y);
	return (DWORD)floor(sqrtf(A * A + B * B));
}

void ConvertMmap(MmapLoc& loc)
{
	DWORD X = loc.X, Y = loc.Y;
	__asm
	{
		MOV EAX,X;
		SAR EAX,2;
		MOV X,EAX;
		MOV EAX,Y;
		SAR EAX,2;
		MOV Y,EAX;
	}
	DWORD Base;
	float xMult, yMult;
	double unk;
	DWORD xOffset, yOffset, xUpperBound, yUpperBound;
	DWORD unk2, unk3;
	float bigAssFloat;
	memcpy(&Base, (void*)addrW3Minimap, sizeof(Base));
	memcpy(&bigAssFloat, (void*)(_BigAssFloat), sizeof(bigAssFloat));
	memcpy(&xUpperBound, (void*)(Base + 0x224), sizeof(xUpperBound));
	memcpy(&xOffset, (void*)(Base + 0x228), sizeof(xOffset));
	memcpy(&yUpperBound, (void*)(Base + 0x230), sizeof(yUpperBound));
	memcpy(&yOffset, (void*)(Base + 0x22C), sizeof(yOffset));
	memcpy(&xMult, (void*)(Base + 0x21C), sizeof(xMult));
	memcpy(&yMult, (void*)(Base + 0x220), sizeof(yMult));
	memcpy(&unk, (void*)(_MmapOffset), sizeof(unk));
	memcpy(&unk2, (void*)(Base + 0x214), sizeof(unk2));
	memcpy(&unk3, (void*)(Base + 0x218), sizeof(unk3));

	if (X <= xOffset)
	{
		X = xOffset;
	}
	else if (X >= xUpperBound)
	{
		X = xUpperBound;
	}
	if (Y <= yOffset)
	{
		Y = yOffset;
	}
	else if (Y >= yUpperBound)
	{
		Y = yUpperBound;
	}


	DWORD edxConst = 2; // this is a little different for buildings but hey we're just drawing a line :D

	DWORD maxX = 0x101 - 2 * edxConst - 1;
	DWORD maxY = 0xFF - unk3 - 2 * edxConst;
	X -= xOffset;
	Y -= yOffset;

	myFloat fX, fY;
	if (X < 0)
	{
		fX.X = (float)X + bigAssFloat;
	}
	else
	{

		fX.X = (float)X;
	}
	if (Y < 0)
	{
		fY.X = (float)Y + bigAssFloat;
	}
	else
	{

		fY.X = (float)Y;
	}

	fX.X = (float)(fX.X * xMult + unk);
	fY.X = (float)(fY.X * yMult + unk);
	__asm
	{
		MOV EAX,fX.dX
			SHR EAX,0xE
			MOVZX EAX,AL
			MOV X,EAX
			MOV EAX,fY.dX
			SHR EAX,0xE
			MOVZX EAX,AL
			MOV Y,EAX
	};
	X += (unk2 - edxConst);
	Y = 0x100 - Y - unk3 - edxConst;

	if (X <= 0)
	{
		X = 1;
	}
	else if (X >= maxX)
	{
		X = maxX;
	}

	if (Y <= 0)
	{
		Y = 1;
	}
	else if (Y >= maxY)
	{
		Y = maxY;
	}

	loc.X = X;
	loc.Y = Y;
}
DWORD CoordToMinimap(float Loc, DWORD offst)
{
	float Result;
	DWORD result;
	__asm
	{
		ADDR(_W3XConversion,EAX)
			add EAX,offst
			PUSH EAX
			LEA EDX,Loc
			LEA ECX,Result
			CALL addrConvertCoord1
			MOV ECX,DWORD PTR DS:[EAX]
		LEA EAX,DWORD PTR DS:[ECX+0xFD000000]
		XOR EAX,ECX
			SAR EAX,0x1F
			LEA EDX,DWORD PTR DS:[ECX+0xFD800000]
		NOT EAX
			AND EAX,EDX
			LEA ECX,Result
			MOV DWORD PTR DS:[ECX],EAX
			CALL addrConvertCoord2
			MOV result,EAX
	}
	return result;
}

MmapLoc LocationToMinimap(Location loc)
{
	MmapLoc ret;
	ret.X = CoordToMinimap(loc.X, 0x6C);
	ret.Y = CoordToMinimap(loc.Y, 0x70);
	ConvertMmap(ret);
	return ret;
}


void DrawPixel(DWORD X, DWORD Y, DWORD Color)
{
	__asm
	{
		ADDR(addrW3Minimap,EDI);
		MOV EDI,DWORD PTR DS:[EDI+0x1D8];
		MOV EAX,Y
			SHL EAX,8
			MOV ECX,X
			ADD EAX,ECX
			MOV ECX,Color
			MOV DWORD PTR DS:[EDI+4*EAX],ECX;
	}
}
void DrawLine(MmapLoc From, MmapLoc To, DWORD Color)
{
	int x2 = To.X, y2 = To.Y, x1 = From.X, y1 = From.Y, x, y, xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels;
	int deltax = abs(x2 - x1);        // The difference between the x's
	int deltay = abs(y2 - y1);        // The difference between the y's
	x = x1;                       // Start x off at the first pixel
	y = y1;                       // Start y off at the first pixel
	if (x2 >= x1)                 // The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                          // The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}
	if (y2 >= y1)                 // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                          // The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}
	if (deltax >= deltay)         // There is at least one x-value for every y-value
	{
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else                          // There is at least one y-value for every x-value
	{
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}

	for (int curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		DrawPixel(x, y, Color);
		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den)             // Check if numerator >= denominator
		{
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
}
void DrawLine(Location from, Location to, DWORD Color)
{
	MmapLoc From = LocationToMinimap(from);
	MmapLoc To = LocationToMinimap(to);
	DrawLine(From, To, Color);
	From.X += 1;
	To.X += 1;
	DrawLine(From, To, Color);
	From.X -= 1;
	To.X -= 1;
	From.Y -= 1;
	To.Y -= 1;
	DrawLine(From, To, Color);
}

void DrawHeroLines()
{
	list<Line>::iterator iter = HeroLines.begin(), iter2 = iter;
	while (iter != HeroLines.end())
	{
		iter2 = iter++;
		if (MyIsUnitDead(MyGetUnitByOffset((DWORD)iter2->hero)))
		{
			HeroLines.erase(iter2);
			continue;
		}
		Location from;
		from.X= MyGetUnitX(MyGetUnitByOffset((DWORD)iter2->hero));
		from.Y= MyGetUnitY(MyGetUnitByOffset((DWORD)iter2->hero));
		if (Distance(from, iter2->to) < 200.0)
		{
			iter2->active = false;
		}
		if (iter2->active)
			DrawLine(from, iter2->to, iter2->color);
		else
			HeroLines.erase(iter2);
	}

}

void _declspec(naked) DrawLineOnMinimap()
{
	__asm
	{
		PUSH EBP;
		MOV EBP,ESP;
		SUB ESP,0x30;
		PUSHAD;
	}
	DrawHeroLines();
	//DanceUnits();
	__asm
	{
		POPAD;
		MOV ESP,EBP;
		POP EBP;
		MOV ECX,DWORD PTR SS:[ESP+0x7C];
		POP EDI;
		JMP addrMinimapDrawJMP;
	}
}
DWORD JGetPlayerColor(DWORD slot)
{
	__asm
	{
		ADDR(addrW3Minimap,EDI)
			MOV ESI,slot
			LEA EAX,DWORD PTR DS:[EDI+ESI*4+0x23C];
		MOV EAX,DWORD PTR DS:[EAX]
	}
}

void AddHeroLine(Unit* Hero, Location to)
{
	RemoveHeroLine(Hero);
	Line ln;
	ln.active = true;
	ln.hero = Hero;
	ln.to = to;
	ln.color = JGetPlayerColor(Hero->dwOwnerSlot);
	HeroLines.push_back(ln);
}

void RemoveHeroLine(Unit* hero)
{
	list<Line>::iterator iter = HeroLines.begin(), iter2 = iter;
	while (iter != HeroLines.end())
	{
		iter2 = iter++;
		if (iter2->hero == hero)
		{
			iter2->active = false;
			HeroLines.erase(iter2);
			break;
		}
	}
}

void ClearHeroLine()
{
	HeroLines.clear();
}
void HeroLineON()
{
	addrW3Minimap=GameBase+0xACD06C;

	addrMinimapDrawHook=GameBase+0x362BF1;
	addrMinimapDrawJMP=GameBase+0x362BF6;

	addrConvertCoord1=GameBase+0x6EF5D0;
	addrConvertCoord2=GameBase+0x6EF300;

	_BigAssFloat=GameBase+0x887BC8;
	_MmapOffset=GameBase+0x94C1F8;
	_W3XConversion=GameBase+0xACE1C0;

	PatchJMP((BYTE*)(addrMinimapDrawHook),(BYTE*)DrawLineOnMinimap,5);
	

}