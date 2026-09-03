#pragma once
#include <vector>
#include <random>

using namespace std;

using EdgeLabel = int;
using Weight    = int;

struct TreapNode {
    EdgeLabel content;
    Weight weight;
    TreapNode* esq;
    TreapNode* dir;

    TreapNode(EdgeLabel content, Weight weight, TreapNode* esq = nullptr, TreapNode* dir = nullptr) 
        : content(content), weight(weight), esq(esq), dir(dir) {}
};

class TreapTree {
    private:
        TreapNode* root;

        TreapNode* rotacaoEsq(TreapNode* root);
        TreapNode* rotacaoDir(TreapNode* root);
        TreapNode* insert(TreapNode* root, TreapNode* node);
        TreapNode* search(TreapNode* root, int valueNode);
        TreapNode* remove(TreapNode* root, int valueNode);
        void printInOrder(TreapNode* root, vector<int>& printer);
        void destructor(TreapNode* root);

    public:
        TreapTree();
        void insert(int newNode);
        TreapNode* search(int valueNode);
        TreapNode* remove(int valueNode);
        void print(vector<int>& printer);
        void destructor();
        bool isEmpty();
};