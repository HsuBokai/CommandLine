#include <stdio.h>
#include <stdlib.h> // malloc

#include "charDef.h"
#include "cmdReader.h"

typedef char bool;

struct _CmdReader {
	char _readBuf[READ_BUF_SIZE];
	char* _readBufPtr;
	char* _readBufEnd;

	char* _history;
	int _historyIdx;

	bool _tempCmdStored;
};

CmdReader* new_CmdReader() {
	CmdReader* obj = (CmdReader*) malloc(sizeof(CmdReader));
	obj->_readBufEnd = obj->_readBufPtr = obj->_readBuf;
	*obj->_readBufPtr = 0;
	obj->_historyIdx = 0;
	obj->_tempCmdStored = 0;
	return obj;
}

void delete_CmdReader(CmdReader* obj) {
	free(obj);
	obj = NULL;
}

static void mybeep(){ printf("\a"); }

static bool moveBufPtr(CmdReader* obj, char* const ptr)
{
	if( !(ptr >= obj->_readBuf && ptr <= obj->_readBufEnd) ) { mybeep(); return 0; }
	for(char* i=ptr; i < obj->_readBufPtr; i++) printf("\b");
	for(char* i=ptr; i > obj->_readBufPtr; i--) printf("%c", obj->_readBufPtr[ptr-i]);
	obj->_readBufPtr = ptr;
	return 1;
}

static bool deleteChar(CmdReader* obj)
{
	char* end = obj->_readBufEnd;
	char* ptr = obj->_readBufPtr;
	if( !(ptr < end) ) { mybeep(); return 0;}
	for(char* i=ptr ; i < end-1 ; i++) {
		printf("%c", i[1]);
		i[0]=i[1];
	}
	printf(" ");
	for(int i=0; i < ( end - ptr ) ; i++) printf("\b");
	obj->_readBufEnd -= 1;
	obj->_readBufEnd[0] = 0;
	return 1;
}

static void insertChar(CmdReader* obj, char ch, int rep)
{
	char* end = obj->_readBufEnd;
	char* ptr = obj->_readBufPtr;
	for(char* p = end; p>=ptr; --p) p[rep] = *p;
	for(int i=0;i<rep;++i) ptr[i] = ch;
	char* ptr_temp;
	for(ptr_temp = ptr; ptr_temp<end; ++ptr_temp) printf("%c", *ptr_temp);
	for(int i=0;i<rep;++i) printf("%c",*(ptr_temp++));
	for(char* p = ptr; p<end; ++p) printf("\b");
	obj->_readBufPtr += rep;
	obj->_readBufEnd += rep;
}

/*
static void deleteLine(CmdReader* obj)
{
	moveBufPtr( obj, obj->_readBuf );
	for(int i=0; i< obj->_readBufEnd-obj->_readBuf ;i++) printf(" ");
	for(int i=0; i< obj->_readBufEnd-obj->_readBuf ;i++) printf("\b");
	obj->_readBufEnd = obj->_readBuf;
	*obj->_readBufPtr = 0;
}
*/

static void moveToHistory(CmdReader* obj, int index)
{
/*
//move up
	if(index < obj->_historyIdx) {
		if(obj->_historyIdx == 0 ) { mybeep(); return; }
		if(obj->_historyIdx == (int) obj->_history.size()) {
			_tempCmdStored = 1;
			obj->_history.push_back( obj->_readBuf );
		}
		if (index < 0) index = 0;
	}
//move down
	if(index > obj->_historyIdx){
		if(obj->_historyIdx == (int) obj->_history.size()) { mybeep(); return; }
		if( index >= (int)obj->_history.size() ) index = obj->_history.size() - 1;
	}
//show the history to the screen
	obj->_historyIdx = index;
	retrieveHistory();

//after showing, release the tempCmdStored if move down to the bottum 
	if( index == (int)obj->_history.size() -1 ) {
		obj->_history.pop_back();
		_tempCmdStored = 0;
	}
*/
}


static void addHistory(CmdReader* obj)
{
	/*
	if( _tempCmdStored == 1 ) obj->_history.pop_back();

//count first blank to know whether it's empity
	const char* key = " ";
	size_t firstblanknum = strspn( obj->_readBuf, key);

//if not empity, remove first and last blank and change to obj->_readBuf and push back to history
	if( (int)firstblanknum < (obj->_readBufEnd-obj->_readBuf) ){
		size_t lastnotblank = obj->_readBufEnd - obj->_readBuf;
		while(! ( obj->_readBuf[--lastnotblank] != ' ') );
		strncpy( obj->_readBuf , obj->_readBuf + firstblanknum , lastnotblank-firstblanknum+1 );
		obj->_readBuf[ lastnotblank-firstblanknum+1 ]=0;
		obj->_history.push_back( obj->_readBuf );
	}
//reset
	obj->_historyIdx = (int) obj->_history.size();
	_tempCmdStored = 0;
	*/
	obj->_readBufPtr = obj->_readBufEnd = obj->_readBuf;
	*obj->_readBufPtr = 0;
}

/*
static void retrieveHistory(CmdReader* obj)
{
   deleteLine();
   strcpy(obj->_readBuf, obj->_history[obj->_historyIdx].c_str());
   cout << obj->_readBuf;
   obj->_readBufPtr = obj->_readBufEnd = obj->_readBuf + obj->_history[obj->_historyIdx].size();
}
*/

static void printPrompt(){ printf(">> "); }

void readCmd(CmdReader* obj)
{
	printPrompt();
	while (1) {
		Key key = parseChar( mygetc() );
		if (key == INPUT_END_KEY) break;
		switch (key) {
			case LINE_BEGIN_KEY :
			case HOME_KEY       :	moveBufPtr(obj, obj->_readBuf); break;
			case LINE_END_KEY   :
			case END_KEY        : 	moveBufPtr(obj, obj->_readBufEnd); break;
			case BACK_SPACE_KEY : 	if(moveBufPtr(obj, obj->_readBufPtr-1)) deleteChar(obj); break;
			case DELETE_KEY     : 	deleteChar(obj); break;
			case NEWLINE_KEY    : 	addHistory(obj); printf("\n"); printPrompt(); break;
			case ARROW_UP_KEY   : 	moveToHistory(obj, obj->_historyIdx - 1); break;
			case ARROW_DOWN_KEY : 	moveToHistory(obj, obj->_historyIdx + 1); break;
			case ARROW_RIGHT_KEY: 	moveBufPtr(obj, obj->_readBufPtr+1); break;
			case ARROW_LEFT_KEY : 	moveBufPtr(obj, obj->_readBufPtr-1); break;
			case PG_UP_KEY      : 	moveToHistory(obj, obj->_historyIdx - PG_OFFSET); break;
			case PG_DOWN_KEY    : 	moveToHistory(obj, obj->_historyIdx + PG_OFFSET); break;
			case TAB_KEY        : 	insertChar(obj, ' ', TAB_POSITION - ((obj->_readBufPtr - obj->_readBuf) % TAB_POSITION) ); break;
			case INSERT_KEY     : 	// not yet supported; fall through to UNDEFINE
			case UNDEFINED_KEY  :	mybeep(); break;
			default		    :  	insertChar(obj, (char)key, 1); break;
		}
	}
}

