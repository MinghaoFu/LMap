#ifndef _LPAIR_h
#define _LPAIR_h

template <class T1, class T2>
class LPair {
    typedef T1 key_type;
    typedef T2 value_type;
private:
    key_type m_key;
    value_type m_value;
public:
    LPair() : m_key(), m_value() {}
    LPair(const LPair& lp) : m_key(lp.m_key), m_value(lp.m_value) {}
    LPair(key_type a, value_type b): m_key(a), m_value(b) {}
    LPair(key_type k): m_key(k) { }
    
    LPair<T1, T2> operator=(const LPair<key_type, value_type>& x) {
        m_key = x.m_key;
        m_value = x.m_value;
        return *this;
    }
    
    const key_type& KeyOfValue() const { return m_key; }
    
    const key_type& key() const { return m_key; }
    value_type& value() { return m_value; }
    
    bool operator==(LPair<T1, T2>& y) {
        return y.key() == key() && y.value() == value();
    }
    
    bool operator!=(LPair<T1, T2>& y) {
        return !(*this == y);
    }
    
    bool operator<(LPair<T1, T2>& y) {
        return key() < y.key() || ((key() == y.key()) && value() < y.value());
    }
    
    bool operator<=(LPair<T1, T2>& y) {
        return !(y < *this);
    }
    
    bool operator>(LPair<T1, T2>& y) {
        return y < *this;
    }

    bool operator>=(LPair<T1, T2>& y) {
        return !(*this < y);
    }
};

#endif /* LPair_h */
