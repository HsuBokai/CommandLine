#include <stdio.h> // getchar
#include <termios.h> // termios

#include "charDef.h"

static int file_des = 0;
static struct termios stored_settings;

static void reset_keypress(void)
{
	tcsetattr(file_des, TCSANOW, &stored_settings);
}

static void set_keypress(void)
{
	struct termios new_settings;
	tcgetattr(file_des, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_lflag &= (~ECHO);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(file_des, &stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(file_des, TCSANOW, &new_settings);
}

char mygetc()
{
	char ch;
	set_keypress();
	//istr.unsetf(ios_base::skipws);
	ch = getc(stdin);
	//istr.setf(ios_base::skipws);
	reset_keypress();
	//#ifdef TEST_ASC
	//cout << left << setw(6) << int(ch);
	//#endif // TEST_ASC
	return ch;
}

Key parseChar(const char c){
	char c2;
	if(c==EOF) return INPUT_END_KEY;
	switch(c){
		case ESC_KEY:
			c2 = mygetc();
			if(c2 == ARROW_KEY_INT) return (mygetc() + ARROW_KEY_FLAG);
			else if(c2 == MOD_KEY_INT) return (mygetc() + MOD_KEY_FLAG);
			else return INPUT_END_KEY;
	}
	return (int)c;
}
