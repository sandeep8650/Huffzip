/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:56:38 PM IST
 *
 *******************************************
 */
#include<cstdlib>
#include"huffzip.h"

void delete_tree(struct node **ptr){
	if(*ptr!=NULL){
		delete_tree( &((*ptr)->left) );
		delete_tree( &((*ptr)->right) );
		//printf("freq=%d\n",(*ptr)->freq);
		free(*ptr);
		*ptr=NULL;
	}
}
