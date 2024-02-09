#include "iGraphics.h"
#include <windows.h>
#include "mmsystem.h"
#include <math.h>
#include <string.h>

/*********************/
// defining const , variables
int screenwidth = 750;
int ScreenHeight = 500;
int menubuttonwidth = 284;
int menubuttonheight = 96;
int programstate = 0; // 0-main menu  1- arithmetic 2-scientific 3-logical
int ArithmeticNormalButtonWidth = 62;
int ArithmeticNormalButtonHeight = 60;
int ScientificNormalButtonWidth = 54;
int ScientificNormalButtonHeight = 55;
char expression[200];
int expressionind=0;
bool isAnsClicked = false;
bool musicOn = true;
char finalans[200];
#define pi 3.1416
//char pre[100]; //ekbar = click korar por abar onno operation e click korle ager ans store kore rakhbe


/*************************/
// including images and buttons
char bg[5][70] = {"bgs\\bg.bmp", "bgs\\bgari.bmp", "bgs\\bgsci.bmp", "bgs\\bglogic.bmp"};
char buttons[20][70] = {"buttons\\arithmetic.bmp", "buttons\\scientific.bmp", "buttons\\logical.bmp"};

//_TCHAR sound[3][40] = { TEXT("click.wav") };


/****************/
// defining functinal prototypesz
void DrawMenu();
void arithmeticinput(int mx, int my);
void  scientificinput(int mx, int my);
void logicalinput(int mx, int my);
void showexpression();
void calculate();
void ArithmeticInputKey(char key);
void ScientificInputKey(char key);
void LogicalInputKey(char key);
void resetalldata();
void resetexpression();
int finalanslen();
int fact(int n);

void iDraw()
{
	iClear();
	// printf("Now programstate is %d\n", programstate);

	// bibhinno programstate e bhibhinno bg and setup
	
	switch (programstate)
	{
	case 0:
		DrawMenu();
		break;
	case 1:
		
		iShowBMP(0, 0, bg[1]);
		showexpression();
		if(isAnsClicked){
		iText(657-strlen(finalans)*10,384,finalans,GLUT_BITMAP_TIMES_ROMAN_24); //ans dekhay
	}
	else{
		iText(0,0," ",GLUT_BITMAP_TIMES_ROMAN_24);
	}
		
		break;
		
	case 2:
		iShowBMP(0, 0, bg[2]);
		showexpression();
		if(isAnsClicked){
		iText(657-strlen(finalans)*10,384,finalans,GLUT_BITMAP_TIMES_ROMAN_24); //ans dekhay
	}
	else{
		iText(0,0," ",GLUT_BITMAP_TIMES_ROMAN_24);
	}
		break;
	case 3:
		iShowBMP(0, 0, bg[3]);
		showexpression();
		if(isAnsClicked){
		iText(657-strlen(finalans)*10,384,finalans,GLUT_BITMAP_TIMES_ROMAN_24); //ans dekhay
	}
	else{
		iText(0,0," ",GLUT_BITMAP_TIMES_ROMAN_24);
	}
		break;
	default:
		break;
	}	
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)

