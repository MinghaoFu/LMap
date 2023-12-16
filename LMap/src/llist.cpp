#include "llist.h"

//构造函数。指定元素类型T，构造一个空的LList对象
template<class T>
LList<T>::LList(){
//开辟一个LArrayDataStruct空间，初始化m_size=0,m_alloc=0,m_pHead=nullptr
    m_pData=new LArrayDataStruct;
    m_pData->m_size=0;
    m_pData->m_alloc=0;
    m_pData->m_pHead= nullptr;
}

/*//构造函数。指定元素t，构造一个包含t的LList对象
template<class T>
LList<T>::LList(const T &t)  {
//开辟一个LArrayDataStruct空间，初始化m_size=1,m_alloc=2
    m_pData=new LArrayDataStruct;
    m_pData->m_size=1;
    m_pData->m_alloc=2;
//开辟两个T的空间并存放t，将地址给m_pHead
    m_pData->m_pHead=new T[m_pData->m_alloc];
    m_pData->m_pHead[0]=t;

}*/

//拷贝构造函数，深拷贝
template<class T>
LList<T>::LList(LList &other){
    m_pData=new LArrayDataStruct;
    m_pData->m_size=other.m_pData->m_size;
    m_pData->m_alloc=other.m_pData->m_alloc;
    if(other.m_pData->m_pHead== nullptr)
        m_pData->m_pHead= nullptr;
    else{
        m_pData->m_pHead=new T[other.m_pData->m_alloc];
        for(int i=0;i<other.m_pData->m_size;i++) {
            m_pData->m_pHead[i]=other.m_pData->m_pHead[i];
        }
    }

}


//根据分配长度创建容量为大于等于allocLength的2^n的空LList
template<class T>
LList<T>::LList(int allocLength){
    if(allocLength<=0){
        fprintf(stderr,"initial length must be grater than 0\n");
        assert(false);
    }
    //开辟一个LArrayDataStruct空间，初始化m_size=0,m_alloc=0,m_pHead=nullptr
    m_pData=new LArrayDataStruct;
    m_pData->m_size=0;
    //将长度变成2^n大小
    int n=allocLength-1;
    n |= (n>>1);
    n |= (n>>2);
    n |= (n>>4);
    n |= (n>>8);
    n |= (n>>16);
    m_pData->m_alloc=n;
    cout<<"初始化长度为："<<n+1<<endl;
    m_pData->m_pHead= new T[n+1];
}

//析构函数
template<class T>
LList<T>::~LList() {
    if(m_pData->m_pHead!= nullptr)
        delete[] m_pData->m_pHead;
    m_pData->m_pHead=nullptr;
    delete m_pData;
    m_pData=nullptr;
}

//下标访问列表元素
template<class T>
T LList<T>::operator[](int pos){
    if(!(pos>=0 && pos<=m_pData->m_size-1)){
        fprintf(stderr,"index out of range!\n");
        assert(false);
    } else{
        return begin()[pos];
    }
}

//重写=运算符
template<class T>
LList<T>& LList<T>::operator=(LList<T>& other){
    if(m_pData!= nullptr) {
        if (m_pData->m_pHead != nullptr) {
            delete[] m_pData->m_pHead;
        }
        m_pData->m_size=other.m_pData->m_size;
        m_pData->m_alloc=other.m_pData->m_alloc;
        if(other.m_pData->m_pHead== nullptr)
            m_pData->m_pHead= nullptr;
        else{
            m_pData->m_pHead=new T[other.m_pData->m_alloc];
            for(int i=0;i<other.m_pData->m_size;i++) {
                m_pData->m_pHead[i]=other.m_pData->m_pHead[i];
            }
        }

    }else {
        m_pData=new LArrayDataStruct;
        m_pData->m_size=other.m_pData->m_size;
        m_pData->m_alloc=other.m_pData->m_alloc;
        if(other.m_pData->m_pHead== nullptr)
            m_pData->m_pHead= nullptr;
        else{
            m_pData->m_pHead=new T[other.m_pData->m_alloc];
            for(int i=0;i<other.m_pData->m_size;i++) {
                m_pData->m_pHead[i]=other.m_pData->m_pHead[i];
            }
        }
    }
    return *this;
}

