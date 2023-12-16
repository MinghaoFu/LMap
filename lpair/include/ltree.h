#ifndef L_LTREE_H
#define L_LTREE_H

#include "lpair.h"
#include <cstring>
#include <algorithm>

typedef bool rbTreeNode_color;
const rbTreeNode_color red = false;
const rbTreeNode_color black = true;

template <class Value>
struct rbTreeNode {
    typedef Value value_type;
    typedef rbTreeNode_color color_type;
    typedef rbTreeNode* node_ptr;

    value_type m_value;
    color_type m_color;
    node_ptr m_pParent;
    node_ptr m_pLeft;
    node_ptr m_pRight;

    rbTreeNode() {
        m_value = value_type();
        m_color = red;
        m_pParent = nullptr;
        m_pLeft = nullptr;
        m_pRight = nullptr;
    }
    rbTreeNode(value_type value,
                 color_type color,
                 node_ptr parent,
                 node_ptr m_pLeftchild,
                 node_ptr m_pRightchild)
    {
        m_value = value;
        m_color = color;
        m_pParent = parent;
        m_pLeft = m_pLeftchild;
        m_pRight = m_pRightchild;
    }
    rbTreeNode(value_type value,
                 color_type color)
    {
        m_value = value;
        m_color = color;
        m_pParent = nullptr;
        m_pLeft = nullptr;
        m_pRight = nullptr;
    }
    rbTreeNode(const node_ptr& node) {
        m_value = node->m_value;
        m_color = node->m_color;
        m_pParent = nullptr;
        m_pLeft = nullptr;
        m_pRight = nullptr;
    }

    static node_ptr minimum(node_ptr x) {
        while (x->m_pLeft) x = x->m_pLeft;
        return x;
    }
    
    static node_ptr maximum(node_ptr x) {
        while (x->m_pRight != nullptr) x = x->m_pRight;
        return x;
    }
};

template <class Value, class Ref>
struct rbTreeIterator {
    typedef Value value_type;
    typedef Value& reference;
    typedef const Value& const_reference;
    typedef Value* pointer;
    typedef rbTreeNode_color color_type;
    typedef rbTreeNode<value_type>* node_ptr;
    typedef rbTreeIterator<value_type, reference> iterator;
    typedef rbTreeIterator<value_type, const_reference> const_iterator;

    rbTreeIterator() {}
    rbTreeIterator(node_ptr x) { m_node = x; }
    rbTreeIterator(const iterator& it) { m_node = it.m_node; }
    rbTreeIterator(iterator& it) { m_node = it.m_node; }

    Ref operator*() const { return m_node->m_value; }
    pointer operator->() const { return (pointer)&m_node->m_value; }
    
    void increment() {
        if (m_node->m_pRight) {
            m_node = m_node->m_pRight;
            while (m_node->m_pLeft) {
                m_node = m_node->m_pLeft;
            }
        } else {
            node_ptr y = m_node->m_pParent;
            while (m_node == y->m_pRight) {
              m_node = y;
              y = y->m_pParent;
            }
            if (m_node->m_pRight != y)
              m_node = y;
        }
    }
    
    void decrement() {
        if (m_node->m_pLeft) {
            m_node = m_node->m_pLeft;
            while (m_node->m_pRight) {
                m_node = m_node->m_pRight;
            }
        } else {
            node_ptr y = m_node->m_pParent;
            while (m_node == y->m_pLeft) {
              m_node = y;
              y = y->m_pParent;
            }
            if (m_node->m_pLeft != y)
              m_node = y;
        }
    }
    
    iterator operator++() { increment(); return *this; }
    iterator operator++(int) {
        iterator tmp = *this;
        increment();
        return tmp;
    }
    
    iterator operator--() { decrement(); return *this; }
    iterator operator--(int) {
        iterator tmp = *this;
        decrement();
        return tmp;
    }
    
    bool operator==(iterator y) { return m_node == y.m_node; }
    bool operator!=(iterator y) { return m_node != y.m_node; }
    
