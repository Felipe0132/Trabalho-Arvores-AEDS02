#pragma once
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using EdgeLabel   = string;
using IsEndOfWord = bool;

struct RadixTreeNode {
    EdgeLabel   content;
    IsEndOfWord endWord;
    unordered_map<char, RadixTreeNode*> children;

    RadixTreeNode(EdgeLabel content = "", IsEndOfWord endWord = false);
};

class RadixTree {
    private:
        RadixTreeNode* root;

        bool search(RadixTreeNode* node, string word);
        void insert(RadixTreeNode* node, string word);
        RadixTreeNode* remove(RadixTreeNode* node, string word);
        void print(vector<string>& printer, RadixTreeNode* node, string prefix);
        void destructor(RadixTreeNode* node);

    public:
        RadixTree();
        bool search(string word);
        void insert(string word);
        RadixTreeNode* remove(string word);
        void print(vector<string>& printer);
        void destructor();
        bool isEmpty();
};