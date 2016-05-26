#pragma once

#define ADDR(X,REG)\
	__asm MOV REG,DWORD PTR DS:[X] \
	__asm MOV REG,DWORD PTR DS:[REG]

struct Line
{
	Location to;
	Unit* hero;
	bool active;
	DWORD color;
};
union myFloat
{
	float X;
	DWORD dX;
};
void HeroLineON();

void AddHeroLine(Unit* Hero, Location to);
void RemoveHeroLine(Unit* hero);
void ClearHeroLine();