    node_ptr m_node;
};

template <class InputIterator>
class rbTreeReverseIterator {
    typedef InputIterator iterator;
    typedef rbTreeReverseIterator reverse_iterator;
    typedef typename InputIterator::value_type value_type;
    typedef typename InputIterator::node_ptr node_ptr;
    typedef typename InputIterator::reference reference;
    typedef typename InputIterator::const_reference const_reference;
    typedef typename InputIterator::pointer pointer;
private:
    iterator m_it;
public:
    rbTreeReverseIterator(iterator x) { m_it = x; }
    rbTreeReverseIterator(node_ptr x) { m_it = x; }
    
    const reference operator*() const { return *m_it; }
    pointer operator->() const { return (pointer)&(*m_it); }
    
    reverse_iterator operator++() { --m_it; return *this; }
    reverse_iterator operator++(int) {
        iterator tmp = m_it;
        m_it--;
        return tmp;
    }
    
    reverse_iterator operator--() { ++m_it; return *this; }
    reverse_iterator operator--(int) {
        iterator tmp = m_it;
        m_it++;
        return tmp;
    }
    
    bool operator==(reverse_iterator y) { return m_it == y.m_it; }
    bool operator!=(reverse_iterator y) { return m_it != y.m_it; }
};

template <class Key, class Value, class Compare = std::less<Key>>
class rbTree {
private:
    typedef Key key_type;
    typedef Value value_type;
    typedef Value& reference;
    typedef const Value& const_reference;
    typedef rbTreeNode_color color_type;
    typedef rbTreeNode<value_type> node;
    typedef rbTreeNode<value_type>* node_ptr;
    typedef rbTree<Key, Value, Compare> tree;
    typedef size_t size_type;
public:
    typedef rbTreeIterator<value_type, reference> iterator;
    typedef rbTreeIterator<value_type, const_reference> const_iterator;
    typedef rbTreeReverseIterator<iterator> reverse_iterator;
    typedef rbTreeReverseIterator<const_iterator> const_reverse_iterator;
    
private:
    size_type m_nodeCount;
    node_ptr m_header;
    Compare m_keyCompare;

protected:
    node_ptr getNode() {
        node_ptr m = new node;
        return m;
    } // substitution for allocator and deallocator temporarily
    void putNode(node_ptr p) { delete p; }
    node_ptr createNode(const value_type& v) {
        node_ptr temp = getNode();
        temp->m_value = v;
        return temp;
    }
    node_ptr cloneNode(node_ptr x) {
        node_ptr temp = createNode(x->m_value);
        temp->m_color = x->m_color;
        return temp;
    }
    void destroyNode(node_ptr p) {
        // Delete key or value avoid memory leak
        putNode(p);
    }
    void clear(node_ptr p) {
        if (!p) return;
        clear(p->m_pLeft);
        clear(p->m_pRight);
        putNode(p);
    }
    void init() {
        m_header = getNode();
        m_header->m_color = red;
        root() = nullptr;
        leftmost() = m_header;
        rightmost() = m_header;
    }
    node_ptr copy(node_ptr x, node_ptr p) {
        node_ptr top = cloneNode(x);
        top->m_pParent = p;
        
        try {
          if (x->right)
            top->right = copy(right(x), top);
          p = top;
          x = left(x);

          while (x != 0) {
            node_ptr y = cloneNode(x);
            p->m_pLeft = y;
            y->parent = p;
            if (x->m_pRight)
              y->m_pRight = copy(x->m_pRight, y);
            p = y;
            x = x->m_pLeft;
          }
        }
        catch(...) {
          erase(top);
          throw;
        }
        return top;
    }
public:
    rbTree(const Compare& comp = Compare())
    : m_nodeCount(0), m_keyCompare(comp) { init(); }
    
