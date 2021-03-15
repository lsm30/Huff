
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <math.h>
#include <cstring>
#include "HuffmanTree.hpp"

using std::cout;
using std::endl;

//////////////////////// code for treap from fellow student

/*********************************************************************************************
/  Using a struct for the data for the Treap.                                                *
/  Each treap has a key (the data) which will be sorted according to BST properties and a    *
/     priority which will be sorted based on max heap properties. Each treap also has        *
/     pointers to its parent, left child node, and right child node.                         *
*********************************************************************************************/
struct Treap
{
    int key;
    int priority;
    Treap *parent;
    Treap *leftChild;
    Treap *rightChild;
};

/*********************************************************************************************
/  Functions                                                                                 *
*********************************************************************************************/
Treap *rotateTreap(char dir, Treap *treap);
Treap *ins(int insertKey, Treap* treapRoot);
Treap *del(int delData, Treap *treap);
void printTreap(Treap *treap);


/*********************************************************************************************
/                                                                                            *
/                                    FUNCTIONS                                               *
/                                                                                            *
*********************************************************************************************/

/*********************************************************************************************
/  Create the Treap node. Generate a random priority between 1-100 to assign to it.          *
/  Set parent, leftChild, and rightChild pointers to the null pointer.                       *
/  Assign key value given by user.                                                           *
/  Given: key to insert as an int                                                            *
/  Returns: newly created treap node                                                         *
*********************************************************************************************/
Treap *createTreapNode(int key)
{
    int insertPriority = rand() % 100;
    Treap* treapNode = new Treap;
    treapNode->key = key;
    treapNode->priority = insertPriority;
    treapNode->parent = nullptr;
    treapNode->leftChild = nullptr;
    treapNode->rightChild = nullptr;
}

/*********************************************************************************************
/  Rotate treap. Used for sorting on insert and for deleting.                                *
/  Given: char dir: direction to rotate, 'L' for left and 'R' for right                      *
/         treap node to perform operation on                                                 *
/  returns: treap node with new rotation                                                     *
*********************************************************************************************/
Treap *rotateTreap(char dir, Treap *nodeToRotate)
{
    Treap *newRoot;
    if(dir == 'L')
    {
        newRoot = nodeToRotate->rightChild;
        Treap *tempNode = newRoot->leftChild;
        newRoot->leftChild = nodeToRotate;
        nodeToRotate->rightChild = tempNode;
    }
    else if(dir == 'R')
    {
        newRoot = nodeToRotate->leftChild;
        Treap *tempNode = newRoot->rightChild;
        newRoot->rightChild = nodeToRotate;
        nodeToRotate->leftChild = tempNode;
    }
    return newRoot;
}

/*********************************************************************************************
/ Insert function                                                                            *
/ create a random priority to assign to the new node of the treap                            *
/ sort based on BST and max heap properties using rotate treap function until the treap      *
/     fits requirements for both. Recursively call until new value is sorted correctly.      *
/ Given: key we will be inserting as int, treap we will be inserting our key into            *
/ Returns: treap with correctly sorted pointers to other treap nodes                         *
*********************************************************************************************/
Treap *ins(int insertKey, Treap* treapRoot)
{
    int insertPriority;
    insertPriority = rand() % 100;
    if (treapRoot == NULL)
    {
      return(createTreapNode(insertKey));
    }
    else if (insertKey <= treapRoot->key)
    {
        treapRoot->leftChild = ins(insertKey, treapRoot->leftChild);
        if(treapRoot->leftChild->priority > treapRoot->priority)
        {
            treapRoot = rotateTreap('R', treapRoot);
        }
    }
    else
    {
        treapRoot->rightChild = ins(insertKey, treapRoot->rightChild);
        if(treapRoot->rightChild->priority > treapRoot->priority)
        {
            treapRoot = rotateTreap('L', treapRoot);
        }
    }
  return treapRoot;
}

/*********************************************************************************************
/ Delete function                                                                            *
/ Find the key we want to delete, rotate it to the end until it has no children.             *
/     then, delete it. If it's already a leaf node, no rotations need to be done.            *
/     Delete function is recursively called until we are able to delete the requested data   *
/ Given: key to delete as int                                                                *
/ Returns: treap with requested treap removed                                                *
*********************************************************************************************/
Treap *del(int delData, Treap* treap)
{
    if(!treap)
    {
        return treap;
    }
    else if(delData < treap->key)
    {
        treap->leftChild = del(delData, treap->leftChild);
    }
    else if(delData > treap->key )
    {
        treap->rightChild = del(delData, treap->rightChild);
    }


    else if(!(treap->leftChild))
    {
        Treap *newRoot = treap->rightChild;
        delete(treap);
        treap = newRoot;
    }
    else if(!(treap->rightChild) )
    {
        Treap *newRoot = treap->leftChild;
        delete(treap);
        treap = newRoot;
    }


    else if(treap->leftChild->priority < treap->rightChild->priority)
    {
        treap = rotateTreap('L', treap);
        treap->leftChild = del(delData, treap->leftChild);
    }
    else
    {
        treap = rotateTreap('R', treap);
        treap->rightChild = del(delData, treap->rightChild);
    }
    return treap;
}