{
	if (programstate == 0)
	{
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			// main menu te thaka obosthay dekhbo koi click hocche

			// printf("x= %d  y=%d\n", mx, my);
			if (mx >= 230 && mx <= 230 + menubuttonwidth && my >= 335 && my <= 335 + menubuttonheight)
			{ // arithmetic e click korse
				programstate = 1;
				PlaySound("sound\\click.wav", NULL, SND_ASYNC);
			}
			else if (mx >= 230 && mx <= 230 + menubuttonwidth && my >= 220 && my <= 220 + menubuttonheight)
			{ // scientfic e clicked
				programstate = 2;
				PlaySound("sound\\click.wav", NULL, SND_ASYNC);
			}
			else if (mx >= 230 && mx <= 230 + menubuttonwidth && my >= 105 && my <= 105 + menubuttonheight)
			{ // logical clicked
				programstate = 3;
				PlaySound("sound\\click.wav", NULL, SND_ASYNC);
			}
		}
	}
	// ekhon onno programstate e screen er mouse click handle korbo
	else if (programstate == 1)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			// artithemtic operation er screen e
			arithmeticinput(mx, my); // arithmetic screen er input bhibhinno buitton e click er jonno alada func
	}
	else if (programstate == 2)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		  scientificinput(mx, my);
	}
	else if (programstate == 3)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			logicalinput(mx, my);
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if(programstate==1){
		ArithmeticInputKey(key);
	}
	if(programstate==2){
		ScientificInputKey(key);
	}
	// place your codes for other keys here
}
void resetexpression(){
	memset(expression,0,sizeof(expression));
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	// place your codes for other keys here
}
void DrawMenu()
{
	iShowBMP(0, 0, bg[0]);
	iShowBMP2(230, 335, buttons[0], 0);
	iShowBMP2(230, 220, buttons[1], 0);
	iShowBMP2(230, 105, buttons[2], 0);
}
void ArithmeticInputKey(char key){
if(programstate==1){
   if(key=='1'){
	 expression[expressionind] = '1';
	 expressionind++;
   }
   else if(key=='2'){
	expression[expressionind] = '2';
	expressionind++;
   }
    else if(key=='3'){
	expression[expressionind] = '3';
	expressionind++;
   }
    else if(key=='4'){
	expression[expressionind] = '4';
	expressionind++;
   }
    else if(key=='5'){
	expression[expressionind] = '5';
	expressionind++;
   }
    else if(key=='6'){
	expression[expressionind] = '6';
	expressionind++;
   }
    else if(key=='7'){
	expression[expressionind] = '7';
	expressionind++;
   }
    else if(key=='8'){
	expression[expressionind] = '8';
	expressionind++;
   }
    else if(key=='9'){
	expression[expressionind] = '9';
	expressionind++;
   }
    else if(key=='0'){
	expression[expressionind] = '0';
	expressionind++;
   }
    else if(key=='+'){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;

		}
	
   }
    else if(key=='-'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '-';
		}
		else{
			expression[expressionind] = '-';
			expressionind++;

		}
   }
    else if(key=='x'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = 'x';
		}
		else{
			expression[expressionind] = 'x';
			expressionind++;

		}
   }
    else if(key=='/'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '/';
		}
		else{
			expression[expressionind] = '/';
			expressionind++;

		}
   }
    else if(key=='%'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '%';
		}
		else{
			expression[expressionind] = '%';
			expressionind++;

		}
   }
    else if(key=='.'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '.';
		}
		else{
			expression[expressionind] = '.';
			expressionind++;

		}
   }
    else if(key=='='){
	  calculate();
	  isAnsClicked=true;
   }
    else if(key=='C'){
	if(expressionind>0)
	  expression[--expressionind] = '\0';
	  
   }
}
}
void arithmeticinput(int mx, int my)
{
	if (mx >= 0 && mx <= 115 && my >= 0 && my <= 50)
	{ // back button e click poreche, main menu te return jabo

		programstate = 0;
		resetalldata();
		
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		PlaySound("sound\\bgmusic.wav", NULL, SND_ASYNC);
	}

	/*****Er por ar kun button e click korle ki hobe niche implement korte hobe*/
	else if(mx>=188 &&  mx<= 188+ArithmeticNormalButtonWidth && my>=287 && my<=287+ArithmeticNormalButtonHeight){
		//clicked 1
		expression[expressionind] = '1';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
    else if(mx>=273 && mx<= 273+ArithmeticNormalButtonWidth && my>=285 && my<=285+ArithmeticNormalButtonHeight){
		expression[expressionind] = '2';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=360 && mx<= 360+ArithmeticNormalButtonWidth && my>=287 && my<=287+ArithmeticNormalButtonHeight){
		expression[expressionind] = '3';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=185 && mx<= 185+ArithmeticNormalButtonWidth && my>=220 && my<=220+ArithmeticNormalButtonHeight){
		expression[expressionind] = '4';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=273 && mx<= 273+ArithmeticNormalButtonWidth && my>=220 && my<=220+ArithmeticNormalButtonHeight){
		expression[expressionind] = '5';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=356 && mx<= 356+ArithmeticNormalButtonWidth && my>=222 && my<=222+ArithmeticNormalButtonHeight){
		expression[expressionind] = '6';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=190 && mx<= 190+ArithmeticNormalButtonWidth && my>=150 && my<=150+ArithmeticNormalButtonHeight){
		expression[expressionind] = '7';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=280 && mx<=  280+ArithmeticNormalButtonWidth && my>=150 && my<=150+ArithmeticNormalButtonHeight){
		expression[expressionind] = '8';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
    else if(mx>=359 && mx<= 359+ArithmeticNormalButtonWidth && my>=150 && my<=150+ArithmeticNormalButtonHeight){
		expression[expressionind] = '9';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=183 && mx<= 183+151 && my>=80 && my<=80+59){
		expression[expressionind] = '0';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=438 && mx<= 438+ArithmeticNormalButtonWidth && my>=222 && my<=222+ArithmeticNormalButtonHeight){
		/*if(isAnsClicked){
			//printf("Expression : %s and current ind = %d\n",expression,expressionind);
			//strcpy(expression,"");
			strncpy(expression,finalans ,6);
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;
		}*/
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	else if(mx>=443 && mx<= 443+ArithmeticNormalButtonWidth && my>=154 && my<=154+ArithmeticNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '-';
		}
		else{
			expression[expressionind] = '-';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		
	}
	
	else if(mx>=525 && mx<= 525+ArithmeticNormalButtonWidth && my>=285 && my<=285+ArithmeticNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = 'x';
		}
		else{
			expression[expressionind] = 'x';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx>=527 && mx<= 527+ArithmeticNormalButtonWidth && my>=224 && my<=224+ArithmeticNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '/';
		}
		else{
			expression[expressionind] = '/';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx>=524 && mx<= 524+ArithmeticNormalButtonWidth && my>=150 && my<=150+ArithmeticNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '%';
		}
		else{
			expression[expressionind] = '%';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
    else if(mx>=442 && mx<= 442+ArithmeticNormalButtonWidth && my>=288 && my<=288+ArithmeticNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '.';
		}
		else{
			expression[expressionind] = '.';
			expressionind++;

		}
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	
	else if(mx>=363 && mx<= 363+ArithmeticNormalButtonWidth && my>=84 && my<=84+ArithmeticNormalButtonHeight ){
		if(expressionind>0)
			expression[--expressionind] = '\0';//removing 1 character from input given by user
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx>=441 && mx<=441+144 && my>=83 && my<=83+55){
		// = clicked
		calculate();
		isAnsClicked=true;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
}
void logicalinput(int mx, int my)
{
	if (mx >= 0 && mx <= 115 && my >= 0 && my <= 50)
	{ // back button e click poreche, main menu te return jabo

		programstate = 0;
		resetalldata();
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	/*****Er por ar kun button e click korle ki hobe niche implement korte hobe*/
}
void scientificinput(int mx, int my)
{
	if (mx >= 0 && mx <= 115 && my >= 0 && my <= 50)
	{ // back button e click poreche, main menu te return jabo

		programstate = 0;
		resetalldata();
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		PlaySound("sound\\bgmusic.wav", NULL, SND_ASYNC);
	}
	/*****Er por ar kun button e click korle ki hobe niche implement korte hobe*/
	else if(mx >=80  && mx<= 80+ScientificNormalButtonWidth   && my>= 281  && my<= 281+ScientificNormalButtonHeight){
        expression[expressionind] = '1';
		expressionind++;
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
        
	}
	else if(mx >=160  && mx<= 160+ScientificNormalButtonWidth   && my>= 281  && my<= 281+ScientificNormalButtonHeight){
        expression[expressionind] = '2';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=240  && mx<= 240+ScientificNormalButtonWidth   && my>= 281  && my<= 281+ScientificNormalButtonHeight){
        expression[expressionind] = '3';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=80  && mx<= 80+ScientificNormalButtonWidth   && my>= 219  && my<= 219+ScientificNormalButtonHeight){
        expression[expressionind] = '4';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=160 && mx<= 160+ScientificNormalButtonWidth   && my>= 215  && my<= 215+ScientificNormalButtonHeight){
        expression[expressionind] = '5';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=236  && mx<= 236+ScientificNormalButtonWidth   && my>= 215  && my<= 215+ScientificNormalButtonHeight){
        expression[expressionind] = '6';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=80  && mx<= 80+ScientificNormalButtonWidth   && my>= 150  && my<= 159+ScientificNormalButtonHeight){
        expression[expressionind] = '7';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=160  && mx<= 160+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
        expression[expressionind] = '8';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=236  && mx<= 236+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
        expression[expressionind] = '9';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=80  && mx<= 214   && my>= 85  && my<= 132){
        expression[expressionind] = '0';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=237  && mx<= 237+ScientificNormalButtonWidth   && my>= 88  && my<= 88+ScientificNormalButtonHeight){
		if(expressionind>0) // c is clicked
        expression[--expressionind] = '\0';
		PlaySound("sound\\click.wav", NULL, SND_ASYNC);
        
	}
	else if(mx >=311  && mx<= 311+ScientificNormalButtonWidth   && my>= 280  && my<= 280+ScientificNormalButtonHeight){
        expression[expressionind] = '.';
		expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=311  && mx<= 311+ScientificNormalButtonWidth   && my>= 220  && my<= 220+ScientificNormalButtonHeight){
        // expression[expressionind] = '+';
		// expressionind++;
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;

		}
       PlaySound("sound\\click.wav", NULL, SND_ASYNC); 
	}
	else if(mx >=311  && mx<= 311+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
        // expression[expressionind] = '-';
		// expressionind++;
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '-';
		}
		else{
			expression[expressionind] = '-';
			expressionind++;

		}
       PlaySound("sound\\click.wav", NULL, SND_ASYNC); 
	}
	else if(mx >=311  && mx<= 311+ScientificNormalButtonWidth   && my>= 90  && my<= 90+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = 's';
			expression[expressionind++] = 'q';
			expression[expressionind++] = 'r';
			expression[expressionind++] = 't';
			//expression[expressionind++] = '>';
		}
		else{
			expression[expressionind++] = 's';
			expression[expressionind++] = 'q';
			expression[expressionind++] = 'r';
			expression[expressionind++] = 't';
			//expression[expressionind++] = '>';
			

		}
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=387  && mx<= 387+ScientificNormalButtonWidth   && my>= 280  && my<= 280+ScientificNormalButtonHeight){
     if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = 'x';
		}
		else{
			expression[expressionind] = 'x';
			expressionind++;

		}
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=387  && mx<= 387+ScientificNormalButtonWidth   && my>= 220  && my<= 220+ScientificNormalButtonHeight){
       if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '/';
		}
		else{
			expression[expressionind] = '/';
			expressionind++;

		}
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=387  && mx<= 387+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
       if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '%';
		}
		else{
			expression[expressionind] = '%';
			expressionind++;

		}
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=387  && mx<= 387+ScientificNormalButtonWidth   && my>= 90  && my<= 90+ScientificNormalButtonHeight){
        //expression[expressionind++] = 'x';
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '^';
		    expression[expressionind++] = '-';
		    expression[expressionind++] = '1';
		}
		else{
			
            expression[expressionind++] = '^';
		    expression[expressionind++] = '-';
		    expression[expressionind++] = '1';
		}
		// expression[expressionind++] = '^';
		// expression[expressionind++] = '-';
		// expression[expressionind++] = '1';
		
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=460  && mx<= 460+ScientificNormalButtonWidth   && my>= 280  && my<= 280+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = 's';
            expression[expressionind++] = 'i';
            expression[expressionind++] = 'n';
		}
		else{
			
            expression[expressionind++] = 's';
            expression[expressionind++] = 'i';
            expression[expressionind++] = 'n';
		}
        
		//expression[expressionind++] = '(';

       PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		//expressionind++;
        
	}
	else if(mx >=460  && mx<= 460+ScientificNormalButtonWidth   && my>= 220  && my<= 220+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = 't';
	        expression[expressionind++] = 'a';
            expression[expressionind++] = 'n';
		}
		else{
			
           expression[expressionind++] = 't';
	       expression[expressionind++] = 'a';
            expression[expressionind++] = 'n';
		}
       
       //expression[expressionind++] = '(';

		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=460  && mx<= 460+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			 expression[expressionind++] = 'a';
		expression[expressionind++] = 'c';
		expression[expressionind++] = 'o';
		expression[expressionind++] = 's';
		}
		else{
			
           expression[expressionind++] = 'a';
		expression[expressionind++] = 'c';
		expression[expressionind++] = 'o';
		expression[expressionind++] = 's';
		}
     
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=460  && mx<= 460+ScientificNormalButtonWidth   && my>= 90  && my<= 90+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			 expression[expressionind++] = {'l'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'g'};
		}
		else{
			
        expression[expressionind++] = {'l'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'g'};
		}
  
		//expression[expressionind++] = {'('};
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=540  && mx<= 540+ScientificNormalButtonWidth   && my>= 280  && my<= 280+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = {'c'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'s'};
		}
		else{
		 expression[expressionind++] = {'c'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'s'};
		}
        
		//expression[expressionind++] = {'('};
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=540  && mx<= 540+ScientificNormalButtonWidth   && my>= 220  && my<= 220+ScientificNormalButtonHeight){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = {'a'};
		expression[expressionind++] = {'s'};
		expression[expressionind++] = {'i'};
		expression[expressionind++] = {'n'};
		}
		else{
		expression[expressionind++] = {'a'};
		expression[expressionind++] = {'s'};
		expression[expressionind++] = {'i'};
		expression[expressionind++] = {'n'};
		}
		//expression[expressionind++] = {'('};
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=540  && mx<= 540+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
		//atan clicked
        if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = {'a'};
		expression[expressionind++] = {'c'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'s'};
		}
		else{
		expression[expressionind++] = {'a'};
		expression[expressionind++] = {'c'};
		expression[expressionind++] = {'o'};
		expression[expressionind++] = {'s'};
		}
		//expression[expressionind++] = {'('};
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=540 && mx<= 540+ScientificNormalButtonWidth   && my>= 90  && my<= 90+ScientificNormalButtonHeight){
		//x^n clicked
        //expression[expressionind++] = 'x';
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = '^';
		}
		else{
		expression[expressionind++] = '^';
		}
		expression[expressionind++] = '^';
		//expression[expressionind++] = 'n';
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=620 && mx<= 620+ScientificNormalButtonWidth   && my>= 280  && my<= 280+ScientificNormalButtonHeight){
		// x! clicked
        //expression[expressionind++] = 'x';
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = '!';
		}
		else{
		expression[expressionind++] = '!';;
		}
		
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=620 && mx<= 620+ScientificNormalButtonWidth   && my>= 220  && my<= 220+ScientificNormalButtonHeight){
		//nCr clicked
        //expression[expressionind++] = 'n';
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		 expression[expressionind++] = 'C';
		}
		else{
		expression[expressionind++] = 'C';
		}
	
		//expression[expressionind++] = 'r';
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=620 && mx<= 620+ScientificNormalButtonWidth   && my>= 150  && my<= 150+ScientificNormalButtonHeight){
		//nPr clicked
        //expression[expressionind++] = 'n';
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
		expression[expressionind++] = 'P';
		}
		else{
		expression[expressionind++] = 'P';
		}
		
		//expression[expressionind++] = 'r';
		//expressionind++;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
	else if(mx >=620 && mx<= 620+ScientificNormalButtonWidth   && my>= 90  && my<= 90+ScientificNormalButtonHeight){
        //= clicked
        calculate();
		isAnsClicked=true;
        PlaySound("sound\\click.wav", NULL, SND_ASYNC);
	}
    
}
void ScientificInputKey(char key){
	if(programstate==2){
      if(key=='1'){
	 expression[expressionind] = '1';
	 expressionind++;
   }
   else if(key=='2'){
	expression[expressionind] = '2';
	expressionind++;
   }
    else if(key=='3'){
	expression[expressionind] = '3';
	expressionind++;
   }
    else if(key=='4'){
	expression[expressionind] = '4';
	expressionind++;
   }
    else if(key=='5'){
	expression[expressionind] = '5';
	expressionind++;
   }
    else if(key=='6'){
	expression[expressionind] = '6';
	expressionind++;
   }
    else if(key=='7'){
	expression[expressionind] = '7';
	expressionind++;
   }
    else if(key=='8'){
	expression[expressionind] = '8';
	expressionind++;
   }
    else if(key=='9'){
	expression[expressionind] = '9';
	expressionind++;
   }
    else if(key=='0'){
	expression[expressionind] = '0';
	expressionind++;
   }
    else if(key=='+'){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;

		}
	
   }
    else if(key=='-'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '-';
		}
		else{
			expression[expressionind] = '-';
			expressionind++;

		}
   }
    else if(key=='x'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = 'x';
		}
		else{
			expression[expressionind] = 'x';
			expressionind++;

		}
   }
    else if(key=='/'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '/';
		}
		else{
			expression[expressionind] = '/';
			expressionind++;

		}
   }
    else if(key=='%'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '%';
		}
		else{
			expression[expressionind] = '%';
			expressionind++;

		}
   }
    else if(key=='.'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '.';
		}
		else{
			expression[expressionind] = '.';
			expressionind++;

		}
   }
    else if(key=='t'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = 't';
			expression[expressionind++] = 'a';
			expression[expressionind++] = 'n';
			expression[expressionind++] = '(';
		}
		else{
			expression[expressionind++] = 't';
            expression[expressionind++] = 'a';
			expression[expressionind++] = 'n';
			expression[expressionind++] = '(';
			//expressionind++;

		}
   }
    else if(key=='='){
	  calculate();
	  isAnsClicked=true;
   }
    else if(key=='C'){
	if(expressionind>0)
	  expression[--expressionind] = '\0';
	  
   }

	}
	
}
void LogicalInputKey(char key){
	if(programstate==3){
		 if(key=='1'){
	 expression[expressionind] = '1';
	 expressionind++;
   }
   else if(key=='2'){
	expression[expressionind] = '2';
	expressionind++;
   }
    else if(key=='3'){
	expression[expressionind] = '3';
	expressionind++;
   }
    else if(key=='4'){
	expression[expressionind] = '4';
	expressionind++;
   }
    else if(key=='5'){
	expression[expressionind] = '5';
	expressionind++;
   }
    else if(key=='6'){
	expression[expressionind] = '6';
	expressionind++;
   }
    else if(key=='7'){
	expression[expressionind] = '7';
	expressionind++;
   }
    else if(key=='8'){
	expression[expressionind] = '8';
	expressionind++;
   }
    else if(key=='9'){
	expression[expressionind] = '9';
	expressionind++;
   }
    else if(key=='0'){
	expression[expressionind] = '0';
	expressionind++;
   }
    else if(key=='+'){
		if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '+';
		}
		else{
			expression[expressionind] = '+';
			expressionind++;

		}
	
   }
    else if(key=='-'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '-';
		}
		else{
			expression[expressionind] = '-';
			expressionind++;

		}
   }
    else if(key=='x'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = 'x';
		}
		else{
			expression[expressionind] = 'x';
			expressionind++;

		}
   }
    else if(key=='/'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '/';
		}
		else{
			expression[expressionind] = '/';
			expressionind++;

		}
   }
    else if(key=='%'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			//printf("Expression ind %d and final ans size %d\n",expressionind,sizeof(expression));
			expression[expressionind++] = '%';
		}
		else{
			expression[expressionind] = '%';
			expressionind++;

		}
   }
    else if(key=='.'){
	if(isAnsClicked){
			resetexpression();
			strcpy(expression,finalans);
			expressionind = finalanslen();
			expression[expressionind++] = '.';
		}
		else{
			expression[expressionind] = '.';
			expressionind++;

		}
   }
    else if(key=='='){
	  calculate();
	  isAnsClicked=true;
   }
    else if(key=='C'){
	if(expressionind>0)
	  expression[--expressionind] = '\0';
	  
   }
	}
}

