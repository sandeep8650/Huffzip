/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:57:44 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include"huffzip.h"

/* function for counting frequency of characters
 * in file filename.
 * @return: 0 if fail to open file "filename" else 1
 * @freq: array of type unsigned of size 256
 * @filename: char* to name of file in which characters to be count
 */
int count_frequency(unsigned short *freq, const char *filename){
	FILE *infile = fopen(filename,"rb");
	if(!infile){ return 0;}
	memset(freq,0,sizeof(unsigned short)*TABLE_SIZE);
	unsigned byte;
	while( (byte=fgetc(infile))!=EOF ){
		freq[byte]++;
	}
	fclose(infile);
	infile=NULL;
	return 1;
}
