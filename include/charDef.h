
#ifndef _CHAR_DEF_H_
#define _CHAR_DEF_H_

typedef enum
{
	LINE_BEGIN_KEY   = 1,
	LINE_END_KEY     = 5,
	INPUT_END_KEY    = 4,
	TAB_KEY          = (int)'\t',
	NEWLINE_KEY      = (int)'\n',
	ESC_KEY          = 27,

	BACK_SPACE_KEY   = 127,

	ARROW_KEY_FLAG   = 1 << 8,
	ARROW_KEY_INT    = 91,
	ARROW_UP_KEY     = 65 + ARROW_KEY_FLAG,
	ARROW_DOWN_KEY   = 66 + ARROW_KEY_FLAG,
	ARROW_RIGHT_KEY  = 67 + ARROW_KEY_FLAG,
	ARROW_LEFT_KEY   = 68 + ARROW_KEY_FLAG,
	ARROW_KEY_BEGIN  = ARROW_UP_KEY,
	ARROW_KEY_END    = ARROW_LEFT_KEY,

	MOD_KEY_FLAG     = 1 << 9,
	MOD_KEY_INT      = 91,
	HOME_KEY         = 49 + MOD_KEY_FLAG,
	INSERT_KEY       = 50 + MOD_KEY_FLAG,
	DELETE_KEY       = 51 + MOD_KEY_FLAG,
	END_KEY          = 52 + MOD_KEY_FLAG,
	PG_UP_KEY        = 53 + MOD_KEY_FLAG,
	PG_DOWN_KEY      = 54 + MOD_KEY_FLAG,
	MOD_KEY_BEGIN    = HOME_KEY,
	MOD_KEY_END      = PG_DOWN_KEY,
	MOD_KEY_DUMMY    = 126,

	UNDEFINED_KEY    = 99999999,

	KEY_END
} Key;

char mygetc();
Key parseChar(const char c);



#endif
