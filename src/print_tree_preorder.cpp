/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:53:38 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include"huffzip.h"

/* function to print huffman tree in preorder
 * @ptr: pointer to root of huffman tree
 */
int print_tree_preorder(struct node *ptr){
	if(ptr!=NULL){
		printf("%d\n",ptr->freq);
		print_tree_preorder(ptr->left);
		print_tree_preorder(ptr->right);
	}
	return 0;
}
