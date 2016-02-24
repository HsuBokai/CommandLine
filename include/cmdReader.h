
#ifndef _CMD_READER_H_
#define _CMD_READER_H_

#define READ_BUF_SIZE    1024
#define TAB_POSITION     8
#define PG_OFFSET        10

typedef struct _CmdReader CmdReader;
CmdReader* new_CmdReader();
void delete_CmdReader(CmdReader* obj);

void readCmd(CmdReader* obj);

#endif
