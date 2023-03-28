#include "G_Main.h"

#include <string>
#include <windows.h>

#include "..\..\KeySize.h"


void WindowMain::LoadLayout_Turkish()
{
	constexpr float LEFT_X		= 10;
	constexpr float TOP_Y		= 16;
	constexpr float LINE1_Y		= 75;
	constexpr float LINE2_Y		= 119;
	constexpr float LINE3_Y		= 161;
	constexpr float LINE4_Y		= 204;
	constexpr float BOTTOM_Y	= 246;
	
	constexpr float MID1_X		= 672;
	constexpr float MID2_X		= 715;
	constexpr float MID3_X		= 758;
	
	constexpr float NUM1_X		= 820;
	constexpr float NUM2_X		= 863;
	constexpr float NUM3_X		= 907;
	constexpr float NUM4_X		= 950;
	
	constexpr float KEY_W		= 36;
	constexpr float KEY_H		= 36;
	
	constexpr float TOP_W		= KEY_W;
	constexpr float TOP_H		= KEY_H;
	
	KeySize sizeTop		{	TOP_W,			TOP_H		};
	KeySize sizeKey		{	KEY_W,			KEY_H		};
	KeySize sizeBackSpc	{	80,				KEY_H		};
	KeySize sizeTab		{	60,				KEY_H		};
	KeySize sizeCpsLck	{	70,				KEY_H		};
	KeySize sizeNumP	{	KEY_W,			81			};
	KeySize sizeLShift	{	48,				KEY_H		};
	KeySize sizeRShift	{	120,			KEY_H		};
	KeySize sizeNumE	{	KEY_W,			81			};
	KeySize sizeLCtrl	{	55,				KEY_H		};
	KeySize sizeBottom	{	50,				KEY_H		};
	KeySize sizeSpace	{	270,			KEY_H		};
	KeySize sizeRCtrl	{	55,				KEY_H		};
	KeySize sizeNum0	{	83,				KEY_H		};

	

	// Virtual Key Codes:
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes



	// FUNCTION KEY LINE

	KeyboardKey	Esc		(	L"ESC",		sizeTop,	{LEFT_X,							TOP_Y},			0x1B);

	KeyboardKey	F1		(	L"F1",		sizeTop,	{93,								TOP_Y},			0x70);
	KeyboardKey	F2		(	L"F2",		sizeTop,	{137,								TOP_Y},			0x71);
	KeyboardKey	F3		(	L"F3",		sizeTop,	{179,								TOP_Y},			0x72);
	KeyboardKey	F4		(	L"F4",		sizeTop,	{222,								TOP_Y},			0x73);

	KeyboardKey	F5		(	L"F5",		sizeTop,	{290,								TOP_Y},			0x74);
	KeyboardKey	F6		(	L"F6",		sizeTop,	{332,								TOP_Y},			0x75);
	KeyboardKey	F7		(	L"F7",		sizeTop,	{375,								TOP_Y},			0x76);
	KeyboardKey	F8		(	L"F8",		sizeTop,	{416,								TOP_Y},			0x77);

	KeyboardKey	F9		(	L"F9",		sizeTop,	{482,								TOP_Y},			0x78);
	KeyboardKey	F10		(	L"F10",		sizeTop,	{526,								TOP_Y},			0x79);
	KeyboardKey	F11		(	L"F11",		sizeTop,	{568,								TOP_Y},			0x7A);
	KeyboardKey	F12		(	L"F12",		sizeTop,	{611,								TOP_Y},			0x7B);
	
	KeyboardKey	PrtScr	(	L"PS",		sizeTop,	{MID1_X,							TOP_Y},			0x2C);
	KeyboardKey	ScrLck	(	L"SL",		sizeTop,	{MID2_X,							TOP_Y},			0x91);
	KeyboardKey	Pause	(	L"BR",		sizeTop,	{MID3_X,							TOP_Y},			0x13);


	// LINE 1
	
	KeyboardKey	Quote	(	L"\"",		sizeKey,	{LEFT_X,							LINE1_Y},		0xC0);
	
	KeyboardKey	Key1	(	L"1",		sizeKey,	{54,								LINE1_Y},		0x31);
	KeyboardKey	Key2	(	L"2",		sizeKey,	{96,								LINE1_Y},		0x32);
	KeyboardKey	Key3	(	L"3",		sizeKey,	{139,								LINE1_Y},		0x33);
	KeyboardKey	Key4	(	L"4",		sizeKey,	{182,								LINE1_Y},		0x34);
	KeyboardKey	Key5	(	L"5",		sizeKey,	{225,								LINE1_Y},		0x35);
	KeyboardKey	Key6	(	L"6",		sizeKey,	{268,								LINE1_Y},		0x36);
	KeyboardKey	Key7	(	L"7",		sizeKey,	{311,								LINE1_Y},		0x37);
	KeyboardKey	Key8	(	L"8",		sizeKey,	{353,								LINE1_Y},		0x38);
	KeyboardKey	Key9	(	L"9",		sizeKey,	{395,								LINE1_Y},		0x39);
	KeyboardKey	Key0	(	L"0",		sizeKey,	{439,								LINE1_Y},		0x30);
	
	KeyboardKey	Aster	(	L"*",		sizeKey,	{482,								LINE1_Y},		0xDF);
	KeyboardKey	Hypen	(	L"-",		sizeKey,	{525,								LINE1_Y},		0xBD);
	KeyboardKey	BackSpc	(	L"BS",		sizeBackSpc,{569,								LINE1_Y},		0x08);
	
	KeyboardKey	Ins		(	L"INS",		sizeKey,	{MID1_X,							LINE1_Y},		0x2D);
	KeyboardKey	Home	(	L"HOM",		sizeKey,	{MID2_X,							LINE1_Y},		0x24);
	KeyboardKey	PU		(	L"PU",		sizeKey,	{MID3_X,							LINE1_Y},		0x21);
	
	KeyboardKey	NumLock	(	L"NL",		sizeKey,	{NUM1_X,							LINE1_Y},		0x90);
	KeyboardKey	NumSlsh	(	L"/",		sizeKey,	{NUM2_X,							LINE1_Y},		0x6F);
	KeyboardKey	NumAst	(	L"*",		sizeKey,	{NUM3_X,							LINE1_Y},		0x6A);
	KeyboardKey	NumHyp	(	L"-",		sizeKey,	{NUM4_X,							LINE1_Y},		0x6D);


	// LINE 2
	
	KeyboardKey	Tab		(	L"TAB",		sizeTab,	{LEFT_X,							LINE2_Y},		0x09);
	
	KeyboardKey	KeyQ	(	L"Q",		sizeKey,	{76,								LINE2_Y},		0x51);
	KeyboardKey	KeyW	(	L"W",		sizeKey,	{120,								LINE2_Y},		0x57);
	KeyboardKey	KeyE	(	L"E",		sizeKey,	{161,								LINE2_Y},		0x45);
	KeyboardKey	KeyR	(	L"R",		sizeKey,	{205,								LINE2_Y},		0x52);
	KeyboardKey	KeyT	(	L"T",		sizeKey,	{247,								LINE2_Y},		0x54);
	KeyboardKey	KeyY	(	L"Y",		sizeKey,	{289,								LINE2_Y},		0x59);
	KeyboardKey	KeyU	(	L"U",		sizeKey,	{332,								LINE2_Y},		0x55);
	KeyboardKey	KeyI	(	L"I",		sizeKey,	{374,								LINE2_Y},		0x49);
	KeyboardKey	KeyO	(	L"O",		sizeKey,	{416,								LINE2_Y},		0x4F);
	KeyboardKey	KeyP	(	L"P",		sizeKey,	{460,								LINE2_Y},		0x50);
	KeyboardKey	KeyYG	(	L"Ğ",		sizeKey,	{503,								LINE2_Y},		0xDB);
	KeyboardKey	KeyUU	(	L"Ü",		sizeKey,	{546,								LINE2_Y},		0xDD);
	
	KeyboardKey	Enter	(	L"",		sizeKey,	{592,								LINE2_Y},		0xFF0D);
	
	KeyboardKey	Del		(	L"DEL",		sizeKey,	{Ins.Location.x,					LINE2_Y},		0x2E);
	KeyboardKey	End		(	L"END",		sizeKey,	{Home.Location.x,					LINE2_Y},		0x23);
	KeyboardKey	PD		(	L"PD",		sizeKey,	{PU.Location.x,						LINE2_Y},		0x22);
	
	KeyboardKey	Num7	(	L"7",		sizeKey,	{NumLock.Location.x,				LINE2_Y},		0x67);
	KeyboardKey	Num8	(	L"8",		sizeKey,	{NumSlsh.Location.x,				LINE2_Y},		0x68);
	KeyboardKey	Num9	(	L"9",		sizeKey,	{NumAst.Location.x,					LINE2_Y},		0x69);
	KeyboardKey	NumP	(	L"+",		sizeNumP,	{NumHyp.Location.x,					LINE2_Y},		0x6B);


	// LINE 3

	constexpr float LINE3_OFFSET = 12;
	
	KeyboardKey	CapsLock(	L"CAPS",	sizeCpsLck,	{LEFT_X,							LINE3_Y},		0x14);
	
	KeyboardKey	KeyA	(	L"A",		sizeKey,	{KeyQ.Location.x + LINE3_OFFSET,	LINE3_Y},		0x41);
	KeyboardKey	KeyS	(	L"S",		sizeKey,	{KeyW.Location.x + LINE3_OFFSET,	LINE3_Y},		0x53);
	KeyboardKey	KeyD	(	L"D",		sizeKey,	{KeyE.Location.x + LINE3_OFFSET,	LINE3_Y},		0x44);
	KeyboardKey	KeyF	(	L"F",		sizeKey,	{KeyR.Location.x + LINE3_OFFSET,	LINE3_Y},		0x46);
	KeyboardKey	KeyG	(	L"G",		sizeKey,	{KeyT.Location.x + LINE3_OFFSET,	LINE3_Y},		0x47);
	KeyboardKey	KeyH	(	L"H",		sizeKey,	{KeyY.Location.x + LINE3_OFFSET,	LINE3_Y},		0x48);
	KeyboardKey	KeyJ	(	L"J",		sizeKey,	{KeyU.Location.x + LINE3_OFFSET,	LINE3_Y},		0x4A);
	KeyboardKey	KeyK	(	L"K",		sizeKey,	{KeyI.Location.x + LINE3_OFFSET,	LINE3_Y},		0x4B);
	KeyboardKey	KeyL	(	L"L",		sizeKey,	{KeyO.Location.x + LINE3_OFFSET,	LINE3_Y},		0x4C);
	KeyboardKey	KeySS	(	L"Ş",		sizeKey,	{KeyP.Location.x + LINE3_OFFSET,	LINE3_Y},		0xBA);
	KeyboardKey	KeyII	(	L"İ",		sizeKey,	{KeyYG.Location.x + LINE3_OFFSET,	LINE3_Y},		0xDE);
	KeyboardKey	Comma	(	L",",		sizeKey,	{KeyUU.Location.x + LINE3_OFFSET,	LINE3_Y},		0xBC);
	
	KeyboardKey	Num4	(	L"4",		sizeKey,	{Num7.Location.x,					LINE3_Y},		0x64);
	KeyboardKey	Num5	(	L"5",		sizeKey,	{Num8.Location.x,					LINE3_Y},		0x65);
	KeyboardKey	Num6	(	L"6",		sizeKey,	{Num9.Location.x,					LINE3_Y},		0x66);


	// LINE 4

	constexpr float LINE4_OFFSET = 22;
	
	KeyboardKey	LShift	(	L"⇧",		sizeLShift,	{LEFT_X,							LINE4_Y},		0xA0);
	
	KeyboardKey	KeySD	(	L"<",		sizeKey,	{65,								LINE4_Y},		0xE2);
	KeyboardKey	KeyZ	(	L"Z",		sizeKey,	{KeyA.Location.x + LINE4_OFFSET,	LINE4_Y},		0x5A);
	KeyboardKey	KeyX	(	L"X",		sizeKey,	{KeyS.Location.x + LINE4_OFFSET,	LINE4_Y},		0x58);
	KeyboardKey	KeyC	(	L"C",		sizeKey,	{KeyD.Location.x + LINE4_OFFSET,	LINE4_Y},		0x43);
	KeyboardKey	KeyV	(	L"V",		sizeKey,	{KeyF.Location.x + LINE4_OFFSET,	LINE4_Y},		0x56);
	KeyboardKey	KeyB	(	L"B",		sizeKey,	{KeyG.Location.x + LINE4_OFFSET,	LINE4_Y},		0x42);
	KeyboardKey	KeyN	(	L"N",		sizeKey,	{KeyH.Location.x + LINE4_OFFSET,	LINE4_Y},		0x4E);
	KeyboardKey	KeyM	(	L"M",		sizeKey,	{KeyJ.Location.x + LINE4_OFFSET,	LINE4_Y},		0x4D);
	KeyboardKey	KeyOO	(	L"Ö",		sizeKey,	{KeyK.Location.x + LINE4_OFFSET,	LINE4_Y},		0xBF);
	KeyboardKey	KeyCC	(	L"Ç",		sizeKey,	{KeyL.Location.x + LINE4_OFFSET,	LINE4_Y},		0xDC);
	KeyboardKey	KeyNK	(	L".",		sizeKey,	{KeySS.Location.x + LINE4_OFFSET,	LINE4_Y},		0xBE);

	KeyboardKey	RShift	(	L"⇑ SHIFT",	sizeRShift,	{KeyII.Location.x + LINE4_OFFSET,	LINE4_Y},		0xA1);

	KeyboardKey	KeyUp	(	L"↑",		sizeKey,	{End.Location.x,					LINE4_Y},		0x26);
	
	KeyboardKey	Num1	(	L"1",		sizeKey,	{Num4.Location.x,					LINE4_Y},		0x61);
	KeyboardKey	Num2	(	L"2",		sizeKey,	{Num5.Location.x,					LINE4_Y},		0x62);
	KeyboardKey	Num3	(	L"3",		sizeKey,	{Num6.Location.x,					LINE4_Y},		0x63);

	KeyboardKey	NumEnter(	L"ENT",		sizeNumE,	{NumP.Location.x,					LINE4_Y},		0x0D);


	// BOTTOM LINE

	KeyboardKey	LCtrl	(	L"CTRL",	sizeLCtrl,	{LEFT_X,							BOTTOM_Y},		0xA2);
	KeyboardKey	LWin	(	L"WIN",		sizeBottom,	{70,								BOTTOM_Y},		0x5B);
	KeyboardKey	Alt		(	L"ALT",		sizeBottom,	{123,								BOTTOM_Y},		0xA4);
	KeyboardKey	Space	(	L"SPACE",	sizeSpace,	{174,								BOTTOM_Y},		0x20);
	KeyboardKey	AltGr	(	L"AltGr",		sizeBottom,	{448,								BOTTOM_Y},		0xA5);
	KeyboardKey	RWin	(	L"WIN",		sizeBottom,	{501,								BOTTOM_Y},		0x5C);
	KeyboardKey	Menu	(	L"MN",		sizeBottom,	{553,								BOTTOM_Y},		0x5D);
	KeyboardKey	RCtrl	(	L"CTRL",	sizeLCtrl,	{607,								BOTTOM_Y},		0xA3);
	
	KeyboardKey	Left	(	L"←",		sizeKey,	{Del.Location.x,					BOTTOM_Y},		0x25);
	KeyboardKey	Down	(	L"↓",		sizeKey,	{End.Location.x,					BOTTOM_Y},		0x28);
	KeyboardKey	Right	(	L"→",		sizeKey,	{PD.Location.x,						BOTTOM_Y},		0x27);
	
	KeyboardKey	Num0	(	L"0",		sizeNum0,	{Num1.Location.x,					BOTTOM_Y},		0x60);
	KeyboardKey	NumDel	(	L"DEL",		sizeKey,	{Num3.Location.x,					BOTTOM_Y},		0x6E);






	
	Llid::KeysSmall.push_back(Esc);
	Llid::KeysLarge.push_back(F1);
	Llid::KeysLarge.push_back(F2);
	Llid::KeysLarge.push_back(F3);
	Llid::KeysLarge.push_back(F4);
	Llid::KeysLarge.push_back(F5);
	Llid::KeysLarge.push_back(F6);
	Llid::KeysLarge.push_back(F7);
	Llid::KeysLarge.push_back(F8);
	Llid::KeysLarge.push_back(F9);
	Llid::KeysLarge.push_back(F10);
	Llid::KeysLarge.push_back(F11);
	Llid::KeysLarge.push_back(F12);
	Llid::KeysLarge.push_back(PrtScr);
	Llid::KeysLarge.push_back(ScrLck);
	Llid::KeysLarge.push_back(Pause);
	Llid::KeysLarge.push_back(Quote);
	Llid::KeysLarge.push_back(Key1);
	Llid::KeysLarge.push_back(Key2);
	Llid::KeysLarge.push_back(Key3);
	Llid::KeysLarge.push_back(Key4);
	Llid::KeysLarge.push_back(Key5);
	Llid::KeysLarge.push_back(Key6);
	Llid::KeysLarge.push_back(Key7);
	Llid::KeysLarge.push_back(Key8);
	Llid::KeysLarge.push_back(Key9);
	Llid::KeysLarge.push_back(Key0);
	Llid::KeysLarge.push_back(Aster);
	Llid::KeysLarge.push_back(Hypen);
	Llid::KeysLarge.push_back(BackSpc);
	Llid::KeysSmall.push_back(Ins);
	Llid::KeysSmall.push_back(Home);
	Llid::KeysSmall.push_back(PU);
	Llid::KeysLarge.push_back(NumLock);
	Llid::KeysLarge.push_back(NumSlsh);
	Llid::KeysLarge.push_back(NumAst);
	Llid::KeysLarge.push_back(NumHyp);
	Llid::KeysSmall.push_back(Tab);
	Llid::KeysLarge.push_back(KeyQ);
	Llid::KeysLarge.push_back(KeyW);
	Llid::KeysLarge.push_back(KeyE);
	Llid::KeysLarge.push_back(KeyR);
	Llid::KeysLarge.push_back(KeyT);
	Llid::KeysLarge.push_back(KeyY);
	Llid::KeysLarge.push_back(KeyU);
	Llid::KeysLarge.push_back(KeyI);
	Llid::KeysLarge.push_back(KeyO);
	Llid::KeysLarge.push_back(KeyP);
	Llid::KeysLarge.push_back(KeyYG);
	Llid::KeysLarge.push_back(KeyUU);
	//Llid::KeysLarge.push_back(Enter);
	Llid::KeysSmall.push_back(Del);
	Llid::KeysSmall.push_back(End);
	Llid::KeysSmall.push_back(PD);
	Llid::KeysLarge.push_back(Num7);
	Llid::KeysLarge.push_back(Num8);
	Llid::KeysLarge.push_back(Num9);
	Llid::KeysLarge.push_back(NumP);
	Llid::KeysLarge.push_back(CapsLock);
	Llid::KeysLarge.push_back(KeyA);
	Llid::KeysLarge.push_back(KeyS);
	Llid::KeysLarge.push_back(KeyD);
	Llid::KeysLarge.push_back(KeyF);
	Llid::KeysLarge.push_back(KeyG);
	Llid::KeysLarge.push_back(KeyH);
	Llid::KeysLarge.push_back(KeyJ);
	Llid::KeysLarge.push_back(KeyK);
	Llid::KeysLarge.push_back(KeyL);
	Llid::KeysLarge.push_back(KeySS);
	Llid::KeysLarge.push_back(KeyII);
	Llid::KeysLarge.push_back(Comma);
	Llid::KeysLarge.push_back(Num4);
	Llid::KeysLarge.push_back(Num5);
	Llid::KeysLarge.push_back(Num6);
	Llid::KeysLarge.push_back(LShift);
	Llid::KeysLarge.push_back(KeySD);
	Llid::KeysLarge.push_back(KeyZ);
	Llid::KeysLarge.push_back(KeyX);
	Llid::KeysLarge.push_back(KeyC);
	Llid::KeysLarge.push_back(KeyV);
	Llid::KeysLarge.push_back(KeyB);
	Llid::KeysLarge.push_back(KeyN);
	Llid::KeysLarge.push_back(KeyM);
	Llid::KeysLarge.push_back(KeyOO);
	Llid::KeysLarge.push_back(KeyCC);
	Llid::KeysLarge.push_back(KeyNK);
	Llid::KeysLarge.push_back(RShift);
	Llid::KeysLarge.push_back(KeyUp);
	Llid::KeysLarge.push_back(Num1);
	Llid::KeysLarge.push_back(Num2);
	Llid::KeysLarge.push_back(Num3);
	Llid::KeysSmall.push_back(NumEnter);
	Llid::KeysSmall.push_back(LCtrl);
	Llid::KeysSmall.push_back(LWin);
	Llid::KeysSmall.push_back(Alt);
	Llid::KeysLarge.push_back(Space);
	Llid::KeysSmall.push_back(AltGr);
	Llid::KeysSmall.push_back(RWin);
	Llid::KeysSmall.push_back(Menu);
	Llid::KeysSmall.push_back(RCtrl);
	Llid::KeysLarge.push_back(Left);
	Llid::KeysLarge.push_back(Down);
	Llid::KeysLarge.push_back(Right);
	Llid::KeysLarge.push_back(Num0);
	Llid::KeysSmall.push_back(NumDel);







	
	Llid::EnterVertices.push_back({591,			LINE2_Y});
	Llid::EnterVertices.push_back({591,			155});
	Llid::EnterVertices.push_back({605,			155});
	Llid::EnterVertices.push_back({605,			198});
	Llid::EnterVertices.push_back({650,			198});
	Llid::EnterVertices.push_back({650,			LINE2_Y});
	Llid::EnterVertices.push_back({591,			LINE2_Y});
	
	Llid::EnterArrowVertices.push_back({640,	155});
	Llid::EnterArrowVertices.push_back({640,	170});
	Llid::EnterArrowVertices.push_back({615,	170});
	Llid::EnterArrowVertices.push_back({620,	165});
	Llid::EnterArrowVertices.push_back({615,	170});
	Llid::EnterArrowVertices.push_back({620,	175});
	
	//Llid::ArrowKeyVertices_Up.push_back({,	});




}

