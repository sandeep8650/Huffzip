/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:54:48 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include"huffzip.h"

f_type write_outfile(char *filename,f_type *freq,struct huffcode *codeTable,struct node *root){
	f_type written_bytes=0;
	NODE_PTR(ptr);
	struct buffer buff={0,-1};
	unsigned b;
	char outfilename[100];
	strcpy(outfilename,filename);
	strcat(outfilename,".hzip");
	FILE *infile=fopen(filename,"rb");
	if(infile==NULL){return 0;}
	FILE *outfile=fopen(outfilename,"wb");
	if(outfile==NULL){ fclose(infile);return 0;}
	written_bytes=fwrite(freq,sizeof(f_type),TABLE_SIZE,outfile);
	if(written_bytes==0){
		fclose(outfile);
		fclose(infile);
		return 0;
	}
	while((b=fgetc(infile))!=EOF){
		for(int i=0;i<codeTable[b].length;i++){
			buff.byte[++buff.top]=codeTable[b].code[i];
			if(buff.top==7){
				fputc(buff.byte.to_ulong(),outfile);
				written_bytes++;
				buff.byte=0;
				buff.top=-1;
			}
		}
	}
	if(buff.top!=-1){
		written_bytes+=2;
		fputc(buff.byte.to_ulong(),outfile);
		fputc(buff.top + 1,outfile);
	}
	else{
		written_bytes++;
		fputc(8,outfile);
	}
	fclose(infile);
	fclose(outfile);
	return written_bytes;
}
