#include<cstdio>
#include<cstring>
#include"huffzip.h"

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("Invalid Arguments\n");
		return 0;
	}
	if(strcmp(argv[1],"-c")==0){
		compress(argv[2]);
	}
	else if(strcmp(argv[1],"-d")==0){
		decompress(argv[2]);
	}
	else{
		printf("Invalid arguments\n");
	}
	
	return 0;
}
