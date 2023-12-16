#include <iostream>
#include "lmap.h"
#include "lchar.h"
#include "lstring.h"

int main(int argc, const char * argv[]) {
    // 测试构造器
    {
        LMap<int, int> m; // 使用空构造器构造一个LMap对象
        for (int i = 0; i < 10; i++) {
            m[i] = i; // 添加元素
        }
        LMap<int, int> n(m.rBegin(), m.rEnd()); // 使用迭代构造器构造一个LMap对象，复制上一个LMap中的所有元素
        // 输出
        std::cout << "Print by order, testing constructor: " << std::endl;
        for (LMap<int, int>::iterator it = n.begin(); it != n.end(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        } // 如果元素从小到大输出，说明构造成功
    }
    // 测试迭代器
    {
        LMap<int, int> m; // 构造一个空LMap
        for (int i = 0; i < 10; i++) {
            m[i] = i; // 添加元素
        }
        // 输出
        std::cout << "Print by order, using iterator: " << std::endl;
        for (LMap<int, int>::iterator it = m.begin(); it != m.end(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        } // 如果元素从小到大输出，说明迭代器可用
    }
    // 测试反向迭代器，测试LChar作为键值
    {
        LMap<LChar, int> n; // 构造一个空LMap，键值类型为LChar
        // 添加元素
        for (int i = 0; i < 10; i++) {
            n['a' + i ] = i;
        }
        
        // 输出
        std::cout << "Print by order, using reverse iterator: " << std::endl;
        for (LMap<LChar, int>::reverse_iterator it = n.rBegin(); it != n.rEnd(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        } // 如果元素从大到小输出，则说明反向迭代器可用
    }
    // 测试其他成员函数
    {
        LMap<int, int> m; // 构造一个空LMap对象
        for (int i = 0; i < 10; i++) {
            m[i] = i; // 添加元素
        }
        // 测试size()
        std::cout << "Test size(): " << (m.size() == 10 ? "true" : "false") <<  std::endl;

        m.clear(); // 测试clear()
        
        // 测试empty()
        std::cout << "Test clear() and empty(): " << (m.empty() ? "true" : "false") << std::endl;

        // 再次添加元素
        for (int i = 0; i < 10; i++) {
            m[i] = i;
        }
        // 测试lowerBound()
        std::cout << "lowerBound(5): " << m.lowerBound(5)->key() << std::endl;
        // 测试upperBound()
        std::cout << "upperBound(5): " << m.upperBound(5)->key() << std::endl;
        
        // 构造一个空LMap对象
        LMap<int, int> n;
        // 添加元素
        for (int i = 0; i < 10; i++) {
            n[i] = i;
        }
        // 测试==运算符重载
        std::cout << "Test operator overload: " << (m == n ? "true" : "false") << std::endl;
    }
}
