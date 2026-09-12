#include "../include/Treap.hpp"

TreapTree::TreapTree() : root(nullptr) {}

TreapNode* TreapTree::rotacaoEsq(TreapNode* root){
    TreapNode* aux = root->dir;

    root->dir = aux->esq;
    aux->esq = root;
    
    return aux;
}

TreapNode* TreapTree::rotacaoDir(TreapNode* root){
    TreapNode* aux = root->esq;

    root->esq = aux->dir;
    aux->dir = root;
    
    return aux;
}

TreapNode* TreapTree::insert(TreapNode* root, TreapNode* node){
    if (root == nullptr) {
        return node;
    }

    if(root->content > node->content){
        root->esq = insert(root->esq, node);

        if (root->esq != nullptr && root->weight < root->esq->weight) {
            root = rotacaoDir(root);
        }
    }else if(root->content < node->content){
        root->dir = insert(root->dir, node);

        if (root->dir != nullptr && root->weight < root->dir->weight) {
            root = rotacaoEsq(root);
        }
    }

    return root;
}

TreapNode* TreapTree::search(TreapNode* root, int valueNode){
    if (root == nullptr || root->content == valueNode) {
        return root;
    }
    if (root->content > valueNode) {
        return search(root->esq, valueNode);
    } else {
        return search(root->dir, valueNode);
    }
}

TreapNode* TreapTree::remove(TreapNode* root, int valueNode){
    if (root == nullptr) {
        return nullptr;
    }       

    if (valueNode < root->content) {
        root->esq = remove(root->esq, valueNode);
    } else if (valueNode > root->content) {
        root->dir = remove(root->dir, valueNode);
    } else {
        if (root->esq == nullptr && root->dir == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->esq == nullptr) {
            TreapNode* aux = root->dir;
            delete root;
            return aux; 
        }
        else if (root->dir == nullptr) {
            TreapNode* aux = root->esq;
            delete root;
            return aux;
        }
        else {
            if (root->esq->weight > root->dir->weight) {
                root = rotacaoDir(root);
                root->dir = remove(root->dir, valueNode);
            } else {
                root = rotacaoEsq(root);
                root->esq = remove(root->esq, valueNode);
            }
        }
    }   
    return root;    
}

void TreapTree::printInOrder(TreapNode* root, vector<int>& printer){
    if (root == nullptr) return;
    printInOrder(root->esq, printer);
    printer.push_back(root->content);
    printInOrder(root->dir, printer);
}

void TreapTree::destructor(TreapNode* root){
    if (root == nullptr) return;
    destructor(root->esq);
    destructor(root->dir);
    delete root;
}

void TreapTree::insert(int newNode){
    static mt19937 gen(42);
    static uniform_int_distribution<> dist(1, 1000000);
    int weight = dist(gen);

    TreapNode* node = new TreapNode(newNode, weight, nullptr, nullptr);

    this->root = insert(this->root, node);
}

TreapNode* TreapTree::search(int valueNode){
    return search(this->root, valueNode);
}

TreapNode* TreapTree::remove(int valueNode){
    this->root = remove(this->root, valueNode);
    return this->root;
}

void TreapTree::print(vector<int>& printer){
    printer.clear();
    printInOrder(this->root, printer);
}

void TreapTree::destructor(){
    destructor(this->root);
    this->root = nullptr;
}

bool TreapTree::isEmpty(){
    return this->root == nullptr;
}