/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:52:05 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<iostream>
#include"huffzip.h"

int compress(char *filename){
	unsigned short freq[TABLE_SIZE];
	struct huffcode codeTable[256];
	count_frequency(freq,filename);
	TREE_INIT(root);
	root = build_tree(freq);
//	for(int i=0;i<TABLE_SIZE;i++){
//		printf("freq[%d]=%u\n",i,freq[i]);
//	}
	create_code_table(codeTable,root);
//	for(int i=0;i<256;i++){
//		cout<<"codeTable["<<i<<"].code="<<codeTable[i].code<<" "<<"codeTable["<<i<<"].length="<<codeTable[i].length<<endl;
//	}
	write_outfile(filename,freq,codeTable,root);
	delete_tree(&root);
	return 0;
}
