#ifndef L_LCHAR_H
#define L_LCHAR_H
#include<string>
#include<iostream>
#include<string.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

class LChar;

class LLatin1Char{
private:
    char m_ch;
public:
    LLatin1Char();
    LLatin1Char(char c);
    char latin1();
    ushort unicode();
};

class LChar{
private:
    ushort m_ucs;
public:
    LChar();
    LChar(char c);
    LChar(uchar c);
    LChar(short rc);
    LChar(ushort rc);
    LChar(int rc);
    LChar(uint rc);
    LChar(char* ch);
    LChar(LLatin1Char rc);

    ushort unicode() const;
    uchar row() const;
    uchar cell() const;
    void toUtf8(char* ch) const;
    bool isNull() const;
    bool isLetter() const;
    bool isNumber() const;
    bool isSpace() const;
    bool isNonCharacter() const;
    bool isChinese() const;
    int compare(const LChar c) const;
    bool operator<(const LChar c) const;
    bool operator>(const LChar c) const;
    bool operator==(const LChar c) const;
    LChar& operator=(uchar c);
    LChar& operator=(const LChar& c);

    static int getUtf8CharSize(const char* pChar);
    static int utf8ToUnicodeOne(const char* pChar, ushort* pUni);
    static int unicodeToUtf8One(ushort pUni, char* pChar);

    friend std::ostream& operator<<(std::ostream& out,const LChar &ch);
    friend std::istream& operator>>(std::istream& in,LChar &ch);
};

#endif