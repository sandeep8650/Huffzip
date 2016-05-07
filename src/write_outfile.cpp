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

/* function to write compressed file
 * @return: total number of written bytes to compressed file i.e. size of compressed file
 */
f_type write_outfile(char *filename,f_type *freq,struct huffcode *codeTable,struct node *root, f_type total_bytes){
	f_type written_bytes=0,read_bytes=0;
	NODE_PTR(ptr);
	struct buffer buff={0,-1};
	unsigned b;
	string outfilename=string(filename) + extension;
	FILE *infile=fopen(filename,"rb");
	if(!infile){
		fprintf(stderr,"Source file opening error: %s\n",strerror(errno));
		return 0;
	}
	FILE *outfile=fopen(outfilename.c_str(),"wbx");
	for(int i=1;i<=5 && !outfile;i++){
		outfilename.insert(outfilename.begin()+outfilename.find_last_of('.'),'1');
		outfile=fopen(outfilename.c_str(),"wbx");
	}
	if(!outfile){
		fclose(infile);
		fprintf(stderr,"Destination file opening error: %s\n",strerror(errno));
		return 0;
	}
	written_bytes=fwrite(freq,sizeof(f_type),TABLE_SIZE,outfile);
	if(written_bytes==0){
		fclose(outfile);
		fclose(infile);
		return 0;
	}
	while((b=fgetc(infile))!=EOF){
		read_bytes++;
		for(int i=0;i<codeTable[b].length;i++){
			buff.byte[++buff.top]=codeTable[b].code[i];
			if(buff.top==7){//buffer is full, so write it to file
				fputc(buff.byte.to_ulong(),outfile);
				written_bytes++;
				buff.byte=0;
				buff.top=-1;
			}
		}
		PROGRESS(read_bytes,total_bytes);
	}
	printf("\n");
	if(buff.top!=-1){
		written_bytes+=2;
		fputc(buff.byte.to_ulong(),outfile);
		fputc(buff.top + 1,outfile);//this is length of code in last byte
	}
	else{
		written_bytes++;
		fputc(8,outfile);//length of code in last byte is 8
	}
	fclose(infile);
	fclose(outfile);
	return written_bytes;
}
