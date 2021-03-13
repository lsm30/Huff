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


struct WeightMap
{
    char name;
    int weight;
};




class HuffmanTree
{
public:
    HuffmanTree(std::string);
    void printPreOrder();
    //virtual ~HuffmanTree();
    std::string search(char);
    void displayChart();
    void clear();
    WeightMap map[26];
private:
    struct node
    {
        char name;
        int weight;
        bool internal;
        node *left;
        node *right;
        node(int weight, char name)
        {
            this->name = name;
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
    std::string original;
    void outputPreOrder(node*);
    node *root;
    node* nodeQueue[100];
    void insertionSort(node**, int);
    void deepCopy(node* n1, node* n2);
    void find(node* aNode, char c, std::string path, std::string& absolute);
    void generateChart(node* aNode, std::string path);

};



#endif
