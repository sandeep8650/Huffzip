/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:52:46 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include"huffzip.h"

int decompress(char *filename){
	int lastlen=0;
	unsigned b,c;
	long size,cur_pos;
	struct buffer buff={0,7};
	TREE_INIT(root);
	NODE_PTR(ptr);
	string outfilename=string(filename)+"d";
	unsigned short freq[TABLE_SIZE]={0};
	FILE *infile=fopen(filename,"rb");
	if(infile==NULL){return 0;}
	FILE *outfile=fopen(outfilename.c_str(),"wb");
	if(outfile==NULL){fclose(infile);return 1;}
	fread(freq,sizeof(unsigned short),TABLE_SIZE,infile);
//	for(int i=0;i<TABLE_SIZE;i++){
//		printf("freq[%d]=%u\n",i,freq[i]);
//	}
	root=build_tree(freq);
	ptr=root;
	cur_pos=ftell(infile);
	fseek(infile,-1,SEEK_END);
	lastlen=fgetc(infile);
//	printf("lastlen=%d\n",lastlen);
	fseek(infile,0L,SEEK_END);
	size=ftell(infile);
	fseek(infile,cur_pos,SEEK_SET);
	while(ftell(infile)!=size-1){
		while(ptr->left!=NULL && ptr->right!=NULL && buff.top!=7){
			buff.top++;
			if(buff.byte[buff.top]==0){
				ptr=ptr->left;
			}
			else{
				ptr=ptr->right;
			}
		}
		if(ptr->left==NULL || ptr->right==NULL){
			fputc(ptr->byte,outfile);
			ptr=root;
		}
		if(buff.top==7){
			buff.byte=fgetc(infile);
			buff.top=-1;
		}
	}
	lastlen=fgetc(infile);
	while(buff.top!=lastlen-1){	
		while(ptr->left!=NULL && ptr->right!=NULL){
			buff.top++;
			if(buff.byte[buff.top]==0){
				ptr=ptr->left;
			}
			else{
				ptr=ptr->right;
			}
		}
		if(ptr->left==NULL || ptr->right==NULL){
			fputc(ptr->byte,outfile);
			ptr=root;
		}
	}
	fclose(outfile);
	fclose(infile);
	delete_tree(&root);
	return 0;
}