void showexpression(){
	iSetColor(0,0,0);
	
	iText(81,384,expression,GLUT_BITMAP_TIMES_ROMAN_24);
}

void calculate(){
	
	int ind = 0,opind=0;
	char operand1[50];
	char operand2[50];
	char operation;
	int expsize = strlen(expression);
	int i=0;
	for(i=0;i<expsize;i++){
		if(expression[i]>='0' && expression[i]<='9' || expression[i]=='.'){
			operand1[opind++] = expression[i];
		}
		else if(expression[i]=='+' || expression[i]=='-' || expression[i]=='x' || expression[i]=='/' || expression[i]=='%' || expression[i]=='s' || expression[i]=='t' || expression[i]=='c' || (expression[i]=='s' && expression[i+1]=='q' ) || (expression[i]=='P') || expression[i]=='!' || (expression[i]=='^' && expression[i+1]=='-') ||expression[i]=='^'){
			if((expression[i]=='s' && expression[i+1]=='q') )
			operation= expression[i+1];
			else if( (expression[i]=='^' && expression[i+1]=='-')){
				operation ='I';
			}
			else
			operation= expression[i]; 
			break;
		}
	}
	opind=0;
	for(i;i<expsize;i++){
		if(expression[i]>='0' && expression[i]<='9' || expression[i]=='.'){
			operand2[opind++] = expression[i];
		}
	}
	int operationclicked=0;
	if(operationclicked==0){
	if(operation=='+'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(operand2);
	ans = a+b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='-'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(operand2);
	ans = a-b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='x'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(operand2);
	ans = a*b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='/'){
	float a,b,ans;  // ans==(int)ans   snprintf(finals size of "%d",as=ns) else 
	a=atof(operand1);
	b=atof(operand2);
	ans = a/b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='%'){
	 float a,b,ans;
	 a=atof(operand1);
	 b=atof(operand2);
	 operationclicked++;
	 if(a==(int)a && b== (int)b){
	 ans = (int)a%(int)b;
	 snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	else {
		strcpy(finalans,"ERROR!");
		
	}
  }
  if(operation=='s'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(operand2);
	c=(pi/180)*b;
	ans = sin(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='t'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(operand2);
	c=(pi/180)*b;
	ans = tan(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='c'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(operand2);
	c=(pi/180)*b;
	ans = cos(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='a'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(operand2);
	//c=(pi/180)*b;
	ans = acos(b)*180/pi;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='q'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(operand2);
	ans = sqrt(b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='P'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(operand2);
	ans = fact(a)/fact(a-b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='!'){
	float a,ans;
	a=atof(operand1);
	//b=atof(operand2);
	ans = fact(a);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='I'){
	float a,ans;
	a=atof(operand1);
	//b=atof(operand2);
	ans = 1/a;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='^'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(operand2);
	ans = pow(a,b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
 }
 else{
	if(operation=='+'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	ans = a+b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='-'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	ans = a-b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='x'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	ans = a*b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='/'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	ans = a/b;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='%'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	operationclicked++;
	 if(a==(int)a && b== (int)b){
	 ans = (int)a%(int)b;
	 snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	else {
		strcpy(finalans,"ERROR!");
		
	}
   }
   if(operation=='s'){
	float a,b,ans,c;
	a=atof(finalans);
	//b=atof(finalans);
	c=(pi/180)*a;
	ans = sin(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='t'){
	float a,b,ans,c;
	a=atof(finalans);
	//b=atof(finalans);
	c=(pi/180)*a;
	ans = tan(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='c'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(finalans);
	c=(pi/180)*b;
	ans = cos(c);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='a'){
	float a,b,ans;
	a=atof(operand1);
	b=atof(finalans);
	//c=(pi/180)*b;
	ans = acos(b)*180/pi;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='q'){
	float a,b,ans,c;
	a=atof(operand1);
	b=atof(finalans);
	ans = sqrt(b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='P'){
	float a,b,ans,c;
	a=atof(finalans);
	b=atof(operand2);
	ans = fact(a)/fact(a-b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='!'){
	float a,ans;
	a=atof(finalans);
	//b=atof(operand2);
	ans = fact(a);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='I'){
	float a,ans;
	a=atof(finalans);
	//b=atof(operand2);
	ans = 1/a;
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
	if(operation=='^'){
	float a,b,ans;
	a=atof(finalans);
	b=atof(operand2);
	ans = pow(a,b);
	operationclicked++;
	snprintf(finalans,sizeof(finalans),"%.2f",ans);
	}
 }
}
int finalanslen(){
	int len = 0;
	for(int i=0;i<200;i++){
		if(finalans[i]==0) break;
		len++;
	}
	return len;
}
void resetalldata(){
	resetexpression();
	memset(finalans,0,sizeof(finalans));
	expressionind=0;
	isAnsClicked = false;

}
int fact(int n){
	int res=1;
	for(int i=1;i<=n;i++){
       res*=i;
	}
	return res;
}
int main()
{
	// place your own initialization codes here.
	if(musicOn){
		PlaySound("sound\\bgmusic.wav", NULL, SND_ASYNC);
	}
	iInitialize(screenwidth, ScreenHeight, "Programming Calculator");
	return 0;
}
