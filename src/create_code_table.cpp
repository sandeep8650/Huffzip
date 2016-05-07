/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:56:06 PM IST
 *
 *******************************************
 */
#include<cstring>
#include"huffzip.h"

/* function to fill codeTable
 * @codeTable:
 * @root: root pointer of huffman tree
 */
void create_code_table(struct huffcode *codeTable,struct node *root){
	bitset<TABLE_SIZE> c(0);
	memset(codeTable,0,sizeof(struct huffcode)*TABLE_SIZE);
	write_code_table(codeTable,root,&c,0);
}

void write_code_table(struct huffcode *codeTable,struct node *ptr,bitset<TABLE_SIZE> *c,int l){
	if(ptr!=NULL){
		if(ptr->left==NULL && ptr->right==NULL){
			codeTable[ptr->byte].code = *c;
			codeTable[ptr->byte].length=l;
		}
		write_code_table(codeTable,ptr->left,c,l+1);
		(*c).set(l);//set bit number 'l' of c
		write_code_table(codeTable,ptr->right,c,l+1);
		(*c).reset(l); //reset bit number 'l' of c
	}
}
