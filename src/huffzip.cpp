#include<cstdio>
#include<cstring>
#include<ctime>
#include"huffzip.h"

int main(int argc, char *argv[]){
	float compression_ratio;
	int status;
	clock_t t1,t2;
	double time;
	if(argc!=3){
		fprintf(stderr,"USE: huffzip [option] [file]\nOption:\n-c to compress\n-d to decompress\n");
		return 0;
	}
	if(strcmp(argv[1],"-c")==0){
		t1=clock();
		compression_ratio=compress(argv[2]);
		t2=clock();
		time=(double)(t2-t1)/CLOCKS_PER_SEC;
		if(compression_ratio!=0){
			printf("Compression ratio: %.2f%%\n",compression_ratio*100);
			printf("Compression time: %.2lf sec\n",time);
		}
	}
	else if(strcmp(argv[1],"-d")==0){
		t1=clock();
		status=decompress(argv[2]);
		t2=clock();
		if(status){
			time=(double)(t2-t1)/CLOCKS_PER_SEC;
			printf("Decompression time: %.2lf sec\n",time);
		}
	}
	else{
		fprintf(stderr,"Invalid arguments\n");
		fprintf(stderr,"USE: huffzip [option] [file]\nOption:\n-c to compress\n-d to decompress\n");
	}
	
	return 0;
}
