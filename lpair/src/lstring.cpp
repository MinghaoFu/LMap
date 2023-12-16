#include"lstring.h"

LLatin1String::LLatin1String (){
    m_pData = nullptr;
    m_size = 0;
}

LLatin1String::LLatin1String (const char* str){
    m_pData = str;
    m_size = (int)strlen(str);
}

LLatin1String::LLatin1String (const char* str,int len){
    m_pData = str;
    m_size = len;
}

const char* LLatin1String::latin1 (){
    return m_pData;
}

int LLatin1String::size () const{
    return m_size;
}

LLatin1Char LLatin1String::at (int index){
    return LLatin1Char(*(m_pData+index));
}

LLatin1Char LLatin1String::operator[] (int index){
    return LLatin1Char(*(m_pData+index));
}

LLatin1String LLatin1String::substr (int index ,int len){
    return LLatin1String(m_pData+index,len);
}

int LLatin1String::compare (const char* str){
    return strcmp(m_pData,str);
}

int LLatin1String::compare (LLatin1String &str){
    return strcmp(m_pData,str.latin1());
}

int LLatin1String::compare (LString &str){
    return strcmp(m_pData,str.toConstChar());
}

bool LLatin1String::operator == (const char* str){
    return compare(str)==0;
}

bool LLatin1String::operator == (LLatin1String &str){
    return compare(str)==0;
}

bool LLatin1String::operator == (LString &str){
    return compare(str)==0;
}

bool LLatin1String::operator < (const char* str){
    return compare(str)==-1;
}

bool LLatin1String::operator < (LLatin1String &str){
    return compare(str)==-1;
}

bool LLatin1String::operator < (LString &str){
    return compare(str)==-1;
}

bool LLatin1String::operator > (const char* str){
    return compare(str)==1;
}

bool LLatin1String::operator > (LLatin1String &str){
    return compare(str)==1;
}

bool LLatin1String::operator > (LString &str){
    return compare(str)==1;
}



LString::LString(){
    m_pData = new struct LStringDataStruct;
    m_pData->m_pLChar = new LChar('\0');
    m_pData->m_size = 0;
    transLStringToConstChar();
}

LString::LString(const char * s){
    m_pData = new struct LStringDataStruct;
    m_pData->m_size = strToLCharStrSize(s);
    m_pData->m_pLChar = toLCharArray(s);
    transLStringToConstChar();
}

LString::LString(LLatin1String &s){
    m_pData = new struct LStringDataStruct;
    const char* tmp = s.latin1();
    m_pData->m_size = strToLCharStrSize(tmp);
    m_pData->m_pLChar = toLCharArray(tmp);
    transLStringToConstChar();
}

LString::LString(std::string& s){
    m_pData = new struct LStringDataStruct;
    const char* tmp = s.c_str();
    m_pData->m_size = strToLCharStrSize(tmp);
    m_pData->m_pLChar = toLCharArray(tmp);
    transLStringToConstChar();
}

LString::LString(LChar ch ,int num){
    m_pData = new struct LStringDataStruct;
    m_pData->m_pLChar = new LChar[num+1];
    for(int i=0;i<num;i++){
        *(m_pData->m_pLChar+i) = ch;
    }
    *(m_pData->m_pLChar+num) = LChar('\0');
    m_pData->m_size = num;
    transLStringToConstChar();
}

LString::LString(const LString& s){
    m_pData = new struct LStringDataStruct;
    const char* tmp = s.toConstChar();
    m_pData->m_size = strToLCharStrSize(tmp);
    m_pData->m_pLChar = toLCharArray(tmp);
    transLStringToConstChar();
}

LString::~LString(){
    delete[] m_pData->m_pLChar;
    delete[] m_pData->m_pChar;
    delete m_pData;
}

int LString::compare(const char* s){
    return strcmp(m_pData->m_pChar,s);
}

int LString::compare(LLatin1String &s){
    return strcmp(m_pData->m_pChar,s.latin1());
}

int LString::compare(const LString& s){
    return strcmp(m_pData->m_pChar,s.toConstChar());
}

bool LString::operator<(const char* s){
    return compare(s)<0;
}

bool LString::operator<(LLatin1String &s){
    return compare(s)<0;
}

bool LString::operator<(const LString& s){
    return compare(s)<0;
}

bool LString::operator>(const char* s){
    return compare(s)>0;
}

bool LString::operator>(LLatin1String &s){
    return compare(s)>0;
}

bool LString::operator>(const LString& s){
    return compare(s)>0;
}

bool LString::operator==(const char* s){
    return compare(s)==0;
}

bool LString::operator==(LLatin1String &s){
    return compare(s)==0;
}

bool LString::operator==(const LString& s){
    return compare(s)==0;
}

LString& LString::operator=(const char* s){
    m_pData->m_size = strToLCharStrSize(s);
    m_pData->m_pLChar = toLCharArray(s);
    transLStringToConstChar();
    return *this;
}

LString& LString::operator=(LLatin1String& s){
    m_pData->m_size = strToLCharStrSize(s.latin1());
    m_pData->m_pLChar = toLCharArray(s.latin1());
    transLStringToConstChar();
    return *this;
}

