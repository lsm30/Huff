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
#include "HuffmanTree.hpp"
#include <bitset>

int bitcount = 0;
HuffmanTree::HuffmanTree(std::string o)
{
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

HuffmanTree::HuffmanTree(char* o)
{
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

int HuffmanTree::search(char c)
{
    int path = 0b0;
    find(root, c, path);
    return path;
}

bool HuffmanTree::find(node* aNode, char c, int path)
{
	if (aNode == root) {
		find(aNode->left, c, (path<<1));
		find(aNode->right, c, (path+1));
	} else {
		std::cout << std::bitset<4>(path) << '\n';
		if(aNode->internal == false){
			if (aNode->name == c)
				std::cout << std::bitset<8>(path);
		} else {
			find(aNode->left, c, (path<<1));
			find(aNode->right, c, ((path<<1) + 1));
		}

	}
	return false;
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
