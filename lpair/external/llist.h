#ifndef L_LLIST_H
#define L_LLIST_H
#include <iostream>
#include <assert.h>

using namespace std;

template<class T>
class LList{
    struct LArrayDataStruct
    {
        int m_size;//数据存放的长度
        int m_alloc;//分配的空间长度
        T *m_pHead;//数据存空间
    };
public:
    class iterator {
    public:
        T *i;

        inline iterator() : i(nullptr) {}
        inline iterator(T *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline T &operator*() const { return *i; }
        inline T *operator->() const { return i; }
        inline T &operator[](int j) const { return *(i + j); }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline iterator operator++(int) { T *n = i; ++i; return n; }
        inline iterator &operator--() { i--; return *this; }
        inline iterator operator--(int) { T *n = i; i--; return n; }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return i - j.i; }
        inline operator T*() const { return i; }
    };
    friend class iterator;
private:
    LArrayDataStruct *m_pData; //维护数据所需要的指针
public:
    LList();//指定元素类型T，构造一个空的LList对象
//    explicit LList(const T &t);//指定元素t，构造一个包含t的LList对象
    LList(LList &other);//拷贝构造函数，深拷贝
    LList(int allocLength);//根据分配长度创建容量为大于等于allocLength的2^n的空LList
    ~LList();//LList析构函数
    T operator[](int i);//下标访问列表元素
    LList<T>& operator=(LList<T> &other);//重写=运算符
    iterator insert(iterator pos,const T &t);//在位置pos插入新的元素节点t,返回插入的节点迭代器
    void insert(int pos,const T &t);//在下标为pos的位置插入新的元素t
    void prepend(const T& t);//插入元素t到头部
    void append(const T& t);//插入元素t到尾部
    int indexOf(const T& t);//搜索数据在列表内首次出现的位置
    int lastIndexOf(const T& t);//搜索数据在列表内最后一次出现的位置
    iterator firstOf(const T& t);//得到元素在列表内首次出现的迭代器
    iterator lastOf(const T& t);//得到元素在列表内最后一次出现的迭代器
    void remove(int pos);//移除指定位置的元素
    void remove(iterator pos);//移除指定元素
    void removeFirst();//移除列表头部元素
    void removeLast();//移除列表尾部元素
    T take(int pos);//提取指定位置元素，并删除该元素
    T take(iterator pos);//提取指定元素，并删除该元素
    T takeFirst();//提取头部元素，并删除该元素
    T takeLast();//提取尾部元素，并删除该元素
    bool contains(const T& t);//判断元素是否存在于列表
    void clear();//清空列表
    bool isEmpty();//判断列表是否为空
    int count();//返回列表长度
    iterator begin();//返回列表第一个节点的迭代器
    iterator end();//返回列表最后一个元素的后一个元素迭代器
    T get(int pos);//获取指定位置元素
    T get(iterator pos);//获取指定元素
    T getFirst();//获取头部元素
    T getLast();//获取尾部元素




};

#endif
