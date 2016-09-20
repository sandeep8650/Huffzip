/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:52:05 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include"huffzip.h"

/* function to compress file
 * @filename: name of file to be compress
 * @return: compression ratio
 */
float compress(char *filename){
	f_type freq[TABLE_SIZE];
	f_type total_bytes,written_bytes;
	float com_ratio;
	struct huffcode codeTable[TABLE_SIZE]; //it will store huffman code for each character(byte)
	total_bytes=count_frequency(freq,filename);//total number of bytes in input file
	if(!total_bytes){return 0;}
	TREE_INIT(root);//initialise empty huffman tree
	root = build_tree(freq);
//	for(int i=0;i<TABLE_SIZE;i++){
//		printf("freq[%d]=%u\n",i,freq[i]);
//	}
	create_code_table(codeTable,root);
//	for(int i=0;i<256;i++){
//		cout<<"codeTable["<<i<<"].code="<<codeTable[i].code<<" "<<"codeTable["<<i<<"].length="<<codeTable[i].length<<endl;
//	}
	written_bytes=write_outfile(filename,freq,codeTable,root,total_bytes);//total number of written bytes on compressed file
	if(!written_bytes){delete_tree(&root);return 0;}//if written_bytes=0 then delete tree and return 0
	delete_tree(&root);
	return (float)(total_bytes-written_bytes)/total_bytes;
}
