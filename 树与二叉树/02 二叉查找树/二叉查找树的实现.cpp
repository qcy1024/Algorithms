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

//�ڸ�Ϊroot�Ķ�����������в���Ԫ��Ϊx�Ľڵ�
void BSTInsert(binTree*& root,elemType x)
{
    //root==NULL���ҵ��˲���λ��
    if( root == NULL )
    {
        root = new binTree(x);
        //cout << "���ڲ���" << x << endl;
        return ;
    }
    //���ڲ������ظ�Ԫ�ص�������x�Ѵ��ڣ�ֱ�ӷ��ء�
    if( root->data == x ) return ;
    //���������в���
    if( x < root->data )
        BSTInsert(root->lchild,x);
    //���������в���
    if( x > root->data )
        BSTInsert(root->rchild,x);
}

//�ɸ�����Ԫ������elems����һ�ö�������������������ڵ��ָ��
binTree* createBST(const std::vector<elemType>& elems)
{
    binTree* root = NULL;
    for( std::vector<elemType>::const_iterator it = elems.begin(); it != elems.end(); ++it )
    {
        BSTInsert(root,*it);
    }
    return root;
}

//�ڸ�Ϊroot�����в���ֵΪx�Ľڵ�
binTree* BSTFind( binTree* root,elemType x)
{
    if( root == NULL )
    {
        std::cout << "����" << std::endl;
        //throw
        return NULL;
    }
    //�ҵ���
    if( root->data == x )
        return root;
    //���������в���
    if( root->data < x )
        return BSTFind(root->rchild,x);
    //���������в���
    if( root->data > x )
        return BSTFind(root->lchild,x);

    //throw
    return NULL;
}

//��root��ɾ��ֵΪx�Ľڵ�
void BSTDelete(binTree*& root,elemType x)
{
    //
    if( root == NULL ) return ;
    //�ҵ���Ҫɾ���Ľڵ�
    if( root->data == x )
    {
        if( root->lchild == NULL && root->rchild == NULL )
        {
            //�ڵ�û�����Һ��ӣ�ֱ�ӽ��ýڵ�ָ���ÿգ��丸�ڵ���ָ������ڵ��lchild��rchild����Ӧ��ָ��NULL
            root = NULL;
            return ;
        }
        //��������ӣ�����ֱ��ǰ��������ֵ�����ݹ������������ɾ����ֱ��ǰ��
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

//�����������ÿһ���ڵ�ִ�к���ָ��pfunָ���Ĳ���
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


