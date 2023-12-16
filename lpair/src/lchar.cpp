#include"lchar.h"

LLatin1Char::LLatin1Char(){
    m_ch = '\0';
}

LLatin1Char::LLatin1Char(char c){
    m_ch = c;
}

char LLatin1Char::latin1(){
    return m_ch;
}

ushort LLatin1Char::unicode(){
    return (ushort)((uchar)m_ch);
}



LChar::LChar(){
    m_ucs = 0;
}

LChar::LChar(char c){
    m_ucs = (ushort)((uchar)c);
}

LChar::LChar(uchar c){
    m_ucs = (ushort)c;
}

LChar::LChar(short rc){
    m_ucs = (ushort)rc;
}

LChar::LChar(ushort rc){
    m_ucs = rc;
}

LChar::LChar(int rc){
    m_ucs = (ushort)(rc & 0xffff);
}

LChar::LChar(uint rc){
    m_ucs = (ushort)(rc & 0xffff);
}

LChar::LChar(char* ch){
    utf8ToUnicodeOne(ch, &m_ucs);
}

LChar::LChar(LLatin1Char rc){
    m_ucs = rc.unicode();
}

ushort LChar::unicode() const{
    return m_ucs;
}

uchar LChar::row() const{
    return uchar((m_ucs>>8)&0xff);
}

uchar LChar::cell() const{
    return uchar(m_ucs&0xff);
}

void LChar::toUtf8(char* ch) const{
    unicodeToUtf8One(m_ucs,ch);
}

bool LChar::isNull() const{
    return m_ucs==0;
}

bool LChar::isLetter() const{
    return (m_ucs >= 'A' && m_ucs <= 'z' && (m_ucs >= 'a' || m_ucs <= 'Z'));
}

bool LChar::isNumber() const{
    return (m_ucs >= '0' && m_ucs <= '9');
}

bool LChar::isSpace() const{
    return (m_ucs == 0x20 || (m_ucs<=0x0d && m_ucs>=0x09) || (m_ucs==0x85 || m_ucs==0xa0));
}

bool LChar::isNonCharacter() const{
    return (m_ucs>=0xfdd0 && (m_ucs<=0xfdef || (m_ucs & 0xfffe)==0xfffe));
}

bool LChar::isChinese() const{
    return ((m_ucs>=0x4e00 && m_ucs<=0x9fff) || (m_ucs>=0x3400 && m_ucs<=0x4dbf) || (m_ucs>=0x20000 && m_ucs<=0x2a6df) || (m_ucs>=0x2a700 && m_ucs<=0x2b738) || (m_ucs>=0x2b740 && m_ucs<=0x2b81d) || (m_ucs>=0x2b820 && m_ucs<=0x2cea1) || (m_ucs>=0x2ceb0 && m_ucs<=0x2ebe0) || (m_ucs>=0x30000 && m_ucs<=0x3134a) || (m_ucs>=0xf900 && m_ucs<=0xfaff) || (m_ucs>=0x2f800 && m_ucs<=0x2fa1f) || (m_ucs>=0x2f00 && m_ucs<=0x2fdf) || (m_ucs>=0x2e80 && m_ucs<=0x2eff) || (m_ucs>=0x31c0 && m_ucs<=0x31ef));
}

int LChar::compare(const LChar c) const{
    return (m_ucs==(c.unicode())?0:(m_ucs<c.unicode()?-1:1));
}

bool LChar::operator<(const LChar c) const{
    return compare(c)==-1?true:false;
}

bool LChar::operator>(const LChar c) const{
    return compare(c)==1?true:false;
}

bool LChar::operator==(const LChar c) const{
    return compare(c)==0?true:false;
}

LChar& LChar::operator=(uchar c){
    m_ucs = (ushort)c;
    return *this;
}

LChar& LChar::operator=(const LChar& c){
    m_ucs = c.unicode();
    return *this;
}


int LChar::getUtf8CharSize(const char* pChar){
    uchar c = *((uchar*) pChar);
    if(c < 0x80)
        return 1;
    if(c >= 0x80 && c < 0xC0)
        return -1;
    if(c >= 0xC0 && c < 0xE0)
        return 2;
    if(c >= 0xE0 && c < 0xF0)
        return 3;
    if(c >= 0xF0 && c < 0xF8)
        return 4;
    if(c >= 0xF8 && c < 0xFC)
        return 5;
    if(c >= 0xFC)
        return 6;
}

int LChar::utf8ToUnicodeOne(const char* pChar, ushort* pUni){
    if(!pChar || !pUni){
        return 0;
    }
    char b1,b2,b3,b4,b5,b6;
    *pUni = 0x0;
    int byteSize = getUtf8CharSize(pChar);
    char* pOut = (char*)pUni;
    switch (byteSize){
        case 1:
            *pOut = *pChar;
            break;
        case 2:
            b1 = *pChar;
            b2 = *(pChar+1);
            if((b2 & 0xE0) != 0x80){
                return 0;
            }
            *(pOut) = (b1<<6) + (b2 & 0x3F);
            *(pOut+1) = (b1>>2) & 0x07;
            break;
        case 3:
            b1 = *pChar;
            b2 = *(pChar+1);
            b3 = *(pChar+2);
            if((b2 & 0xC0) != 0x80 || ((b3 & 0xC0) != 0x80)){
                return 0;
            }
            *(pOut) = (b2<<6) + (b3 & 0x3F);
            *(pOut+1) = (b1<<4) + ((b2>>2) & 0x0F);
            break;
        default:
            return 0;
            break;
    }
    return byteSize;
}

int LChar::unicodeToUtf8One(ushort pUni, char* pChar){
    if (pUni <= 0x7F) { 
        *pChar = (pUni & 0x7F); 
        return 1; 
    } 
    else if (pUni >= 0x80 && pUni <= 0x7FF) { 
        *(pChar+1) = (pUni & 0x3F) | 0x80; 
        *pChar     = ((pUni >> 6) & 0x1F) | 0xC0; 
        return 2; 
    } 
    else if (pUni >= 0x800 && pUni <= 0xFFFF) {
        *(pChar+2) = (pUni & 0x3F) | 0x80; 
        *(pChar+1) = ((pUni >>  6) & 0x3F) | 0x80; 
        *pChar     = ((pUni >> 12) & 0x0F) | 0xE0; 
        return 3; 
    } 

    return 0;
}

std::ostream& operator<<(std::ostream& out,const LChar &ch){
    char buf[6] = {0};
    ch.toUtf8(buf);
    out<<buf;
    return out;
}

std::istream& operator>>(std::istream& in,LChar &ch){
    char buf = '\0';
    in>>buf;
    ch = buf;
    return in;
}