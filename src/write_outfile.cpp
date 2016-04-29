/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:54:48 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include"huffzip.h"

int write_outfile(char *filename,unsigned short *freq,struct huffcode *codeTable,struct node *root){
	size_t written;
	NODE_PTR(ptr);
	struct buffer buff={0,-1};
	unsigned b;
	char outfilename[100];
	strcpy(outfilename,filename);
	strcat(outfilename,".hzip");
	FILE *infile=fopen(filename,"rb");
	if(infile==NULL){return 0;}
	FILE *outfile=fopen(outfilename,"wb");
	if(outfile==NULL){ fclose(infile);return 1;}
	written=fwrite(freq,sizeof(unsigned short),TABLE_SIZE,outfile);
	if(written==0){
		fclose(outfile);
		fclose(infile);
		return 3;
	}
	while((b=fgetc(infile))!=EOF){
		for(int i=0;i<codeTable[b].length;i++){
			buff.byte[++buff.top]=codeTable[b].code[i];
			if(buff.top==7){
				fputc(buff.byte.to_ulong(),outfile);
				buff.byte=0;
				buff.top=-1;
			}
		}
	}
	if(buff.top!=-1){
		fputc(buff.byte.to_ulong(),outfile);
		fputc(buff.top + 1,outfile);
	}
	else{
		fputc(8,outfile);
	}
	fclose(infile);
	fclose(outfile);
	return 0;
}
