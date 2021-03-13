
#include <iostream>
#include <cstring>
#include "HuffmanTree.hpp"

int main()
{

    // std::string o = "bourgpppppeoisie";
    std::string o = "cory in the house";
    HuffmanTree tree(o);
    //
    std::cout << "\n\n";
    tree.printPreOrder();

    std::cout << "\n\n\n" << tree.search('s');
    tree.displayChart();
    return 0;
}