    rbTree(const tree& x)
    : m_nodeCount(0), m_keyCompare(x.m_keyCompare) {
        m_header = getNode();
        m_header->m_color = red;
        if (x.root() == 0) {
          root() = 0;
          leftmost() = m_header;
          rightmost() = m_header;
        }
        else {
          try {
            root() = copy(x.root(), m_header);
          }
          catch(...) {
              putNode(m_header);
            throw;
          }
          leftmost() = minimum(root());
          rightmost() = maximum(root());
        }
        m_nodeCount = x.m_nodeCount;
    }
    ~rbTree() {
        clear(m_header->m_pParent);
        putNode(m_header);
    }
    
    void rbTreeRotateLeft(node_ptr x, node_ptr& root) {
        node_ptr y = x->m_pRight;
        x->m_pRight = y->m_pLeft;
        if (y->m_pLeft)
            y->m_pLeft->m_pParent = x;
        y->m_pParent = x->m_pParent;
        
        if (root == x)
            root = y;
        else if (x->m_pParent->m_pLeft == x)
            x->m_pParent->m_pLeft = y;
        else
            x->m_pParent->m_pRight = y;
        y->m_pLeft = x;
        x->m_pParent = y;
    }
    
    void rbTreeRotateRight(node_ptr x, node_ptr& root) {
        node_ptr y = x->m_pLeft;
        x->m_pLeft = y->m_pRight;
        if (y->m_pRight)
            y->m_pRight->m_pParent = x;
        y->m_pParent = x->m_pParent;
        
        if (root == x)
            root = y;
        else if (x->m_pParent->m_pRight == x)
            x->m_pParent->m_pRight = y;
        else
            x->m_pParent->m_pLeft = y;
        y->m_pRight = x;
        x->m_pParent = y;
    }
    
    void rbTreeRebalance(node_ptr x, node_ptr& root) {
        x->m_color = red;
        while (x != root && x->m_pParent->m_color == red) {
            if (x->m_pParent == x->m_pParent->m_pParent->m_pLeft) {
                node_ptr y = x->m_pParent->m_pParent->m_pRight;
                if (y && y->m_color == red) {
                    y->m_pParent->m_color = red;
                    y->m_color = black;
                    x->m_pParent->m_color = black;
                    x = x->m_pParent->m_pParent;
                } else {
                    if (x == x->m_pParent->m_pRight) {
                        x = x->m_pParent;
                        rbTreeRotateLeft(x, root);
                    }
                    rbTreeRotateRight(x->m_pParent->m_pParent, root);
                    x->m_pParent->m_color = black;
                    x->m_pParent->m_pRight->m_color = red;
                }
            } else {
                node_ptr y = x->m_pParent->m_pParent->m_pLeft;
                if (y && y->m_color == red) {
                    y->m_pParent->m_color = red;
                    y->m_color = black;
                    x->m_pParent->m_color = black;
                    x = x->m_pParent->m_pParent;
                } else {
                    if (x == x->m_pParent->m_pLeft) {
                        x = x->m_pParent;
                        rbTreeRotateRight(x, root);
                    }
                    rbTreeRotateLeft(x->m_pParent->m_pParent, root);
                    x->m_pParent->m_color = black;
                    x->m_pParent->m_pLeft->m_color = red;
                }
            }
        }
        root->m_color = black;
    }
    
