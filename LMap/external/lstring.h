
#ifndef L_LSTRING_H
#define L_LSTRING_H
#include<string>
#include<iostream>
#include<string.h>
#include"lchar.h"

typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

class LString;

class LLatin1String{
private:
    const char* m_pData = nullptr;
    int m_size = 0;
public:
    LLatin1String ();
    LLatin1String (const char* str);
    LLatin1String (const char* str,int len);
    const char* latin1 ();
    int size () const;
    LLatin1Char at (int index);
    LLatin1Char operator[](int index);
    LLatin1String substr (int index ,int len);
    int compare (const char* str);
    int compare (LLatin1String &str);
    int compare (LString &str);
    bool operator == (const char* str);
    bool operator == (LLatin1String &str);
    bool operator == (LString &str);
    bool operator < (const char* str);
    bool operator < (LLatin1String &str);
    bool operator < (LString &str);
    bool operator > (const char* str);
    bool operator > (LLatin1String &str);
    bool operator > (LString &str);
};

class LString{
private:
    struct LStringDataStruct{
        LChar* m_pLChar = nullptr;
        const char* m_pChar = nullptr;
        int m_size = 0;//unicode字符数
    };
    struct LStringDataStruct* m_pData = nullptr;

    LChar* toLCharArray(const char* s);
    void transLStringToConstChar();
    
    
    int endian();//判断大小端，0小，1大
    int lCharStrToStrSize();
public:
    LString();
    LString(const char * s);
    LString(LLatin1String &s);
    LString(std::string& s);
    LString(LChar ch ,int num);
    LString(const LString& s);
    ~LString();

    int compare(const char* s);
    int compare(LLatin1String &s);
    int compare(const LString& s);
    bool operator<(const char* s);
    bool operator<(LLatin1String &s);
    bool operator<(const LString& s);
    bool operator>(const char* s);
    bool operator>(LLatin1String &s);
    bool operator>(const LString& s);
    LString& operator=(const char* s);
    LString& operator=(LLatin1String& s);
    LString& operator=(const LString& s);
    bool operator==(const char* s);
    bool operator==(LLatin1String& s);
    bool operator==(const LString& s);
    LChar at(int index);
    LChar operator[](int index);
    void insert(int pos,const char* s);
    void insert(int pos,LLatin1String &s);
    void insert(int pos,const LString& s);
    void prepend(const char* s);
    void prepend(LLatin1String &s);
    void prepend(const LString& s);
    void append(const char* s);
    void append(LLatin1String &s);
    void append(const LString& s);
    void trim();
    void replace(const LString &s1, const LString &s2);
    void erase(int pos, int num);
    bool isEmpty();
    int indexOf(LChar ch);
    int lastIndexOf(LChar ch);
    int length() const;
    int toInt(int base = 10);
    uint toUInt(int base = 10);
    long toLong(int base = 10);
    ulong toULong(int base = 10);
    longlong toLongLong(int base = 10);
    ulonglong toULongLong(int base = 10);
    float toFloat();
    double toDouble();
    long double toLongDouble();
    LString toUpper();
    LString toLower();
    std::string toStdString() const;
    const char* toConstChar() const;
    template <typename ...Args>
    LString format(Args... args);

    static int strToLCharStrSize(const char* s);

    friend std::ostream& operator<<(std::ostream& out,const LString &str);
    friend std::istream& operator>>(std::istream& in,LString &str);
};

template <typename ...Args>
LString LString::format(Args... args){
    std::string str=toStdString();
    const char* cs= m_pData->m_pChar;
    int size = 1+snprintf(nullptr,0,cs,args...);
    char chs[size];
    snprintf(chs,size,cs,args...);
    return LString(chs);
}

#endif
