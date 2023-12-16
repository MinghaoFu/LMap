#include <iostream>
#include "lmap.h"
#include "lchar.h"
#include "lstring.h"

int main(int argc, const char * argv[]) {
    {
        LMap<int, int> m;
        for (int i = 0; i < 10; i++) {
            m[i] = i;
        }
        LMap<int, int> n(m.rBegin(), m.rEnd());
        std::cout << "Print by order, testing constructor: " << std::endl;
        for (LMap<int, int>::iterator it = n.begin(); it != n.end(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        }
    }
    
    {
        LMap<int, int> m;
        for (int i = 0; i < 10; i++) {
            m[i] = i;
        }
        std::cout << "Print by order, using iterator: " << std::endl;
        for (LMap<int, int>::iterator it = m.begin(); it != m.end(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        }
    }
    
    {
        LMap<LChar, int> n;
        for (int i = 0; i < 10; i++) {
            n['a' + i ] = i;
        }
        std::cout << "Print by order, using reverse iterator: " << std::endl;
        for (LMap<LChar, int>::reverse_iterator it = n.rBegin(); it != n.rEnd(); it++) {
            std::cout << "    Key: " << it->key() << " Value: " << it->value() << std::endl;
        }
    }
    
    {
        LMap<int, int> m;
        for (int i = 0; i < 10; i++) {
            m[i] = i;
        }
        std::cout << "Test size(): " << (m.size() == 10 ? "true" : "false") <<  std::endl;
        m.clear();
        std::cout << "Test clear() and empty(): " << (m.empty() ? "true" : "false") << std::endl;
        for (int i = 0; i < 10; i++) {
            m[i] = i;
        }
        std::cout << "lowerBound(5): " << m.lowerBound(5)->key() << std::endl;
        std::cout << "upperBound(5): " << m.upperBound(5)->key() << std::endl;
        LMap<int, int> n;
        for (int i = 0; i < 10; i++) {
            n[i] = i;
        }
        std::cout << "Test operator overload: " << (m == n ? "true" : "false") << std::endl;
    }
}
