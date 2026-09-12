#pragma once
#include <vector>
#include <random>

using namespace std;

struct SplayNode;

using Dir = SplayNode*;
using Esq = SplayNode*;
using Parent = SplayNode*;
using EdgeLabel = int;

struct SplayNode{
    EdgeLabel content;
    Dir dir;
    Esq esq;
    Parent parent;

    SplayNode(EdgeLabel content, Dir dir = nullptr, Esq esq = nullptr, Parent parent = nullptr) : content(content), dir(dir), esq(esq), parent(parent) {}
};

class SplayTree{
    private:
        SplayNode* root;

        void rotacaoDir(SplayNode *root);
        void rotacaoEsq(SplayNode *root);
        void splay(SplayNode *node);

        SplayNode* search(SplayNode *node, SplayNode *anterior, int valor);
        void insert(SplayNode *node, SplayNode *anterior, int valor);
        void destructor(SplayNode *node);

    public:
        SplayTree();
        SplayNode* search(int valor);
        void insert(int valor);
        void remove(int valor);
        void destructor();
        void printInOrder();
    private:
        void printInOrder(SplayNode* node);
};