    node_ptr rbTreeRebalanceForErase(node_ptr z,
                                node_ptr& root,
                                node_ptr& leftmost,
                                node_ptr& rightmost) {
        node_ptr y = z;
        node_ptr x = 0;
        node_ptr x_parent = 0;
        if (y->m_pLeft == 0)             // z has at most one non-null child. y == z.
          x = y->m_pRight;               // x might be null.
        else
          if (y->m_pRight == 0)          // z has exactly one non-null child.  y == z.
            x = y->m_pLeft;              // x is not null.
          else {                      // z has two non-null children.  Set y to
            y = y->m_pRight;             //   z's successor.  x might be null.
            while (y->m_pLeft != 0)
              y = y->m_pLeft;
            x = y->m_pRight;
          }
        if (y != z) {                 // relink y in place of z.  y is z's successor
          z->m_pLeft->m_pParent = y;
          y->m_pLeft = z->m_pLeft;
          if (y != z->m_pRight) {
              x_parent = y->m_pParent;
            if (x) x->m_pParent = y->m_pParent;
            y->m_pParent->m_pLeft = x;      // y must be a left child
            y->m_pRight = z->m_pRight;
            z->m_pRight->m_pParent = y;
          }
          else
            x_parent = y;
          if (root == z)
            root = y;
          else if (z->m_pParent->m_pLeft == z)
            z->m_pParent->m_pLeft = y;
          else
            z->m_pParent->m_pRight = y;
          y->m_pParent = z->m_pParent;
            std::swap(y->m_color, z->m_color);
          y = z;
          // y now points to node to be actually deleted
        }
        else {                        // y == z
          x_parent = y->m_pParent;
          if (x) x->m_pParent = y->m_pParent;
          if (root == z)
            root = x;
          else
            if (z->m_pParent->m_pLeft == z)
              z->m_pParent->m_pLeft = x;
            else
              z->m_pParent->m_pRight = x;
          if (leftmost == z)
            if (z->m_pRight == 0)        // z->left must be null also
              leftmost = z->m_pParent;
          // makes leftmost == header if z == root
            else { leftmost = node::minimum(x); }
          if (rightmost == z)
            if (z->m_pLeft == 0)         // z->right must be null also
              rightmost = z->m_pParent;
          // makes rightmost == header if z == root
            else { rightmost = node::maximum(x); }                    // x == z->left
        }
        if (y->m_color != red) {
          while (x != root && (x == 0 || x->m_color == black))
              if (x == x_parent->m_pLeft) {
              node_ptr w = x_parent->m_pRight;
              if (w->m_color == red) {
                w->m_color = black;
                x_parent->m_color = red;
                rbTreeRotateLeft(x_parent, root);
                w = x_parent->m_pRight;
              }
              if ((w->m_pLeft == 0 || w->m_pLeft->m_color == black) &&
                  (w->m_pRight == 0 || w->m_pRight->m_color == black)) {
                w->m_color = red;
                  x = x_parent;
                  x_parent = x_parent->m_pParent;
              } else {
                if (w->m_pRight == 0 || w->m_pRight->m_color == black) {
                  if (w->m_pLeft) w->m_pLeft->m_color = black;
                  w->m_color = red;
                  rbTreeRotateRight(w, root);
                  w = x_parent->m_pRight;
                }
                w->m_color = x_parent->m_color;
                x_parent->m_color = black;
                if (w->m_pRight) w->m_pRight->m_color = black;
                rbTreeRotateLeft(x_parent, root);
                break;
              }
            } else {                  // same as above, with right <-> lefm_t.
              node_ptr w = x_parent->m_pLeft;
              if (w->m_color == red) {
                w->m_color = black;
                x_parent->m_color = red;
                rbTreeRotateRight(x_parent, root);
                w = x_parent->m_pLeft;
              }
              if ((w->m_pRight == 0 || w->m_pRight->m_color == black) &&
                  (w->m_pLeft == 0 || w->m_pLeft->m_color == black)) {
                w->m_color = red;
                x = x_parent;
                x_parent = x_parent->m_pParent;
              } else {
                if (w->m_pLeft == 0 || w->m_pLeft->m_color == black) {
                  if (w->m_pRight) w->m_pRight->m_color = black;
                  w->m_color = red;
                  rbTreeRotateLeft(w, root);
                  w = x_parent->m_pLeft;
                }
                w->m_color = x_parent->m_color;
                x_parent->m_color = black;
                if (w->m_pLeft) w->m_pLeft->m_color = black;
                rbTreeRotateRight(x_parent, root);
                break;
              }
            }
          if (x) x->m_color = black;
        }
        return y;
    }
    