LString& LString::operator=(const LString& s){
    m_pData->m_size = strToLCharStrSize(s.toConstChar());
    m_pData->m_pLChar = toLCharArray(s.toConstChar());
    transLStringToConstChar();
    return *this;
}

LChar LString::at(int index){
    if(index>=0 && index<m_pData->m_size){
        return *(m_pData->m_pLChar+index);
    }
    return LChar();
}

LChar LString::operator[](int index){
    if(index>=0 && index<m_pData->m_size){
        return *(m_pData->m_pLChar+index);
    }
    return LChar();
}

void LString::insert(int pos,const char* s){
    if(pos<0 || pos>m_pData->m_size){
        return;
    }

    int len = strToLCharStrSize(s);
    m_pData->m_size = m_pData->m_size+len;
    LChar* lc = new LChar[m_pData->m_size+1];

    for(int i=0;i<pos;i++){
        *(lc+i) = *(m_pData->m_pLChar+i);
    }

    int charSize = 0;
    for(int i=pos,j=0;i<(pos+len);i++){
        ushort tempShort = 0;
        charSize = LChar::utf8ToUnicodeOne(s+j,&tempShort);
        *(lc+i) = LChar(tempShort);
        j += charSize;
    }
    
    for(int i=pos+len;i<m_pData->m_size;i++){
        *(lc+i) = *(m_pData->m_pLChar+i-len);
    }

    delete[] m_pData->m_pLChar;
    m_pData->m_pLChar = lc;
    transLStringToConstChar();
}

void LString::insert(int pos,LLatin1String &s){
    insert(pos,s.latin1());
}

void LString::insert(int pos,const LString& s){
    insert(pos,s.toConstChar());
}

void LString::prepend(const char* s){
    insert(0,s);
}

void LString::prepend(LLatin1String &s){
    insert(0,s);
}

void LString::prepend(const LString& s){
    insert(0,s);
}

void LString::append(const char* s){
    insert(m_pData->m_size,s);
}

void LString::append(LLatin1String &s){
    insert(m_pData->m_size,s);
}

void LString::append(const LString& s){
    insert(m_pData->m_size,s);
}

void LString::trim(){
    if(m_pData->m_pLChar==nullptr){
        return;
    }
    int l,r;
    for(l=0;l<m_pData->m_size;l++){
        if(!(m_pData->m_pLChar+l)->isSpace())
            break;
    }
    for(r=m_pData->m_size-1;r>l;r--){
        if(!(m_pData->m_pLChar+r)->isSpace())
            break;
    }
    int len = r-l+1;
    LChar* tmp = new LChar[len+1];
    m_pData->m_size = len;
    if(len!=0){
        for(int i=l;i<=r;i++){
            *(tmp+i-l) = *(m_pData->m_pLChar+i);
        }
    }
    delete[] m_pData->m_pLChar;
    m_pData->m_pLChar = tmp;
    *(m_pData->m_pLChar+len) = LChar('\0');
    transLStringToConstChar();
}

void LString::replace(const LString &s1, const LString &s2){
    std::string str = toStdString();
    std::string temp1 = s1.toStdString();
    std::string temp2 = s2.toStdString();
    int index = 0;

    for(int i=0;i<lCharStrToStrSize();i+=temp2.length()){
        index = str.find(temp1,i);
        i = index;
        if(index==std::string::npos){
            break;
        }
        str.replace(index,temp1.length(),temp2);
    }

    delete[] m_pData->m_pLChar;
    m_pData->m_size = strToLCharStrSize(str.c_str());
    m_pData->m_pLChar = toLCharArray(str.c_str());
    transLStringToConstChar();
}

void LString::erase(int pos, int num){
    if(pos<0 || pos+num>m_pData->m_size){
        return;
    }
    m_pData->m_size = m_pData->m_size-num;
    LChar* tmp = new LChar[m_pData->m_size+1];
    for(int i=0;i<pos;i++){
        *(tmp+i) = *(m_pData->m_pLChar+i);
    }
    for(int i=pos;i<m_pData->m_size;i++){
        *(tmp+i) = *(m_pData->m_pLChar+i+num);
    }
    delete[] m_pData->m_pLChar;
    m_pData->m_pLChar = tmp;
    transLStringToConstChar();
}

bool LString::isEmpty(){
    return m_pData->m_size==0;
}

int LString::indexOf(LChar ch){
    for(int i=0;i<m_pData->m_size;i++){
        if(*(m_pData->m_pLChar+i)==ch){
            return i;
        }
    }
    return -1;
}

int LString::lastIndexOf(LChar ch){
    for(int i=m_pData->m_size-1;i>=0;i--){
        if(*(m_pData->m_pLChar+i)==ch){
            return i;
        }
    }
    return -1;
}

int LString::length() const{
    return m_pData->m_size;
}

int LString::toInt(int base){
    return (std::stoi(toStdString(),0,base));
}

uint LString::toUInt(int base){
    return (std::stoul(toStdString(),0,base));
}

