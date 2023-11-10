/*                         平衡二叉树模板                                     *
*                        Author: chenyu qi                                    *
*                           已实现接口                                        *
* 1.创建一棵空树: avlTreeNode<elemType> root = NULL;                          *
* 2.在树root中插入x: avlTreeInsert(root,x);                                   *
* 3.在树root中查找x: avlTreeFind(root,x);                                     *
* 4.层序遍历root，对每个节点执行指定操作fun: layerOrderTravel(root,fun);      *
* 5.返回以root为根的树的高度: getHeight(root)                                 */

/*                  用法示例
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
    //叶子节点的高度定义为1，叶子节点的孩子节点(nullptr)高度为0
    _avlTreeNode<elemType>() = delete;
    _avlTreeNode<elemType>(elemType data) : data(data), height(1), lchild(nullptr), rchild(nullptr) {};
};

template <typename elemType>
using avlTreeNode = _avlTreeNode<elemType>*;

//层序遍历
template <typename elemType>
void layerOrderTravel(const avlTreeNode<elemType>& root, void (*fun) (const avlTreeNode<elemType>&))
{
    if (root == nullptr)
    {
        //std::cout << "尝试对空树进行遍历" << std::endl;
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
    //注意这里使用getHeight获取高度很重要，而不能直接用指针：root->lchild->height以及root->rchild->height
    //因为root的左孩子和有孩子有可能为NULL，直接获取指针容易导致程序崩溃。
    return getHeight(root->lchild) - getHeight(root->rchild);
}

template <typename elemType>
static void updateHeight(avlTreeNode<elemType>& root)
{
    if (root == nullptr)
    {
        //throw
        //std::cout << "updateHeight中尝试对空树更新高度" << std::endl;
        return;
    }
    root->height = std::max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

//对以root为根的子树进行左旋
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

//右旋
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

//插入
template <typename elemType>
void avlTreeInsert(avlTreeNode<elemType>& root, elemType x)
{
    //二叉查找树和平衡二叉树的插入位置一定是叶子节点的孩子(nullptr)
    if (root == nullptr)
    {
        avlTreeNode<elemType> newNode = new _avlTreeNode<elemType>(x);
        root = newNode;
        //std::cout << root->data << "已经插入" << std::endl;
        return;
    }
    if (x == root->data)
    {
        //std::cout << "元素" << x << "已经存在" << std::endl;
        return;
    }
    if (x < root->data)
    {
        avlTreeInsert(root->lchild, x);
        updateHeight(root);
        //在root的左子树中插入，若导致不平衡，root的平衡因子一定是2
        if (getBalance(root) == 2)
        {
            //LL型，对root右旋
            if (getBalance(root->lchild) == 1)
                rRotate(root);
            //LR型，先对root的左子树左旋，再对root右旋
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
        //在root的右子树中插入，若导致不平衡，root的平衡因子一定是-2
        if (getBalance(root) == -2)
        {
            //RL型，先对root的右子树右旋，再对root左旋
            if (getBalance(root->rchild) == 1)
            {
                rRotate(root->rchild);
                lRotate(root);
            }
            //RR型，直接对root左旋
            if (getBalance(root->rchild) == -1)
                lRotate(root);
        }
    }

}

//建立
template <typename elemType>
avlTreeNode<elemType> createAVLTree(std::vector<elemType>& elems)
{
    avlTreeNode<elemType> root = nullptr;
    for (int i = 0; i < elems.size(); i++)
        avlTreeInsert(root, elems[i]);
    return root;
}

//查找
template <typename elemType>
avlTreeNode<elemType> avlTreeFind(const avlTreeNode<elemType>& root, elemType x)
{
    if (root == nullptr)
    {
        //std::cout << "正在尝试对空树进行查找" << std::endl;
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

//将遍历操作定义为打印节点的值
template <typename elemType>
void printAVLTree(const avlTreeNode<elemType>& root)
{
    std::cout << root->data << std::endl;
}

#endif // __AVLTREE__H
