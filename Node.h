#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tgmath.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>
#define max_array 1024

using namespace std;

struct Node
    {
        std::string prefix ;
        char sym; // carattere del nodo
        int counter; // suffissi inizianti con il carattere s
        int level ; // livello del nodo radice = 0
        Node * child; // nodi aventi prefisso prefix+sym
        Node * next; // nodi aventi prefisso prefix
        Node(char s, int ctr , int lvl,std::string prefix,bool h);
        Node();
        ~Node();
    };

typedef struct Node* pNode;

void print_node(pNode p);
