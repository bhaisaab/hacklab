#include < stdio.h >
#include < stdlib.h >

enum yCOLOR = {BLACK=0,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE,RESET};
	
	//0=BLACK 1=RED 2=GREEN 3=YELLOW 4=BLUE 5=MAGENTA 6=CYAN 7=WHITE
	//30+ 90+(LIGHT)  -> FOREGROUND
	//40+ 100+(LIGHT) -> BACKGROUND
	//1 = BOLD; 0 = Normal; 4 = Underline; 5 = Blink ON  
	

int yPrintf( const char * , int , int , int , int );
int yReset();
int yClearScreen();
int yGotoXY( int, int );
int ySetCursor();
int yClearLine();
int yColorPrintf();
int yRevertVideo();
int yTab(int);

int yTab( int tab )
{	
	while(tab--)
		printf("\t");
	return 0;
}

int yRevertVideo()
{
	printf("\e[7m]");
	return 0;
}

// *** yColorPrintf ***
int yColorPrintf( const char *s , int fgrnd, int bgrnd, int bold , int underl, int blink)
{
	
	printf("\x1B[%d;%d;%d;%dm", bold, underl, blink fgrnd ,bgrnd);
	printf(s);
	yReset();
	return 0;
}

// *** yClearLine ***
int yClearLine()
{
	//CAN USE \x1B or \e both are the sam efor ESC 
	printf("\x1B[K");
	return 0;
}

// *** ySetCursor ***
int ySetCursor( int up, int down, int forward, int back )
{
	printf("\x1B[%dA", up);
	printf("\x1B[%dB", down);
	printf("\x1B[%dC", forward);
	printf("\x1B[%dD", back);
	return 0;
}

// *** yGotoXY ***
int yGotoXY( int line, int column )
{
	printf("\x1B[%d;%dH", line, column);	//line = Y, Column = X 
	return 0;
}

// *** yClearScreen ***
int yClearScreen()
{
	printf("\x1B[2J");			//ESC[2J   Clear screen and home cursor
	printf("\x1B[u");			//ESC[u    Return to saved cursor position
	printf("\x1B[0;0H");		//ESC[#;#H Moves cusor to line #, column #
	return 0;
}

// *** yReset ***
int yReset()
{
	printf("\x1B[00m");
	return 0;
}

// *** yPrintf ***
int yPrintf( const char *s , int foreground, int background, int tab, int nl)
{
	while(nl)
	{ printf("\n"); nl--; }
	while(tab)
	{ printf("\t"); tab--; }
	printf("\x1B[%d;%dm",foreground ,background);
	printf(s);
	yReset();
	return 0;
}
