/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 05:00:00 PM IST
 *
 *******************************************
 */
#include<bitset>

using namespace std;

#define TABLE_SIZE 256

struct node{
	unsigned byte;
	unsigned short freq;
	struct node *left;
	struct node *right;
};
struct compare{
  bool operator()(struct node *lhs, struct node *rhs) {
    return lhs->freq > rhs->freq; //calls your operator
  }
};

struct huffcode{
	bitset<TABLE_SIZE> code;
	int length;
};

struct buffer{
	bitset<8> byte;
	int top;
};

/* macro to initialise empty huffman tree
 * @name: name of tree
 */
#define TREE_INIT(name) \
	struct node *name = NULL

/* macro to declare node
 * @name: name of node
 */
#define NODE_PTR(name) \
	struct node *name = NULL

/* macro to allocate memory for node
 * @name: name of node
 */
#define NEW_NODE(ptr_name) \
	ptr_name= /*new struct node*/ (struct node*)malloc(sizeof(struct node))

/* macro to initialise tree node
 * @name: name of node
 */
#define NODE_INIT(name,b,f,l,r) \
	name->byte=b;name->freq=f;name->left=l;name->right=r
	
int compress(char *filename);
int decompress(char *filename);
int print_tree_preorder(struct node *ptr);
int write_outfile(char *filename,unsigned short *freq,struct huffcode *codeTable,struct node *root);
void create_code_table(struct huffcode *codeTable,struct node *root);
void write_code_table(struct huffcode *codeTable,struct node *ptr,bitset<TABLE_SIZE> *c,int l);
int count_frequency(unsigned short *freq, const char *filename);
struct node* build_tree(unsigned short *freq);
void delete_tree(struct node **ptr);


