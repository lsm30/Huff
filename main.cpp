
#include <iostream>
#include <cstring>
#include "HuffmanTree.hpp"

int main()
{

    std::string o = "bourgpppppeoisie";
    HuffmanTree tree(o);
    //
    std::cout << "\n\n";
    tree.printPreOrder();

    std::cout << "\n\n\n" << tree.search('p');
    return 0;
}
