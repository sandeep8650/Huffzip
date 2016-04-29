/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 04:57:07 PM IST
 *
 *******************************************
 */
#include<cstdlib>
#include<queue>
#include"huffzip.h"

struct node* build_tree(unsigned short *freq){
	priority_queue<struct node*, vector<struct node*>, compare> pq;
	int qsize;
	NODE_PTR(newnode);
	NODE_PTR(x);
	NODE_PTR(y);
	for(int i=0;i<TABLE_SIZE;i++){
		if(freq[i]){
			NEW_NODE(newnode);
			NODE_INIT(newnode,i,freq[i],NULL,NULL);
			pq.push(newnode);
		}
	}
	qsize=pq.size();
	for(int i=0;i<qsize-1;i++){
		NEW_NODE(newnode);
		x=pq.top();pq.pop();
		y=pq.top();pq.pop();
		NODE_INIT(newnode,0,x->freq + y->freq,x,y);
		pq.push(newnode);
	}
	x=pq.top();pq.pop();
	return x;
}