#include "../include/Trie.hpp"
TrieTree::TrieTree()
    : root(new TrieTreeNode(false)) {}

bool TrieTree::search(TrieTreeNode* node, string word) {
    if (word.empty()) {
        return node->endWord;
    }

    TrieTreeNode* current = node;

    char firstChar = word.at(0);

    if (!current->children.count(firstChar)) { // No one children can be the result
        return false;
    }

    TrieTreeNode* child = current->children[firstChar]; // Get the children possible

    return search(child, word.substr(1));
}

void TrieTree::insert(TrieTreeNode* node, string word) {    
    if (word.empty()) { // fineshed recursion
        node->endWord = true;
        return;
    }

    char firstChar = word.at(0);
    if (!node->children.count(firstChar)) { // if don't find children comun
        node->children[firstChar] = new TrieTreeNode(false);
    }
    insert(node->children[firstChar], word.substr(1)); // continue down until finished chars
}

TrieTreeNode* TrieTree::remove(TrieTreeNode* node, string word){
    TrieTreeNode* aux = node;

    if (word.empty()) {
        aux->endWord = false;
    }else{
        if(aux->children.count(word.at(0))){ // If exists children
            node->children[word.at(0)] = remove(node->children[word.at(0)], word.substr(1)); // Delete children, if are 2 sequences, the function down until the last char

            if (node->children[word.at(0)] == nullptr) { // Check if children has delete, if yes, remove the pointer
                node->children.erase(word.at(0));
            }
        }
    }

    if (!node->endWord && node->children.empty()) { // If no don't finished word and don't have children
        delete node;
        return nullptr;
    }

    return node;
}

void TrieTree::print(vector<string>& printer, TrieTreeNode* node, string word){
    if(node->endWord){
        printer.push_back(word);
    }

    for(auto& [ch, child] : node->children){
        string acc = word + ch;

        print(printer, child, acc);
    }
}

void TrieTree::destructor(TrieTreeNode* node){
    for(auto& [ch, child] : node->children){
        destructor(child);
    }

    delete node;
}

bool TrieTree::search(string word) {
    return search(root, word);
}

void TrieTree::insert(string word) {
    if (word.empty() || search(word)){
        return;
    }
    insert(root, word);
}

TrieTreeNode* TrieTree::remove(string word){
    if(!search(word)){ 
        return nullptr;
    }

    remove(root, word);
    return root;
}

void TrieTree::print(vector<string>& printer){
    if(this->root->children.empty()){
        printer.push_back("Empty Tree");
        return;
    }

    TrieTreeNode* aux = this->root;

    for(auto& [ch, child] : aux->children){
        string word = string(1, ch);
        print(printer, child, word);
    }
}

void TrieTree::destructor(){
    destructor(root);
    root = nullptr;
}

bool TrieTree::isEmpty(){
    return root == nullptr || root->children.empty();
}