//在pos位置插入新的元素节点t,返回插入的节点迭代器
template<class T>
class LList<T>::iterator LList<T>::insert(class LList<T>::iterator pos, const T &t){
    //列表为空并且pos为无效迭代器，则为t分配空间，将t地址返回给m_pData->m_pHead，m_size++,m_alloc=2返回t的迭代器
    if(m_pData->m_size==0 && (T*)pos== nullptr) {
        if(m_pData->m_pHead== nullptr){ //刚初始化的列表,没有空间分配
            m_pData->m_alloc=2;
            m_pData->m_pHead = new T[m_pData->m_alloc];
        }
        m_pData->m_pHead[0]=t;
        m_pData->m_size++;
        return iterator(m_pData->m_pHead);
    }
    //列表为空，pos不为无效迭代器，返回无效迭代器
    //列表不为空，pos迭代器范围不在列表地址范围，返回无效迭代器
    if((m_pData->m_size==0 && (T*)pos!= nullptr) || (m_pData->m_size!=0 && !(begin()<=pos && pos<=end())))
        return iterator(nullptr);
    //列表不为空，pos不为无效迭代器并且迭代器在列表地址范围，执行以下操作：
    if(m_pData->m_size!=0 && begin()<=pos && pos<=end()){
        if(m_pData->m_alloc > m_pData->m_size){//如果m_alloc>m_size,将pos位置元素及之后的所有元素后移一位，将t插入位置pos,m_size++
            for(iterator i=end()-1;i>=pos;i--){
                *(i+1) = *i;
            }
            *pos=t;
            m_pData->m_size++;
        }else{
            //如果m_alloc<=m_size,查新开辟一段可以存放2*m_alloc的T的空间，将数据复制到新空间，将pos位置元素及之后的元素后移一位，将t插入到pos之后，最后就原来的空间释放, m_size++,m_alloc=2*m_alloc
            T *pNewHead=new T[2*m_pData->m_alloc];
            int j=0;
            for(iterator i=begin();i<pos;i++,j++){
                pNewHead[j]=*i;
            }
            j=m_pData->m_size;
            for(iterator i=end()-1;i>=pos;i--,j--){
                pNewHead[j]=*i;
            }
            pNewHead[j]=t;
            delete[] m_pData->m_pHead;
            m_pData->m_pHead=pNewHead;
            m_pData->m_size++;
            m_pData->m_alloc*=2;
            //返回t元素节点的迭代器
            return iterator(m_pData->m_pHead+j);

        }
    }

}

