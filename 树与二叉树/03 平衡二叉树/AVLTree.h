/*                         ƽ�������ģ��                                     *
*                        Author: chenyu qi                                    *
*                           ��ʵ�ֽӿ�                                        *
* 1.����һ�ÿ���: avlTreeNode<elemType> root = NULL;                          *
* 2.����root�в���x: avlTreeInsert(root,x);                                   *
* 3.����root�в���x: avlTreeFind(root,x);                                     *
* 4.�������root����ÿ���ڵ�ִ��ָ������fun: layerOrderTravel(root,fun);      *
* 5.������rootΪ�������ĸ߶�: getHeight(root)                                 */

/*                  �÷�ʾ��
int main()
{
    std::vector<int>  elems = {7,5,6,8,9,13,10,2};
    avlTreeNode<int> root = createAVLTree(elems);
	layerOrderTravel(root,printAVLTree);
}                                                   */

#ifndef __AVLTREE__H
#define __AVLTREE__H

#include <iostream>
#include <queue>
#include <algorithm>

template <typename elemType> struct _avlTreeNode
{
    elemType data;
    int height;
    _avlTreeNode<elemType>* lchild;
    _avlTreeNode<elemType>* rchild;
    //Ҷ�ӽڵ�ĸ߶ȶ���Ϊ1��Ҷ�ӽڵ�ĺ��ӽڵ�(nullptr)�߶�Ϊ0
    _avlTreeNode<elemType>() = delete;
    _avlTreeNode<elemType>(elemType data) : data(data), height(1), lchild(nullptr), rchild(nullptr) {};
};

template <typename elemType>
using avlTreeNode = _avlTreeNode<elemType>*;

//�������
template <typename elemType>
void layerOrderTravel(const avlTreeNode<elemType>& root, void (*fun) (const avlTreeNode<elemType>&))
{
    if (root == nullptr)
    {
        //std::cout << "���ԶԿ������б���" << std::endl;
        return;
    }
    std::queue<avlTreeNode<elemType> > q;
    q.push(root);
    while (!q.empty())
    {
        const avlTreeNode<elemType> node = q.front();
        if (node->lchild != nullptr) q.push(node->lchild);
        if (node->rchild != nullptr) q.push(node->rchild);
        fun(node);
        q.pop();
    }
}

template <typename elemType>
int getHeight(const avlTreeNode<elemType>& root)
{
    if (root == nullptr) return 0;
    return root->height;
}

template <typename elemType>
static int getBalance(const avlTreeNode<elemType>& root)
{
    if (root == nullptr) return 0;
    //ע������ʹ��getHeight��ȡ�߶Ⱥ���Ҫ��������ֱ����ָ�룺root->lchild->height�Լ�root->rchild->height
    //��Ϊroot�����Ӻ��к����п���ΪNULL��ֱ�ӻ�ȡָ�����׵��³��������
    return getHeight(root->lchild) - getHeight(root->rchild);
}

template <typename elemType>
static void updateHeight(avlTreeNode<elemType>& root)
{
    if (root == nullptr)
    {
        //throw
        //std::cout << "updateHeight�г��ԶԿ������¸߶�" << std::endl;
        return;
    }
    root->height = std::max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

//����rootΪ����������������
template <typename elemType>
static void lRotate(avlTreeNode<elemType>& root)
{
    avlTreeNode<elemType> node = root->rchild;
    root->rchild = node->lchild;
    node->lchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//����
template <typename elemType>
static void rRotate(avlTreeNode<elemType>& root)
{
    avlTreeNode<elemType> node = root->lchild;
    root->lchild = node->rchild;
    node->rchild = root;
    updateHeight(root);
    updateHeight(node);
    root = node;
}

//����
template <typename elemType>
void avlTreeInsert(avlTreeNode<elemType>& root, elemType x)
{
    //�����������ƽ��������Ĳ���λ��һ����Ҷ�ӽڵ�ĺ���(nullptr)
    if (root == nullptr)
    {
        avlTreeNode<elemType> newNode = new _avlTreeNode<elemType>(x);
        root = newNode;
        //std::cout << root->data << "�Ѿ�����" << std::endl;
        return;
    }
    if (x == root->data)
    {
        //std::cout << "Ԫ��" << x << "�Ѿ�����" << std::endl;
        return;
    }
    if (x < root->data)
    {
        avlTreeInsert(root->lchild, x);
        updateHeight(root);
        //��root���������в��룬�����²�ƽ�⣬root��ƽ������һ����2
        if (getBalance(root) == 2)
        {
            //LL�ͣ���root����
            if (getBalance(root->lchild) == 1)
                rRotate(root);
            //LR�ͣ��ȶ�root���������������ٶ�root����
            else if (getBalance(root->lchild) == -1)
            {
                lRotate(root->lchild);
                rRotate(root);
            }
        }
    }
    else if (x > root->data)
    {
        avlTreeInsert(root->rchild, x);
        updateHeight(root);
        //��root���������в��룬�����²�ƽ�⣬root��ƽ������һ����-2
        if (getBalance(root) == -2)
        {
            //RL�ͣ��ȶ�root���������������ٶ�root����
            if (getBalance(root->rchild) == 1)
            {
                rRotate(root->rchild);
                lRotate(root);
            }
            //RR�ͣ�ֱ�Ӷ�root����
            if (getBalance(root->rchild) == -1)
                lRotate(root);
        }
    }

}

//����
template <typename elemType>
avlTreeNode<elemType> createAVLTree(std::vector<elemType>& elems)
{
    avlTreeNode<elemType> root = nullptr;
    for (int i = 0; i < elems.size(); i++)
        avlTreeInsert(root, elems[i]);
    return root;
}

//����
template <typename elemType>
avlTreeNode<elemType> avlTreeFind(const avlTreeNode<elemType>& root, elemType x)
{
    if (root == nullptr)
    {
        //std::cout << "���ڳ��ԶԿ������в���" << std::endl;
        return nullptr;
    }
    if (root->data == x)
        return root;
    else if (x < root->data)
        avlTreeFind(root->lchild, x);
    else if (x > root->data)
        avlTreeFind(root->rchild, x);
    return nullptr;
}

//��������������Ϊ��ӡ�ڵ��ֵ
template <typename elemType>
void printAVLTree(const avlTreeNode<elemType>& root)
{
    std::cout << root->data << std::endl;
}

#endif // __AVLTREE__H
