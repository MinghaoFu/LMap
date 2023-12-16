#include <iostream>
#include "lmap.h"
#include "lchar.h"
#include "lstring.h"

int main(int argc, const char * argv[]) {
    // 测试LPair构造器
    LPair<LChar, LString> lp_1('1', "fmh"); // 使用LChar和LString作为LPair并赋值，条件构造
    LPair<int, LString> lp_2; // 使用LChar和LString作为LPair, 默认构造
    LPair<LChar, LString> lp_3 = lp_1; // 使用LChar和LSting作为LPair，复制构造
    // 测试LPair的成员函数访问
    std::cout << "Test LPair constructor and access: " << std::endl; // 输出
    std::cout << "    lp_1 key: " << lp_1.key() << " lp_1 value: " << lp_1.value() << std::endl;
    std::cout << "    lp_2 key: " << lp_2.key() << " lp_2 value: " << lp_2.value() << std::endl;
    std::cout << "    lp_3 key: " << lp_3.key() << " lp_3 value: " << lp_3.value() << std::endl;
    // 测试LPair的运算符重载
    LPair<LChar, LString> lp_4('2', "xdy"); // 使用LChar和LString作为LPair并赋值，条件构造
    LPair<LChar, LString> lp_5('1', "fmh"); // 使用LChar和LString作为LPair并赋值，条件构造
    std::cout << "Test operator overload: " << std::endl; // 输出
    std::cout << "    lp_4 > lp5: " << (lp_4 > lp_5 ? "true" : "false") << std::endl; // 测试运算符>
    std::cout << "    lp_5 < lp4: " << (lp_5 < lp_4 ? "true" : "false") << std::endl; // 测试运算符<
    std::cout << "    lp_5 == lp1: " << (lp_5 == lp_1 ? "true" : "false") << std::endl; // 测试运算符==
    std::cout << "    lp_4 != lp5: " << (lp_4 != lp_5 ? "true" : "false") << std::endl; // 测试运算符!=
    
    
    
}
