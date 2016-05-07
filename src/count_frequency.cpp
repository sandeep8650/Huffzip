/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:57:44 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include<cerrno>
#include"huffzip.h"

/* function for counting frequency of characters in a file.
 * @return: 0 if fail to open file else total number of bytes in file
 * @freq: (frequency table) array of type f_type of size of TABLE_SIZE i.e 256
 * @filename: name of file in which characters to be count
 */
f_type count_frequency(f_type *freq, const char *filename){
	f_type total_bytes=0;
	FILE *infile = fopen(filename,"rb");
	if(!infile){
		fprintf(stderr,"Source file opening error: %s\n",strerror(errno));
		return 0;
	}
	memset(freq,0,sizeof(f_type)*TABLE_SIZE);//initialise frequency table with 0 entries
	unsigned byte;
	while( (byte=fgetc(infile))!=EOF ){
		freq[byte]++;
		total_bytes++;
	}
	fclose(infile);
	infile=NULL;
	return total_bytes;
}
