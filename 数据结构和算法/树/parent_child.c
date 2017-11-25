#define MAX_TREE_SIZE 100
typedef char ElemType;


//孩子结点
typedef struct CTNode
{
    int child;//孩子结点的下标
    struct CTNode *next; //指向下一个孩子结点的指针
}*ChilePtr;

//表头结构
typedef struct
{
    ElemType data;
    int parent;
    ChildPtr firstchild;
}CTBox;

//树结构
typedef struct
{
    CTBox nodes[MAX_TREE_SIZE];//结点数组
	int r,n;
}
