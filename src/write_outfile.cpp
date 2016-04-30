/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:54:48 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include<cerrno>
#include<string>
#include"huffzip.h"

f_type write_outfile(char *filename,f_type *freq,struct huffcode *codeTable,struct node *root){
	f_type written_bytes=0;
	NODE_PTR(ptr);
	struct buffer buff={0,-1};
	unsigned b;
	string outfilename=string(filename) + extension;
	FILE *infile=fopen(filename,"rb");
	if(!infile){
		printf("Source file opening error: %s\n",strerror(errno));
		return 0;
	}
	FILE *outfile=fopen(outfilename.c_str(),"wbx");
	for(int i=1;i<=5 && !outfile;i++){
		outfilename.insert(outfilename.begin()+outfilename.find_last_of('.'),'1');
		outfile=fopen(outfilename.c_str(),"wbx");
	}
	if(!outfile){
		fclose(infile);
		printf("Destination file opening error: %s\n",strerror(errno));
		return 0;
	}
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