    iterator insert(const value_type& v) {
        node_ptr tmp = createNode(v);
        node_ptr it = root();
        if (!it) {
            m_header->m_pParent = tmp;
            tmp->m_pParent = m_header;
            m_header->m_pLeft = tmp;
            m_header->m_pRight = tmp;
        } else {
            while (it) {
                if (it->m_value.KeyOfValue() ==  v.KeyOfValue()) {
                    tmp = nullptr;
                    return tmp;
                } else if (it->m_value.KeyOfValue() > v.KeyOfValue()) {
                    if (!it->m_pLeft) {
                        it->m_pLeft = tmp;
                        tmp->m_pParent = it;
                        break;
                    } else {
                        it = it->m_pLeft;
                    }
                } else {
                    if (!it->m_pRight) {
                        it->m_pRight = tmp;
                        tmp->m_pParent = it;
                        break;
                    } else {
                        it = it->m_pRight;
                    }
                }
            }
        }
        leftmost() = node::minimum(root());
        rightmost() = node::maximum(root());
        rbTreeRebalance(tmp, root());
        ++m_nodeCount;
        return tmp;
    }
    
    node_ptr search(const key_type& k) {
        node_ptr it = root();
        if (!it) {
            return nullptr;
        } else {
            while (it) {
                if (it->m_value.KeyOfValue() == k) {
                    return it;
                } else if (it->m_value.KeyOfValue() < k) {
                    it = it->m_pRight;
                } else {
                    it = it->m_pLeft;
                }
            }
        }
        return nullptr;
    }
    
    value_type& insertOrAccess(const value_type& v) {
        node_ptr tmp = createNode(v);
        node_ptr it = root();
        if (!it) {
            m_header->m_pParent = tmp;
            tmp->m_pParent = m_header;
            m_header->m_pLeft = tmp;
            m_header->m_pRight = tmp;
        } else {
                while (it) {
                    if ((key_type)it->m_value.KeyOfValue() == (key_type)v.KeyOfValue()) {
                        return it->m_value;
                    } else if ((key_type)it->m_value.KeyOfValue() > (key_type)v.KeyOfValue()) {
                        if (!it->m_pLeft) {
                            it->m_pLeft = tmp;
                            tmp->m_pParent = it;
                            break;
                        } else {
                            it = it->m_pLeft;
                        }
                    } else {
                        if (!it->m_pRight) {
                            it->m_pRight = tmp;
                            tmp->m_pParent = it;
                            break;
                        } else {
                            it = it->m_pRight;
                        }
                    }
                }
        }
        leftmost() = node::minimum(root());
        rightmost() = node::maximum(root());
        rbTreeRebalance(tmp, root());
        ++m_nodeCount;
        return tmp->m_value;
    }
    
    template <class InputIterator = iterator>
    iterator insert(InputIterator it) {
        return insert(value_type(it->key(), it->value()));
    }
    
    template <class InputIterator = iterator>
    iterator insertUnique(InputIterator first, InputIterator last) {
        for (InputIterator it = first; it != last; ++it) {
            insert(it);
        }
        return nullptr;
    }
    
    void erase(iterator position) {
        node_ptr y = rbTreeRebalanceForErase(position.m_node,
                                                 m_header->m_pParent,
                                                 m_header->m_pLeft,
                                                 m_header->m_pRight);
        destroyNode(y);
        --m_nodeCount;
    }
    
    size_type erase(const key_type& k) {
        node_ptr x = search(k);
        if (!x) {
            return size_type(0);
        }
        node_ptr y = rbTreeRebalanceForErase(x,
                                                 m_header->m_pParent,
                                                 m_header->m_pLeft,
                                                 m_header->m_pRight);
        destroyNode(y);
        --m_nodeCount;
        return size_type(1);
    }
    
    template <class InputIterator = iterator>
    void eraseUnique(InputIterator first, InputIterator last) {
        for (InputIterator it = first; it != last; ++it) {
            erase(it);
        }
    }
    
