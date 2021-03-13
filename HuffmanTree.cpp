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
 * 1. search for a value (returns binary encoding)
 * 2. Print chart of encoding
 *
 */
#include "HuffmanTree.hpp"
#include <bitset>

int bitcount = 0;
HuffmanTree::HuffmanTree(std::string o)
{
    original = o;
    int i = 0;
    int j = 0;
    int k = 0;

    while (o[i] != '\0')
    {
        i++;

    }

    int size = i;
    WeightMap map[size];
    i = 0;

    while (o[i] != '\0')
    {
        if (o[i] != '\t') {
            map[k].name = o[i];
            map[k].weight = 1;
            j = i + 1;
            while (o[j] != '\0'){
                if(o[j] == map[k].name) {
                    map[k].weight++;
                    o[j] = '\t';
                }
                j++;
            }
            k++;
            map[k].name = '\0';
        }
        o[i] = '\t';
        
        //std::cout << '\n' << o;
        i++;

    }
    int length = k;
    
    i = 0;
    for (int i = 0; i < length; i++)
    {
        node *newNode = new node(map[i].weight, map[i].name);
        nodeQueue[i] = newNode;
    }
    insertionSort(nodeQueue, length);
    while (map[i].name != '\0'){
        std::cout << nodeQueue[i]->name;
        i++;
    }
    i = 0;
    std::cout << '\n';
    while (map[i].name != '\0'){
        std::cout << nodeQueue[i]->weight;
        i++;
    }

    int n = 0;
    root = nullptr;
    while (nodeQueue[1]->weight != 1000){
        node* newNodeLeft = nodeQueue[0];
        node* newNodeRight = nodeQueue[1];
        node* newNodeAgg = new node(nodeQueue[0]->weight + nodeQueue[1]->weight);
        newNodeAgg->left = newNodeLeft;
        newNodeAgg->right = newNodeRight;
        node* temp = newNodeAgg;
        if (nodeQueue[2]->weight == 1000){
            root = newNodeAgg;
        }

        nodeQueue[0] = newNodeAgg;
        nodeQueue[1] = new node(1000);
        insertionSort(nodeQueue, length);
    }
}

void HuffmanTree::printPreOrder()
{
    outputPreOrder(root);
}

void HuffmanTree::outputPreOrder(node* aNode){
    if (aNode != nullptr){
        if (aNode->internal)
        {   
            std::cout << aNode->weight << " ";
        } else {
            std::cout << aNode->weight << '|' << aNode->name << " ";
        }
        outputPreOrder(aNode->left);
        outputPreOrder(aNode->right);
        
    }
}

std::string HuffmanTree::search(char c)
{
    std::string path = "0";
    std::string absolute = "not found";
    find(root, c, path, absolute);
    return absolute;
}

void HuffmanTree::find(node* aNode, char c, std::string path, std::string& absolute)
{
	if (aNode == root) {
		find(aNode->left, c, ("0"), absolute);
		find(aNode->right, c, ("1"), absolute);
	} else {
		std::cout << '\n' << path;
		if(aNode->internal == false){
                std::cout << aNode->name;
			if (aNode->name == c)
				absolute = path;
		} else {
			find(aNode->left, c, (path + '0'), absolute);
			find(aNode->right, c, (path + '1'), absolute);
		}

	}
}

void HuffmanTree::displayChart()
{
    std::string path = "0";
    std::cout << "\n\nHuffman Chart";
    generateChart(root, path);
    std::cout << "\n\n";
}

void HuffmanTree::generateChart(node* aNode, std::string path)
{
    if (aNode == root) {
        generateChart(aNode->left, "0");
        generateChart(aNode->right, "1");
    } else {
        if(aNode->internal == false){
                std::cout << "\n---------------\n";
                std::cout << aNode->name << "   |   "<< path;

        } else {
            generateChart(aNode->left, (path + '0'));
            generateChart(aNode->right, (path + '1'));
        }

    }
}

void HuffmanTree::deepCopy(node* n1, node* n2)
{
    n1->name = n2->name;
    n1->weight = n2->weight;
    n1->left = n2->left;
    n1->right = n2->right;
    n1->internal = n2->internal;
}

void HuffmanTree::insertionSort(node* map[], int size){
    node* key = new node(0, 'h');
    int j;
    for (int i = 1; i < size; i++){
        deepCopy(key, map[i]);
        j = i - 1;
        while(j >= 0  && map[j]->weight > key->weight)
        {
            deepCopy(map[j+1], map[j]);
            j = j - 1;
        }
        deepCopy(map[j+1], key);
    }

    key = nullptr;
    delete key;
}
