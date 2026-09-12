#include "../include/PATRICIA.hpp"

RadixTreeNode::RadixTreeNode(EdgeLabel content, IsEndOfWord endWord)
    : content(content), endWord(endWord) {}

RadixTree::RadixTree()
    : root(new RadixTreeNode("", false)) {}

bool RadixTree::search(RadixTreeNode* node, string word) {
    RadixTreeNode* current = node;
    string remaining = word;

    while (!remaining.empty()) {
        char firstChar = remaining.at(0);

        if (!current->children.count(firstChar)) {
            return false;
        }

        RadixTreeNode* child = current->children[firstChar];

        if (remaining.starts_with(child->content)) {
            remaining = remaining.substr(child->content.length());
            current = child;
        } else {
            return false;
        }
    }
    return current->endWord;
}

void RadixTree::insert(RadixTreeNode* node, string word) {
    if (search(node, word)) {
        return;
    }

    string contentAux = node->content;
    int count = 0;
    while (count < (int)contentAux.length() && count < (int)word.length() && contentAux[count] == word[count]) {
        count++;
    }

    string prefix   = contentAux.substr(0, count);
    string sufixOld = contentAux.substr(count);
    string sufixNew = word.substr(count);

    if (sufixOld.empty() && sufixNew.empty()) { // Caso 1
        node->endWord = true;

        return;
    }                                           // Caso 1

    if (sufixOld.empty() && !sufixNew.empty()) { // Caso 2
        if (node->children.count(sufixNew.at(0))) {
            insert(node->children[sufixNew.at(0)], sufixNew);
        } else {
            node->children[sufixNew.at(0)] = new RadixTreeNode(sufixNew, true);
        }
        return;
    }                                            // Caso 2

    if (!sufixOld.empty() && sufixNew.empty()) { // Caso 3
        RadixTreeNode* oldChild = new RadixTreeNode(sufixOld, node->endWord);
        oldChild->children = node->children;

        node->content = prefix;
        node->endWord = true;
        node->children.clear();
        node->children[sufixOld.at(0)] = oldChild;
        return;
    }                                            // Caso 3

                                                 // Caso 4
    RadixTreeNode* newChild = new RadixTreeNode(sufixNew, true);
    RadixTreeNode* oldChild = new RadixTreeNode(sufixOld, node->endWord);
    oldChild->children = node->children;

    node->content = prefix;
    node->endWord = false;
    node->children.clear();
    node->children[sufixNew.at(0)] = newChild;
    node->children[sufixOld.at(0)] = oldChild;
                                                 // Caso 4
}                                               

RadixTreeNode* RadixTree::remove(RadixTreeNode* node, string word){
    if(!search(word)){
        return nullptr;
    }

    RadixTreeNode* aux = node;

    if(word == node->content){
        if(node->children.empty()){
            delete aux;
            return nullptr;
        }

        if(node->children.size() == 1){
            auto onlyChild = aux->children.begin()->second;

            aux->content.append(onlyChild->content);
            aux->children = onlyChild->children;
            aux->endWord = onlyChild->endWord;
            delete onlyChild;
            return aux;
        }

        aux->endWord = false;
        return aux;
    }

    string contentAux = node->content;
    int count = 0;
    while (count < (int)contentAux.length() && count < (int)word.length() && contentAux[count] == word[count]) {
        count++;
    }

    string prefix   = contentAux.substr(0, count);
    string sufixOld = contentAux.substr(count);
    string sufixNew = word.substr(count);

    node->children[sufixNew.at(0)] = remove(node->children[sufixNew.at(0)], sufixNew);

    if(node->children[sufixNew.at(0)] == nullptr){
        node->children.erase(sufixNew.at(0));
    }

    return node;
}

void RadixTree::print(vector<string>& printer, RadixTreeNode* node, string prefix){
    string acc = prefix + node->content;

    if(node->endWord){
        printer.push_back(acc);
    }
    for(auto& [ch, child] : node->children){
        print(printer, child, acc);
    }
}

void RadixTree::destructor(RadixTreeNode* node){
    for(auto& [ch, child] : node->children){
        destructor(child);
    }

    delete node;
}

bool RadixTree::search(string word) {
    return search(root, word);
}

void RadixTree::insert(string word) {
    if (!root->children.count(word.at(0))) {
        root->children[word.at(0)] = new RadixTreeNode(word, true);
        return;
    }

    if (search(word)) {
        return;
    }

    insert(root->children[word.at(0)], word);
}

RadixTreeNode* RadixTree::remove(string word){
    if(!search(word)){ 
        return nullptr;
    }

    root->children[word.at(0)] = remove(root->children[word.at(0)], word);

    if(root->children[word.at(0)] == nullptr){
        root->children.erase(word.at(0));
    }

    return root;
}

void RadixTree::print(vector<string>& printer){
    if(this->root->children.size()==0){
        printer.push_back("Empty Tree");
        return;
    }

    RadixTreeNode* aux = this->root;

    for(auto& [ch, child] : aux->children){
        print(printer, child, "");
    }
}

void RadixTree::destructor(){
    destructor(root);
    root = nullptr;
}

bool RadixTree::isEmpty(){
    return root == nullptr || root->children.empty();
}