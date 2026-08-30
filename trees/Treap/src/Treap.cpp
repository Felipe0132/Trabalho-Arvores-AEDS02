#include "../include/Treap.hpp"
Treap::TrieTree()
    : root(new TrieTreeNode(false)) {}

bool TrieTree::search(TrieTreeNode* node, string word) {
    if (word.empty()) {
        return node->endWord;
    }