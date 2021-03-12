
#include <iostream>
#include <cstring>
#include "HuffmanTree.hpp"

int main()
{

    std::string o = "bourgpppppeoisie";
    // std::string o = "poopies";
    HuffmanTree tree(o);
    std::cout << "\n\n";
    tree.printPreOrder();
    return 0;
}
