/*      Author: chenyu qi       *
* Heap<>是一个类模板，用Heap<>可*
* 以创建一个堆，所有的操作都在类*
* 模板对象上进行。              */
#include <vector>

using namespace std;

template <typename T>
struct Heap
{
    typedef T elemType;
    vector<elemType> heap;

    Heap(const std::vector<elemType> v);
    elemType operator [] (int i) { return heap[i]; };
    int size() {return heap.size();};
    void downAdjust(int i,int tail);
    void upAdjust(int i);
    void insertHeap(elemType x);
    void deleteRoot();
    void Sort();
};

template <typename T>
void Heap<T>::downAdjust(int i,int tail)
{
    if( i >= tail ) return ;
    int j = 2 * i + 1;
    while( j <= tail )
    {
        if( j + 1 <= tail && heap[j+1] > heap[j] )
            j = j + 1;
        if( heap[j] > heap[i] )
        {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
            i = j;
            j = j * 2 + 1;
        }
        else break;
    }
}

template <typename T>
void Heap<T>::upAdjust(int i)
{
    if( i <= 0 ) return ;
    int j = ( i - 1 ) / 2;
    while( j > 0 )
    {
        if( heap[i] > heap[j] )
        {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
            i = j;
            j = ( j - 1 ) / 2;
        }
        else break;
    }
}

template <typename T>
void Heap<T>::insertHeap(elemType x)
{
    heap.push_back(x);
    upAdjust(heap.size()-1);
}

template <typename T>
void Heap<T>::deleteRoot()
{
    elemType t = heap[0];
    heap[0] = heap[heap.size()-1];
    heap[heap.size()-1] = t;
    heap.pop_back();
}

template <typename T>
void Heap<T>::Sort()
{
    if( heap.size() < 2 ) return ;
    int tail = heap.size()-1;
    //有heap.size()个元素，一次操作排好一个，因此heap.size()-1次操作就全部排好了
    for( int i=1; i<=heap.size()-1; i++ )
    {
        elemType t = heap[0];
        heap[0] = heap[tail];
        heap[tail] = t;
        downAdjust(0,--tail);
    }
}

template <typename T>
Heap<T>::Heap(const std::vector<elemType> v)
{
    heap = v;
    for( int i=heap.size()/2; i>=0; i-- )
    {
        downAdjust(i,heap.size()-1);
    }
}