long LString::toLong(int base){
    return (std::stol(toStdString(),0,base));
}

ulong LString::toULong(int base){
    return (std::stoul(toStdString(),0,base));
}

longlong LString::toLongLong(int base){
    return (std::stoll(toStdString(),0,base));
}

ulonglong LString::toULongLong(int base){
    return (std::stoull(toStdString(),0,base));
}

float LString::toFloat(){
    return (std::stof(toStdString(),0));
}

double LString::toDouble(){
    return (std::stod(toStdString(),0));
}

long double LString::toLongDouble(){
    return (std::stold(toStdString(),0));
}

LString LString::toUpper(){
    int strSize = lCharStrToStrSize();
    const char* tmp = m_pData->m_pChar;
    char ch[strSize+1] = {0};

    int charSize = 0;
    for(int i=0;i<strSize;){
        charSize = LChar::getUtf8CharSize(tmp+i);
        if(charSize == 1){
            if(*(tmp+i)>=0x61 && *(tmp+i)<=0x7a){
                *(ch+i) = *(tmp+i)-32;
            }
            else{
                *(ch+i) = *(tmp+i);
            }
        }
        else{
            for(int j=0;j<charSize;j++){
                *(ch+i+j) = *(tmp+i+j);
            }
        }
    }
    *(ch+strSize) = '\0';
    return LString(ch);
}

LString LString::toLower(){
    int strSize = lCharStrToStrSize();
    const char* tmp = m_pData->m_pChar;
    char ch[strSize+1] = {0};

    int charSize = 0;
    for(int i=0;i<strSize;){
        charSize = LChar::getUtf8CharSize(tmp+i);
        if(charSize == 1){
            if(*(tmp+i)>=0x41 && *(tmp+i)<=0x5a){
                *(ch+i) = *(tmp+i)+32;
            }
            else{
                *(ch+i) = *(tmp+i);
            }
        }
        else{
            for(int j=0;j<charSize;j++){
                *(ch+i+j) = *(tmp+i+j);
            }
        }
    }
    *(ch+strSize) = '\0';
    return LString(ch);
}

std::string LString::toStdString() const{
    return std::string(m_pData->m_pChar);
}

const char* LString::toConstChar() const{
    return m_pData->m_pChar;
}

int LString::endian(){
    int i = 1;
    char* p = (char*)&i;
    if(*p == 1){
        return 0;
    }
    else{
        return 1;
    }
}

int LString::strToLCharStrSize(const char* s){
    if(!s){
        return 0;
    }
    int sizeLCharStr = 0;
    const char* pChar = s;
    for(int i=0;i<strlen(s);){
        int tmp = LChar::getUtf8CharSize(pChar);
        pChar += tmp;
        i += tmp;
        sizeLCharStr += 1;
    }
    return sizeLCharStr;
}

int LString::lCharStrToStrSize(){
    if(!(m_pData->m_pLChar)){
        return 0;
    }
    int sizeStr = 0;
    const LChar* pChar = m_pData->m_pLChar;
    LChar tmp = LChar('\0');
    for(int i=0;i<m_pData->m_size;i++){
        if(pChar->unicode() <= 0x7F){
            sizeStr += 1;
        }
        else if(pChar->unicode() <= 0x7FF && pChar->unicode() >= 0x80){
            sizeStr += 2;
        }
        else if(pChar->unicode() <= 0xFFFF && pChar->unicode() >= 0x800){
            sizeStr += 3;
        }
        pChar ++;
    }
    return sizeStr;
}

LChar* LString::toLCharArray(const char* s){
    int sizeLCharStr = m_pData->m_size;
    const char* pChar = s;
    LChar* tempLChar=new LChar[sizeLCharStr+1];

    for(int i=0;i<sizeLCharStr;i++){
        ushort tempShort = 0;

        int charSize = LChar::getUtf8CharSize(pChar);
        LChar::utf8ToUnicodeOne(pChar, &tempShort);
        pChar += charSize;
        
        *(tempLChar+i) = LChar(tempShort);
    }
    *(tempLChar+sizeLCharStr) = LChar('\0');
    return tempLChar;
}

void LString::transLStringToConstChar(){
    int strSize = lCharStrToStrSize();
    char* buf= new char[strSize+1];
    delete[] m_pData->m_pChar;
    if(m_pData->m_pLChar!=nullptr){
        for(int i=0,j=0;i<m_pData->m_size;i++){
            int charSize = LChar::unicodeToUtf8One((m_pData->m_pLChar+i)->unicode(),(buf+j));
            j += charSize;
        }
    }
    *(buf+strSize) = '\0';
    m_pData->m_pChar = buf;
}




std::ostream& operator<<(std::ostream& out,const LString &str){
    out<<str.toConstChar();
    return out;
}

std::istream& operator>>(std::istream& in,LString &str){
    char buf[2048] = {0};
    in>>buf;
    str.m_pData->m_size = str.strToLCharStrSize(buf);
    str.m_pData->m_pLChar = str.toLCharArray(buf);
    str.transLStringToConstChar();
    return in;
}
