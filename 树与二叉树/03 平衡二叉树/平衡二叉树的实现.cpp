/*Author: chenyu qi*
*    ��ʵ�ֲ���          *
* 01   ����                 * 
* 02   ����                 *
* 03   ����                 *
* 04 ֧�ֺ���ָ��ָ   *
*  �������Ĳ������     */
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
    //Ҷ�ӽڵ�ĸ߶ȶ���Ϊ1��Ҷ�ӽڵ�ĺ��ӽڵ�(NULL)�߶�Ϊ0
    avlTree(elemType data) : data(data), height(1),lchild(NULL),rchild(NULL){};
};

//�������
void layerOrderTravel(const avlTree* const& root,void (*fun) (const avlTree* const &))
{
    if( root == NULL )
    {
        std::cout << "���ԶԿ������б���" << std::endl;
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

//������������������������
void preOrderTravel(const avlTree* const& root,void (*fun) (const avlTree* const &))
{
    if( root == NULL ) return ;
    preOrderTravel(root->lchild,fun);
    std::cout << root->data << std::endl;
    preOrderTravel(root->rchild,fun);
}

//�����һ��const��ʾavlTreeָ��Ķ�����const�ģ��ڶ���const��ʾavlTree��const�ġ�
//���÷���&��ʾroot��һ���� const avlTree* const ���͵Ķ�������á�
int getHeight(const avlTree* const& root)
{
    if( root == NULL ) return 0;
    return root->height;
}

int getBalance(const avlTree* const& root)
{
    if( root == NULL ) return 0;
    //ע������ʹ��getHeight��ȡ�߶Ⱥ���Ҫ��������ֱ����ָ�룺root->lchild->height�Լ�root->rchild->height
    //��Ϊroot�����Ӻ��к����п���ΪNULL��ֱ�ӻ�ȡָ�����׵��³��������
    return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(avlTree* const root)
{
    if( root == NULL )
    {
        //throw
        std::cout << "updateHeight�г��ԶԿ������¸߶�" << std::endl;
        return ;
    }
    root->height = std::max( getHeight(root->lchild),getHeight(root->rchild) ) + 1;
}

//����rootΪ����������������
void lRotate(avlTree*& root)
{
    avlTree* node = root->rchild;
    root->rchild = node->lchild;
    node->lchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//����
void rRotate(avlTree*& root)
{
    avlTree* node = root->lchild;
    root->lchild = node->rchild;
    node->rchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//����
void avlTreeInsert(avlTree*& root,elemType x)
{
    //�����������ƽ��������Ĳ���λ��һ����Ҷ�ӽڵ�ĺ���(NULL)
    if( root == NULL )
    {
        avlTree* newNode = new avlTree(x);
        root = newNode;
        return ;
    }
    if( x == root->data )
    {
        std::cout << "Ԫ��" << x << "�Ѿ�����" << std::endl;
        return ;
    }
    if( x < root->data )
    {
        avlTreeInsert(root->lchild,x);
        updateHeight(root);
        //��root���������в��룬�����²�ƽ�⣬root��ƽ������һ����2
        if( getBalance(root) == 2 )
        {
            //LL�ͣ���root����
            if( getBalance(root->lchild) == 1 )
            {
                rRotate(root);
            }
            //LR�ͣ��ȶ�root���������������ٶ�root����
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
        //��root���������в��룬�����²�ƽ�⣬root��ƽ������һ����-2
        if( getBalance(root) == -2 )
        {
            //RL�ͣ��ȶ�root���������������ٶ�root����
            if( getBalance(root->rchild) == 1 )
            {
                rRotate(root->rchild);
                lRotate(root);
            }
            //RR�ͣ�ֱ�Ӷ�root����
            if( getBalance(root->rchild) == -1 )
            {
                lRotate(root);
            }
        }
    }

}

//����
avlTree* createAVLTree(const std::vector<elemType>& elems)
{
    avlTree* root = NULL;
    for( int i=0; i<elems.size(); i++ )
    {
        avlTreeInsert(root,elems[i]);
    }
    return root;
}

//����
avlTree* avlTreeFind(avlTree* const& root,elemType x)
{
    if( root == NULL )
    {
        std::cout << "�Կ������в���" << std::endl;
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

