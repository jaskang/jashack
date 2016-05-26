// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>
#include <iostream>
#include <Process.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <TlHelp32.h>
#include <map>
#include <list>
#include <string>
using namespace std;

#define M_PI 3.141592653589793238462643
#define deg2rad(a) ((a)*M_PI/180)

// TODO: 在此处引用程序需要的其他头文件s
#include "Tools.h"
#include "variables.h"
#include "func.h"
#include "Jass.h"

#include "MapPatch.h"
#include "Gamestate.h"
#include "HeroLine.h"
#include "UnitCommad.h"
#include "zResourceHook.h"
#include "ColoredInvi.h"
#include "GreyHP.h"
#include "DamageNotifier.h"

#include "NumShow.h"