//将元素t插入到位置pos；
template<class T>
void LList<T>::insert(int pos, const T &t){
    //判断是否0<=pos<=m_size，若pos不在该范围：
    if(!(0<=pos && pos<=m_pData->m_size)){
        //在错误输出流中输出位置错误，跳过以下操作
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else if(m_pData->m_size==0){//列表为空
        if(m_pData->m_pHead== nullptr){
            //分配空间存放数据t
            m_pData->m_pHead=new T[2];
            m_pData->m_alloc=2;
        }
        m_pData->m_pHead[0]=t;
        m_pData->m_size++;
    }
    else{//列表不为空
        //判断m_alloc和m_size大小，若m_alloc>m_size，若是将pos及之后的元素后移一位，将t插入位置pos,m_size++
        if(m_pData->m_alloc > m_pData->m_size){
            for(int i=m_pData->m_size-1;i>=pos;i--){
                m_pData->m_pHead[i+1]=m_pData->m_pHead[i];
            }
            m_pData->m_pHead[pos]=t;
            m_pData->m_size++;
        }else{
            //若m_alloc<=m_size，查新开辟一段可以存放2*m_alloc的T的空间，将数据复制到新空间，将pos位置元素及之后的元素后移一位，将t插入到pos之后，最后就原来的空间释放, m_size++,m_alloc=2*m_alloc
            T* pNewHead=new T[2*m_pData->m_alloc];
            for(int i=0;i<pos;i++){
                pNewHead[i]=m_pData->m_pHead[i];
            }
            for(int i=m_pData->m_size-1;i>=pos;i--){
                pNewHead[i+1]=m_pData->m_pHead[i];
            }
            pNewHead[pos]=t;
            delete[] m_pData->m_pHead;
            m_pData->m_pHead=pNewHead;
            m_pData->m_size++;
            m_pData->m_alloc *= 2;

        }

    }


}

//插入元素t到头部
template<class T>
void LList<T>::prepend(const T& t){
    insert(0,t);

}

//插入元素到尾部
template<class T>
void LList<T>::append(const T& t){
    insert(m_pData->m_size,t);
}

//搜索数据在列表内首次出现的位置
template<class T>
int LList<T>::indexOf(const T& t){
    //在0~m_size-1范围内遍历元素，若找到立即返回元素下标
    //没找到则返回-1
    if(m_pData->m_size==0)
        return -1;
    int i;
    for(i=0;i<m_pData->m_size;i++){
        if(m_pData->m_pHead[i]==t)
            break;
    }
    if(0<=i && i<=m_pData->m_size-1)
        return i;
    else
        return -1;

}

//搜索元素在列表内最后一次出现的位置
template<class T>
int LList<T>::lastIndexOf(const T& t){
    //在在0~m_size-1范围内倒序遍历元素，若找到立即返回元素下标
    //没找到则返回-1
    if(m_pData->m_size==0)
        return -1;
    int i;
    for(i=m_pData->m_size-1;i>=0;i--){
        if(m_pData->m_pHead[i]==t)
            break;
    }
    if(0<=i && i<=m_pData->m_size-1)
        return i;
    else
        return -1;

}

//得到元素在列表内首次出现的迭代器
template<class T>
class LList<T>::iterator LList<T>::firstOf(const T& t){
    //遍历列表，如果找到数据则立即将节点迭代器返回，没找到则返回无效迭代器
    if(m_pData->m_size==0)//列表为空
        return iterator(nullptr);
    iterator i;
    for(i=begin();i<end();i++){
        if(*i==t)
            break;
    }
    if(begin()<=i && i<end())
        return i;
    else
        return iterator(nullptr);
}

//得到元素在列表内最后一次出现的迭代器
template<class T>
class LList<T>::iterator LList<T>::lastOf(const T& t){
    //倒序遍历列表，如果找到数据则立即将节点迭代器返回，没找到则返回无效迭代器
    if(m_pData->m_size==0)//列表为空
        return iterator(nullptr);
    iterator i;
    for(i=end()-1;i>=begin();i--){
        if(*i==t)
            break;
    }
    if(begin()<=i && i<end())
        return i;
    else
        return iterator(nullptr);
}

//移除指定位置的元素
template<class T>
void LList<T>::remove(int pos){
    //若0<=pos<=m_size-1，将pos位置之后的元素前移一位，m_size--
    //若pos不在该范围则在错误输出流中输出错误信息，并结束执行
    if(!(0<=pos && pos<=m_pData->m_size-1)){
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else{
        for(int i=pos+1;i<m_pData->m_size;i++){
            m_pData->m_pHead[i-1]=m_pData->m_pHead[i];
        }
        m_pData->m_size--;

    }
}

//移除指定元素
template<class T>
void LList<T>::remove(class LList<T>::iterator pos){
    //若0<=pos<=m_size-1，将pos位置之后的元素前移一位，m_size--
    //若pos不在该范围或列表为空则在错误输出流中输出错误信息，并结束执行
    if(!(pos>=begin() && pos<end())){
        fprintf(stderr,"index out of range!\n");
        assert(false);
    } else{
        for (iterator i = pos + 1; i <= this->end(); i++)
            *(i-1).i = *i;
        m_pData->m_size--;
    }

}

//移除头部元素
template<class T>
void LList<T>::removeFirst(){
    //m_size==0,在错误输出流中输出错误信息，并结束执行
    if(m_pData->m_size==0){
        fprintf(stderr,"the list is empty!\n");
        assert(false);
    }
    else{//m_size!=0，将首位置之后的元素前移一位，m_size--,返回True
        for(int i=1;i<m_pData->m_size;i++){
            m_pData->m_pHead[i-1]=m_pData->m_pHead[i];
        }
        m_pData->m_size--;
    }
}

//移除尾部元素
template<class T>
void LList<T>::removeLast(){
    //m_size==0，在错误输出流中输出错误信息，并结束执行
    if(m_pData->m_size==0){
        fprintf(stderr,"the list is empty!\n");
        assert(false);
    }
    else{//m_size！=0，m_size--
        m_pData->m_size--;
    }
}

//提取指定位置元素，并删除该元素
template<class T>
T LList<T>::take(int pos){
    //pos不在范围,在错误输出流中输出迭代器错误信息
    if(!(0<=pos && pos<=m_pData->m_size-1)){
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else{//列表不为空，并且位置正确（即pos合适）
        //接收位置为pos的元素，使用remove函数移除元素，返回该元素
        T t=m_pData->m_pHead[pos];
        remove(pos);
        return t;
    }

}

//提取指定元素，并删除该元素
template<class T>
T LList<T>::take(class LList<T>::iterator pos){
    //列表为空或者位置不正确
    if(!(pos>=begin() || pos<end()))
    {
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else{//m_size!=0,pos合理，接收pos迭代器元素，使用remove移除元素，返回元素
        T t=*pos;
        remove(pos);
        return t;
    }

}

//提取头部元素，并删除该元素
template<class T>
T LList<T>::takeFirst(){
    //m_size==0,在错误输出流中输出列表为空信息
    if(m_pData->m_size==0){
        fprintf(stderr,"the list is empty!\n");
        assert(false);
    }else{//m_size！=0，使用removeFist函数移除首部元素，返回头部元素
        T t=m_pData->m_pHead[0];
        removeFirst();
        return t;
    }

}

//提取尾部元素，并删除该元素
template<class T>
T LList<T>::takeLast(){
    //m_size==0，则在错误输出流中打印错误信息
    if(m_pData->m_size==0){
        fprintf(stderr,"the list is empty!\n");
        assert(false);
    }else {//m_size!=0,接收m_size-1位置元素，使用removeLast移除尾部元素，返回m_size-1位置元素
        T t = m_pData->m_pHead[m_pData->m_size - 1];
        removeLast();
        return t;
    }
}

//判断是否包含元素
template<class T>
bool LList<T>::contains(const T& t){
    if(m_pData->m_size==0)//列表为空
        return false;
    //遍历列表进行判断
    int i;
    for(i=0;i<m_pData->m_size;i++){
        if(m_pData->m_pHead[i]==t)
            break;
    }
    if(0<=i && i<=m_pData->m_size-1)
        return true;
    else
        return false;
}

//清空列表内所有的元素
template<class T>
void LList<T>::clear(){
    m_pData->m_size=0;
}

//判断列表是否为空
template<class T>
bool LList<T>::isEmpty(){
    return m_pData->m_size==0;
}

//返回列表长度
template<class T>
int LList<T>::count(){
    return m_pData->m_size;
}

//初始位置迭代器
template<class T>
class LList<T>::iterator LList<T>::begin(){
    if(m_pData->m_size==0)
        return iterator(nullptr);
    else
        return iterator(m_pData->m_pHead);
}

//末尾位置迭代器
template<class T>
class LList<T>::iterator LList<T>::end(){
    if(m_pData->m_size==0)
        return iterator(nullptr);
    else
        return iterator(m_pData->m_pHead+m_pData->m_size);
}

//获取指定位置元素
template<class T>
T LList<T>::get(int pos){
    //pos不在范围,在错误输出流中输出迭代器错误信息
    if(!(0<=pos && pos<=m_pData->m_size-1)){
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else{//列表不为空，并且位置正确（即pos合适）
        //接收位置为pos的元素，返回该元素
        T t=m_pData->m_pHead[pos];
        return t;
    }
}

//获取指定元素
template<class T>
T LList<T>::get(class LList<T>::iterator pos){
    //列表为空或者位置不正确
    if(!(pos>=begin() || pos<end()))
    {
        fprintf(stderr,"index out of range!\n");
        assert(false);
    }else{//m_size!=0,pos合理，接收pos迭代器元素，使用remove移除元素，返回元素
        T t=*pos;
        return t;
    }
}

//获取头部元素
template<class T>
T LList<T>::getFirst(){
    //m_size==0,在错误输出流中输出列表为空信息
    if(m_pData->m_size==0){
        fprintf(stderr,"the list is empty!\n");
        assert(false);
    }else{//m_size！=0，使用removeFist函数移除首部元素，返回头部元素
        T t=m_pData->m_pHead[0];
        return t;
    }
}

//获取尾部元素
template<class T>
T LList<T>::getLast() {
    //m_size==0，则在错误输出流中打印错误信息
    if (m_pData->m_size == 0) {
        fprintf(stderr, "the list is empty!\n");
        assert(false);
    } else {//m_size!=0,接收m_size-1位置元素，使用removeLast移除尾部元素，返回m_size-1位置元素
        T t = m_pData->m_pHead[m_pData->m_size - 1];
        return t;
    }
}








