#pragma once
#include <vector>
#include <random>

using namespace std;

using EdgeLabel   = int;
using Weight = int;

struct TreapNode {
    EdgeLabel content;
    Weight weight;
};

class Treap{
    private:
        TreapNode* root;

        void insert(TreapNode* root, int newNode);

    public:
        void insert(int newNode);
};