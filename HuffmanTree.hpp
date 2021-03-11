//
// Logan Mashchak
// Data Structures
// Project 2: Huffman Tree
// 02/05/21
//
/*  Huffman Tree: a templated data structure storing the data in a doubly linked list
 *  with deleted nodes being allocated to the free list for reuse.
 *
 * Functionality:
 * 1. insert a value
 * 2. remove a value
 * 3. search for a value (return iterations found)
 * 4. clear list
 * 5. Print list forward
 * 6. Print list backwards
 * 7. Print status of free list
 *
 */
#ifndef PROJECT2_HUFFMANTREE_H
#define PROJECT2_HUFFMANTREE_H

#include <iostream>
#include <string>

template<class T>
class HuffmanTree
{
public:
    HuffmanTree(int);
    virtual ~HuffmanTree();
    void insertBack(T);
    void insertFront(T);
    int search(T);
    void remove(T);
    void printForward();
    void printBackward();
    void printFreeList();
    int length();
    void clear();

private:
    struct node
    {
        T val;
        int weight;
        bool internal;
        node *left;
        node *right;
        node(T val, int weight)
        {
            this->val = val;
            this->weight = weight;
            left = nullptr;
            right = nullptr;
            internal = false;
        }
        node(int weight)
        {
            this->weight = weight;
            left = nullptr;
            right = nullptr;
            internal = true;
        }
    };

    node *head;
    node *tail;
    node *free_head;
    node *free_tail;

};

template class HuffmanTree<int>;
template class HuffmanTree<unsigned int>;
template class HuffmanTree<char>;
template class HuffmanTree<double>;
template class HuffmanTree<float>;
template class HuffmanTree<std::string>;


#endif
