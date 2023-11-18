#include <iostream>
#include <vector>
#include <queue>

typedef int elemType;

//binary tree
struct binTree
{
    elemType data;
    binTree* lchild;
    binTree* rchild;
    binTree(elemType data):data(data),lchild(NULL),rchild(NULL) {};
};

//在根为root的二叉查找树树中插入元素为x的节点
void BSTInsert(binTree*& root,elemType x)
{
    //root==NULL即找到了插入位置
    if( root == NULL )
    {
        root = new binTree(x);
        //cout << "正在插入" << x << endl;
        return ;
    }
    //对于不允许重复元素的树，若x已存在，直接返回。
    if( root->data == x ) return ;
    //在左子树中插入
    if( x < root->data )
        BSTInsert(root->lchild,x);
    //在右子树中插入
    if( x > root->data )
        BSTInsert(root->rchild,x);
}

//由给定的元素序列elems创建一棵二叉查找树，返回树根节点的指针
binTree* createBST(const std::vector<elemType>& elems)
{
    binTree* root = NULL;
    for( std::vector<elemType>::const_iterator it = elems.begin(); it != elems.end(); ++it )
    {
        BSTInsert(root,*it);
    }
    return root;
}

//在根为root的树中查找值为x的节点
binTree* BSTFind( binTree* root,elemType x)
{
    if( root == NULL )
    {
        std::cout << "空树" << std::endl;
        //throw
        return NULL;
    }
    //找到了
    if( root->data == x )
        return root;
    //在右子树中查找
    if( root->data < x )
        return BSTFind(root->rchild,x);
    //在左子树中查找
    if( root->data > x )
        return BSTFind(root->lchild,x);

    //throw
    return NULL;
}

//在root中删除值为x的节点
void BSTDelete(binTree*& root,elemType x)
{
    //
    if( root == NULL ) return ;
    //找到了要删除的节点
    if( root->data == x )
    {
        if( root->lchild == NULL && root->rchild == NULL )
        {
            //节点没有左右孩子，直接将该节点指针置空，其父节点中指向这个节点的lchild或rchild会相应地指向NULL
            root = NULL;
            return ;
        }
        //如果有左孩子，令其直接前驱代替其值，并递归地在左子树中删除其直接前驱
        else if( root->lchild != NULL )
        {
            binTree* node = root->lchild;
            while( node->rchild )
                node = node->rchild;
            root->data = node->data;
            BSTDelete(root->lchild,node->data);
        }
        else if( root->rchild != NULL )
        {
            binTree* node = root->rchild;
            while( node->lchild )
                node = node->lchild;
            root->data = node->data;
            BSTDelete(root->rchild,node->data);
        }
    }
    else if( x < root->data ) BSTDelete(root->lchild,x);
    else if( x > root->data ) BSTDelete(root->rchild,x);
}

void fun(const binTree* root)
{
    std::cout << root->data << std::endl;
}

//层序遍历，对每一个节点执行函数指针pfun指定的操作
void layerOrderTravel(const binTree * root,void (*pfun) (const binTree* root) )
{
    if( root == NULL ) return ;
    std::queue<const binTree*> q;
    q.push(root);
    while(!q.empty())
    {
        const binTree* node = q.front();
        if( node->lchild != NULL ) q.push(node->lchild);
        if( node->rchild != NULL ) q.push(node->rchild);
        pfun(node);
        q.pop();
    }
    return ;
}


