#pragma once
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using IsEndOfWord = bool;

struct TrieTreeNode {
    IsEndOfWord endWord;
    unordered_map<char, TrieTreeNode*> children;

    TrieTreeNode(bool endWord = false) : endWord(endWord) {}
};

class TrieTree {
    private:
        TrieTreeNode* root;

        bool search(TrieTreeNode* node, string word);
        void insert(TrieTreeNode* node, string word);
        TrieTreeNode* remove(TrieTreeNode* node, string word);
        void print(vector<string>& printer, TrieTreeNode* node, string prefix);
        void destructor(TrieTreeNode* node);

    public:
        TrieTree();
        bool search(string word);
        void insert(string word);
        TrieTreeNode* remove(string word);
        void print(vector<string>& printer);
        void destructor();
        bool isEmpty();
};