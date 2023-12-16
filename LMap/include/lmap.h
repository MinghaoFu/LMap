#ifndef _LMAP_h
#define _LMAP_h

#include "ltree.h"
#include "llist.h"

template <class Key, class Data>
class LMap {
    typedef Key key_type;
    typedef Data data_type;
    typedef LPair<key_type, data_type> value_type;
    typedef size_t size_type;
    
    static key_type KeyOfValue(value_type v)  { return v->m_key; }
    
private:
    typedef LRbTree<key_type, value_type> tree;
    tree m_t;
    
public:
    typedef typename tree::iterator iterator;
    typedef typename tree::const_iterator const_iterator;
    typedef typename tree::reverse_iterator reverse_iterator;
    typedef typename tree::const_reverse_iterator const_reverse_iterator;

    LMap() : m_t() {};
    template <class InputIterator>
    LMap(InputIterator first, InputIterator last) : m_t() { m_t.insertUnique(first, last); }
    
    LMap(const LMap<key_type, data_type>& x) : m_t(x.m_t) {}
    LMap<key_type, data_type>& operator=(const LMap<key_type, data_type>& x)
    {
      m_t = x.m_t;
      return *this;
    }
    
    iterator begin() { return m_t.begin(); }
    iterator end() { return m_t.end(); }
    const_iterator cBegin() const { return m_t.cBegin(); }
    const_iterator cEnd() const { return m_t.cEnd(); }
    reverse_iterator rBegin() { return m_t.rBegin(); }
    reverse_iterator rEnd() { return m_t.rEnd(); }
    const_reverse_iterator crBegin() { return m_t.crBegin(); }
    const_reverse_iterator crEnd() { return m_t.crEnd(); }
    bool empty() const { return m_t.empty(); }
    size_type size() const { return m_t.size(); }
    size_type maxSize() const { return m_t.maxSize(); }
    
    data_type& operator[](const key_type& k) {
        return (m_t.insertOrAccess(value_type(k, data_type()))).value();
    }
    void swap(LMap<key_type, data_type>& x) { m_t.swap(x.t); }
    
    LPair<iterator, bool> insert(const value_type& x) {
        iterator it = m_t.insert(x);
        bool b = it.m_node ? true : false;
        return LPair<iterator, bool>(it, b);
    }
    
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        m_t.insertUnique(first, last);
    }
    
    void erase(iterator position) { m_t.erase(position); }
    size_type erase(const key_type& k) { return m_t.erase(k); }
    template<class InputIterator>
    void erase(InputIterator first, InputIterator last) {
        m_t.eraseUnique(first, last);
    }
    void clear() { m_t.clear(); }
    
    iterator find(const key_type& k) { return m_t.search(k); }
    size_type count(const key_type& k) { return m_t.count(k); }
    const_iterator lowerBound(const key_type& k) { return m_t.lowerBound(k); }
    const_iterator upperBound(const key_type& k) { return m_t.upperBound(k); }
    
    LPair<const_iterator, const_iterator> equalRange(const key_type& k) { return m_t.equalRange(k); }
    
    bool operator==(LMap& x) { return m_t == x.m_t; }
    bool operator!=(LMap& x) { return m_t != x.m_t; }

    LList<key_type> keyList() {
        LList<key_type> l;
        for (auto it = m_t.begin(); it != m_t.end(); ++it) {
            l.append(it->key());
        }
        return l;
    }
};

#endif /* LMap_h */
