#include<stdio.h>
#include<stdlib.h> // exit

#include "cmdReader.h"

static char * exec_file;
static void usage(){
	printf("Usage: %s [ -file < doFile > ]\n", exec_file);
}

static void my_exit(){ 
	usage();
	exit(-1); 
}

int main(int argc, char** argv){
	exec_file = argv[0];

	if(argc == 3) {
		usage();
	}
	if(argc != 1){
		fprintf(stderr, "Error: argc != 1\n");
		my_exit();
	}
	
	CmdReader* cr = new_CmdReader();
	readCmd(cr);
	delete_CmdReader(cr);
}
