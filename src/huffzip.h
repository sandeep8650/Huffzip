/*******************************************
 * @author: Sandeep Singh
 * @date: Fri 29/Apr/2016 05:00:00 PM IST
 *
 *******************************************
 */
#include<bitset>

using namespace std;

/* size of frequency table */
#define TABLE_SIZE 256 //2^8

/* @f_type: data type of frequency table array
 */
typedef unsigned int f_type;

/* structure of node for huffman tree
 */
struct node{
	unsigned byte;
	f_type freq;
	struct node *left;
	struct node *right;
};

/* custom compare functor for priority queue
 */
struct compare{
  bool operator()(struct node *lhs, struct node *rhs) {
    return lhs->freq > rhs->freq;
  }
};

/* structure for huffman code of character
 */
struct huffcode{
	bitset<TABLE_SIZE> code;
	int length;
};

/* size of buffer of bitset */
#define BUFF_SIZE 8

/* structure for buffer of bits
 */
struct buffer{
	bitset<BUFF_SIZE> byte;
	int top;
};

/*extension name*/
const string extension=".hzip";

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

/* macro for progress bar
 * @i: completed
 * @n: total
 */
#define BAR_SIZE 50
#define PROGRESS(i,n) printf("["); \
						for(f_type j=0;j<i*BAR_SIZE/n;j++){printf("#");} \
						for(f_type j=i*BAR_SIZE/n;j<BAR_SIZE;j++){printf("_");} \
						printf("]"); \
						printf("\r")
	
/* prototype of all functions used */
float compress(char *filename);
int decompress(char *filename);
f_type write_outfile(char *filename,f_type *freq,struct huffcode *codeTable,struct node *root, f_type total_bytes);
void create_code_table(struct huffcode *codeTable,struct node *root);
void write_code_table(struct huffcode *codeTable,struct node *ptr,bitset<TABLE_SIZE> *c,int l);
f_type count_frequency(f_type *freq, const char *filename);
struct node* build_tree(f_type *freq);
void delete_tree(struct node **ptr);
int print_tree_preorder(struct node *ptr);

