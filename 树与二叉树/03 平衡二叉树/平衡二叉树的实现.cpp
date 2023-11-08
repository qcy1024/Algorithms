/*Author: chenyu qi*
*    已实现操作          *
* 01   查找                 * 
* 02   建树                 *
* 03   插入                 *
* 04 支持函数指针指   *
*  定操作的层序遍历     */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef int elemType;

struct avlTree
{
    elemType data;
    int height;
    avlTree* lchild;
    avlTree* rchild;
    //叶子节点的高度定义为1，叶子节点的孩子节点(NULL)高度为0
    avlTree(elemType data) : data(data), height(1),lchild(NULL),rchild(NULL){};
};

//层序遍历
void layerOrderTravel(const avlTree* const& root,void (*fun) (const avlTree* const &))
{
    if( root == NULL )
    {
        std::cout << "尝试对空树进行遍历" << std::endl;
        return ;
    }
    std::queue<const avlTree*> q;
    q.push(root);
    while( !q.empty() )
    {
        const avlTree* node = q.front();
        if( node->lchild != NULL ) q.push(node->lchild);
        if( node->rchild != NULL ) q.push(node->rchild);
        //std::cout << node->data << std::endl;
        fun(node);
        q.pop();
    }
}

//先序遍历，遍历序列是有序的
void preOrderTravel(const avlTree* const& root,void (*fun) (const avlTree* const &))
{
    if( root == NULL ) return ;
    preOrderTravel(root->lchild,fun);
    std::cout << root->data << std::endl;
    preOrderTravel(root->rchild,fun);
}

//这里第一个const表示avlTree指向的对象是const的，第二个const表示avlTree是const的。
//引用符号&表示root是一个对 const avlTree* const 类型的对象的引用。
int getHeight(const avlTree* const& root)
{
    if( root == NULL ) return 0;
    return root->height;
}

int getBalance(const avlTree* const& root)
{
    if( root == NULL ) return 0;
    //注意这里使用getHeight获取高度很重要，而不能直接用指针：root->lchild->height以及root->rchild->height
    //因为root的左孩子和有孩子有可能为NULL，直接获取指针容易导致程序崩溃。
    return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(avlTree* const root)
{
    if( root == NULL )
    {
        //throw
        std::cout << "updateHeight中尝试对空树更新高度" << std::endl;
        return ;
    }
    root->height = std::max( getHeight(root->lchild),getHeight(root->rchild) ) + 1;
}

//对以root为根的子树进行左旋
void lRotate(avlTree*& root)
{
    avlTree* node = root->rchild;
    root->rchild = node->lchild;
    node->lchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//右旋
void rRotate(avlTree*& root)
{
    avlTree* node = root->lchild;
    root->lchild = node->rchild;
    node->rchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//插入
void avlTreeInsert(avlTree*& root,elemType x)
{
    //二叉查找树和平衡二叉树的插入位置一定是叶子节点的孩子(NULL)
    if( root == NULL )
    {
        avlTree* newNode = new avlTree(x);
        root = newNode;
        return ;
    }
    if( x == root->data )
    {
        std::cout << "元素" << x << "已经存在" << std::endl;
        return ;
    }
    if( x < root->data )
    {
        avlTreeInsert(root->lchild,x);
        updateHeight(root);
        //在root的左子树中插入，若导致不平衡，root的平衡因子一定是2
        if( getBalance(root) == 2 )
        {
            //LL型，对root右旋
            if( getBalance(root->lchild) == 1 )
            {
                rRotate(root);
            }
            //LR型，先对root的左子树左旋，再对root右旋
            else if( getBalance(root->lchild) == -1 )
            {
                lRotate(root->lchild);
                rRotate(root);
            }
        }
    }
    else if( x > root->data )
    {
        avlTreeInsert(root->rchild,x);
        updateHeight(root);
        //在root的右子树中插入，若导致不平衡，root的平衡因子一定是-2
        if( getBalance(root) == -2 )
        {
            //RL型，先对root的右子树右旋，再对root左旋
            if( getBalance(root->rchild) == 1 )
            {
                rRotate(root->rchild);
                lRotate(root);
            }
            //RR型，直接对root左旋
            if( getBalance(root->rchild) == -1 )
            {
                lRotate(root);
            }
        }
    }

}

//建立
avlTree* createAVLTree(const std::vector<elemType>& elems)
{
    avlTree* root = NULL;
    for( int i=0; i<elems.size(); i++ )
    {
        avlTreeInsert(root,elems[i]);
    }
    return root;
}

//查找
avlTree* avlTreeFind(avlTree* const& root,elemType x)
{
    if( root == NULL )
    {
        std::cout << "对空树进行查找" << std::endl;
        return NULL;
    }
    if( root->data == x )
    {
        return root;
    }
    if( x < root->data )
    {
        avlTreeFind(root->lchild,x);
    }
    if( x > root->data )
    {
        avlTreeFind(root->rchild,x);
    }
    return NULL;
}

void printAVLTree(const avlTree* const & root)
{
    std::cout << root->data << std::endl;
}