/*********************************************************************************************
/  Prints each node of the treap passed to it and its left and right children, if it has any *
/  Print is formated as:                                                                     *
/                   parentNode(priority)                                                     *
/     leftChild(priority)       rightChild(priority)                                         *
/  for each node.                                                                            *
*********************************************************************************************/
void printTreap(Treap *treap)
{
    if (treap)
    {
        printTreap(treap->leftChild);
        cout << "       " << treap->key << "(p" << treap->priority << ")" << endl;
        if (treap->leftChild)
        {
            cout << treap->leftChild->key << "(p" << treap->leftChild->priority << ")";
        }
        if (treap->rightChild)
        {
            cout << "           " << treap->rightChild->key << "(p" << treap->rightChild->priority << ")\n";
        }
        cout << endl << "------------------"  << endl;
        printTreap(treap->rightChild);
    }
}



void test1()
{

    Treap *treap = NULL;
    std::string thou = "7nKsmbar8qo2r3dvIVXAbcEcvMPnO5cBAwhuAZ8WXE3xpalCDB7jJ5zWn0zy561CyvqFK30uEyTsASjEghgcoNupCC7ttM99bus7mlAB4d9BpBPk6pc0pfJGjt4d7bjpo6ChJS0YoLQhVcDnlYln8qTkrRZbTjRYFP9KEfI7CB82l4CtwVj3BHvQAd5oIDBFfmZ0a33x1f8j8coWdsygv3RZopEjdIUugpKkRYakpjXOVdnUOOqOQDcoJRDaGlSsF3SaZg5mki2MNAhfQXAsEcu2EVIPWVxCBEorRhmZy1vlispT3C5TGpbaBvMzawfyAp1gzHK7WTTmX0CsbM00xt2HJbRjBy6Zxr1YgN8UKR15WJ0ELvJYoVN7tTeZV1Uzv0AFnFz2BmM0HIc0Quq6sRg8AxCc0R8jXS2l6awB14WiDrHxDSlCZeeZOYnmlhn5oOWUdXLDfMiIYPUNLI328gIW5CgSRpz9JhYFU0xRTxEKq3ArbXbDk7z05c0pKQEaGXwHvTlp9Hgpyg3zznNP1Gz3boUvbZ4nNaKxratVhuLEFsD9BjXCQz2mnxOQRbhRhzOtUjMuU4NkOm58rvLKiroihHJomQcNlxwynZAg0hWWRCu7ZMlYXj4k13wMOjnhH6PrxnnEofgBPyyJOjUoQV8KemY1NmYifmxEjhht3iXATwBtNfycuKDJtZUh2SxicxyJV43ttwA4wcq2t9IFpHxjwbYMNVryh3d5rNDax9fAZLsvBKlhnlEOjOlrJARND8tShpkNTXEwc2RZBemUKbpBMtxnxDWNYcJph2o0hxNs1zP4pXbuYpqFegKzZkVytfcdZIBiWOQ4EGAC2BCqxMc3mXRdUveEqOf8LvQBg6LuoPmuUegrlYlZMKwfjiLGz0CbNnK1qhb3BnqsDH14vUr59dHSqwhwOciwdQCaS1uALxJEwrsdqxhuvjTEY1m7hCJgdRel842Z1vL5iWPu8batnayqV57wYViI6mpi";
    int testQuantity = 1000;
    std::string tenthou = thou;

    // creating the strings
    for(int i = 0; i < 9; i++)
    {
        tenthou.append(thou);
    }

    std::string hundthou = tenthou;
    for(int i = 0; i < 9; i++)
    {
        hundthou.append(tenthou);
    }

    std::string mil = hundthou;
    for(int i = 0; i < 9; i++)
    {
        mil.append(hundthou);
    }

    clock_t timer = clock();
    HuffmanTree test(thou);
    timer = clock() - timer;
    cout << "Huff 1000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    HuffmanTree test1(tenthou);
    timer = clock() - timer;
    cout << "Huff 10000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    HuffmanTree test2(hundthou);
    timer = clock() - timer;
    cout << "Huff 100000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    HuffmanTree test3(mil);
    timer = clock() - timer;
    cout << "Huff 1M: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    for(int i = 0; i < 1000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 1000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    for(int i = 0; i < 10000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 10000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    for(int i = 0; i < 100000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 100000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    for(int i = 0; i < 1000000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 1M: " << (float)timer / CLOCKS_PER_SEC << endl;

}