    size_type count(const key_type& k) {
        return search(k) ? 1 : 0;
    }
    
    node_ptr& root() const { return m_header->m_pParent; }
    node_ptr& leftmost() const { return m_header->m_pLeft; }
    node_ptr& rightmost() const { return m_header->m_pRight; }
    
    value_type& value(const node_ptr& x) const { return x->m_value; }
    
    
    int black_node_count(node_ptr node, const node_ptr& root) {
        if (node == nullptr || node == m_header) {
            return 0;
        } else {
            int bc = node->m_color == black ? 1 : 0;
            return bc + black_node_count(node->m_pParent, root);
        }
    }
    
public:
    iterator begin() const { return leftmost(); }
    iterator end() { return m_header; }
    const_iterator cBegin() const { return leftmost(); }
    const_iterator cEnd() const { return m_header; }
    reverse_iterator rBegin() { return rightmost(); }
    reverse_iterator rEnd() { return m_header; }
    const_reverse_iterator crBegin() { return rightmost(); }
    const_reverse_iterator crEnd() { return m_header; }
    bool empty() const { return m_nodeCount == 0; }
    void clear() {
        clear(root());
        root() = nullptr;
        rightmost() = m_header;
        leftmost() = m_header;
        m_nodeCount = 0;
    }
    size_type size() const { return m_nodeCount; }
    size_type maxSize() const { return size_type(-1); } // size_t maximum
    const_iterator lowerBound(const key_type& k) const {
        node_ptr y = m_header;
        node_ptr x = root();
        while (x) {
            if ((key_type)x->m_value.KeyOfValue() > k || (key_type)x->m_value.KeyOfValue() == k) {
                y = x;
                x = x->m_pLeft;
            } else {
                x = x->m_pRight;
            }
        }
        return const_iterator(y);
    }
    const_iterator upperBound(const key_type& k) const {
        node_ptr y = m_header;
        node_ptr x = root();
        while (x) {
            if (x->m_value.KeyOfValue() < k) {
                y = x;
                x = x->m_pRight;
            } else {
                x = x->m_pLeft;
            }
        }
        return const_iterator(y);
    }
    void swap(tree& t) {
        std::swap(m_header, t.m_header);
        std::swap(m_nodeCount, t.m_nodeCount);
        std::swap(m_keyCompare, t.m_keyCompare);
    }
    
    LPair<const_iterator, const_iterator> equalRange(const key_type& k) const {
        return LPair<const_iterator, const_iterator>(lowerBound(k), upperBound(k));
    }
    
    bool operator==(tree& x) {
        auto i = begin(), j = x.begin();
        while (i != end() && j != x.end()) {
            if (i->key() != j->key() || i->value() != j->value()) { return false; }
            ++i, ++j;
        }
        if (i == end() && j == x.end())
            return true;
        else
            return false;
    } // simple equal definition
    bool operator!=(const tree& x) const { return !(*this == x); }
    
    bool rbVerify() {
        if (m_nodeCount == 0 || begin() == end())
          return m_nodeCount == 0 && begin() == end() &&
            m_header->m_pLeft == m_header && m_header->m_pRight == m_header;
        
        int len = black_node_count(leftmost(), root());
        for (iterator it = begin(); it != end(); ++it) {
          node_ptr x = (node_ptr)it.m_node;
          node_ptr L = x->m_pLeft;
          node_ptr R = x->m_pRight;

          if (x->m_color == red)
            if ((L && L->m_color == red) ||
                (R && R->m_color == red))
              return false;

          if (L && m_keyCompare(KeyOfValue(x->m_value), x->m_value))
            return false;
          if (R && m_keyCompare(KeyOfValue(R), KeyOfValue(x)))
            return false;

          if (!L && !R && black_node_count(x, root()) != len)
            return false;
        }

        if (leftmost() != node::minimum(root()))
          return false;
        if (rightmost() != node::maximum(root()))
          return false;

        return true;
    }
};


#endif
