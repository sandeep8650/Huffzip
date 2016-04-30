/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:52:46 PM IST
 *
 *******************************************
 */
#include<cstdio>
#include<cstring>
#include<cerrno>
#include<string>
#include"huffzip.h"

int decompress(char *filename){
	int lastlen=0;
	string::size_type pos;
	long size,cur_pos;
	f_type freq[TABLE_SIZE]={0};
	struct buffer buff={0,7};
	TREE_INIT(root);
	NODE_PTR(ptr);
	string outfilename=string(filename);
	if((pos=outfilename.rfind(extension))!=string::npos){
		outfilename.erase(pos);
	}
	else{
		printf("Unknown file type\n");
		return 0;
	}
	FILE *infile=fopen(filename,"rb");
	if(!infile){
		printf("Source file opening error: %s\n",strerror(errno));
		return 0;
	}
	FILE *outfile=fopen(outfilename.c_str(),"wbx");
	for(int i=1;i<=5 && !outfile;i++){
		if((pos=outfilename.find_first_of('.'))==string::npos){
			outfilename.append(1,'1');
		}
		else{
			outfilename.insert(outfilename.begin()+pos,'1');
		}
		outfile=fopen(outfilename.c_str(),"wbx");
	}
	if(!outfile){
		fclose(infile);
		printf("Destination file opening error: %s\n",strerror(errno));
		return 0;
	}
	fread(freq,sizeof(f_type),TABLE_SIZE,infile);
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
	return 1;
}