void test2()
{

    Treap *treap = NULL;
    std::string thou = "7nKsmbar8qo2r3dvIVXAbcEcvMPnO5cBAwhuAZ8WXE3xpalCDB7jJ5zWn0zy561CyvqFK30uEyTsASjEghgcoNupCC7ttM99bus7mlAB4d9BpBPk6pc0pfJGjt4d7bjpo6ChJS0YoLQhVcDnlYln8qTkrRZbTjRYFP9KEfI7CB82l4CtwVj3BHvQAd5oIDBFfmZ0a33x1f8j8coWdsygv3RZopEjdIUugpKkRYakpjXOVdnUOOqOQDcoJRDaGlSsF3SaZg5mki2MNAhfQXAsEcu2EVIPWVxCBEorRhmZy1vlispT3C5TGpbaBvMzawfyAp1gzHK7WTTmX0CsbM00xt2HJbRjBy6Zxr1YgN8UKR15WJ0ELvJYoVN7tTeZV1Uzv0AFnFz2BmM0HIc0Quq6sRg8AxCc0R8jXS2l6awB14WiDrHxDSlCZeeZOYnmlhn5oOWUdXLDfMiIYPUNLI328gIW5CgSRpz9JhYFU0xRTxEKq3ArbXbDk7z05c0pKQEaGXwHvTlp9Hgpyg3zznNP1Gz3boUvbZ4nNaKxratVhuLEFsD9BjXCQz2mnxOQRbhRhzOtUjMuU4NkOm58rvLKiroihHJomQcNlxwynZAg0hWWRCu7ZMlYXj4k13wMOjnhH6PrxnnEofgBPyyJOjUoQV8KemY1NmYifmxEjhht3iXATwBtNfycuKDJtZUh2SxicxyJV43ttwA4wcq2t9IFpHxjwbYMNVryh3d5rNDax9fAZLsvBKlhnlEOjOlrJARND8tShpkNTXEwc2RZBemUKbpBMtxnxDWNYcJph2o0hxNs1zP4pXbuYpqFegKzZkVytfcdZIBiWOQ4EGAC2BCqxMc3mXRdUveEqOf8LvQBg6LuoPmuUegrlYlZMKwfjiLGz0CbNnK1qhb3BnqsDH14vUr59dHSqwhwOciwdQCaS1uALxJEwrsdqxhuvjTEY1m7hCJgdRel842Z1vL5iWPu8batnayqV57wYViI6mpi";
    int testQuantity = 1000;
    std::string tenthou = thou;

    // creating the strings
    for(int i = 0; i < 9; i++)
    {
        tenthou.append(thou);
    }

    std::string hundthou = tenthou;
    for(int i = 0; i < 9; i++)
    {
        hundthou.append(tenthou);
    }

    std::string mil = hundthou;
    for(int i = 0; i < 9; i++)
    {
        mil.append(hundthou);
    }

    clock_t timer = clock();
    // HuffmanTree test(thou);
    // timer = clock() - timer;
    // cout << "Huff 1000: " << (float)timer / CLOCKS_PER_SEC << endl;

    // timer = clock();
    // HuffmanTree test1(tenthou);
    // timer = clock() - timer;
    // cout << "Huff 10000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    HuffmanTree test2(hundthou);
    timer = clock() - timer;
    cout << "Huff 100000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    HuffmanTree test3(mil);
    timer = clock() - timer;
    cout << "Huff 1M: " << (float)timer / CLOCKS_PER_SEC << endl;

    // timer = clock();
    // for(int i = 0; i < 1000; i++)
    // {
    //     treap = ins((rand()%100), treap);
    // }
    // timer = clock() - timer;
    // cout << "Treap 1000: " << (float)timer / CLOCKS_PER_SEC << endl;

    // timer = clock();
    // for(int i = 0; i < 10000; i++)
    // {
    //     treap = ins((rand()%100), treap);
    // }
    // timer = clock() - timer;
    // cout << "Treap 10000: " << (float)timer / CLOCKS_PER_SEC << endl;
    //test2.clear();
    test3.clear();
    timer = clock();
    for(int i = 0; i < 100000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 100000: " << (float)timer / CLOCKS_PER_SEC << endl;

    timer = clock();
    for(int i = 0; i < 1000000; i++)
    {
        treap = ins((rand()%100), treap);
    }
    timer = clock() - timer;
    cout << "Treap 1M: " << (float)timer / CLOCKS_PER_SEC << endl;

}

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

    test2();
    return 0;
}
