#include "../include/Splay.hpp"
#include <iostream>


SplayTree::SplayTree() : root(nullptr) {}

void SplayTree::rotacaoDir(SplayNode* no){
    SplayNode* x = no->esq;
    SplayNode* aux = x->dir; 

    no->esq = aux;
    if (aux != nullptr)
        aux->parent = no;

    x->parent = no->parent;
    if (no->parent == nullptr)
        root = x;
    else if (no->parent->esq == no)
        no->parent->esq = x;
    else
        no->parent->dir = x;

    x->dir = no;
    no->parent = x;
}

void SplayTree::rotacaoEsq(SplayNode* no){
    SplayNode* x = no->dir;
    SplayNode* aux = x->esq; 

    no->dir = aux;
    if (aux != nullptr)
        aux->parent = no;

    x->parent = no->parent;
    if (no->parent == nullptr)
        root = x;
    else if (no->parent->dir == no)
        no->parent->dir = x;
    else
        no->parent->esq = x;

    x->esq = no;
    no->parent = x;
}

void SplayTree::splay(SplayNode* node){
    while(node != root){
        SplayNode* pai = node->parent;
        SplayNode* avo = pai->parent;

        // Zig
        if(avo == nullptr){ 
            if(node == pai->esq){
                rotacaoDir(pai);
            }else{
                rotacaoEsq(pai);
            }
        }
        // Zig-Zig
        else if(pai->esq == node && pai == avo->esq){
            rotacaoDir(avo);
            rotacaoDir(pai);
        }else if(node == pai->dir && pai == avo->dir){
            rotacaoEsq(avo);
            rotacaoEsq(pai);
        }
        // Zig-Zag
        else if(node == pai->dir && pai == avo->esq){
            rotacaoEsq(pai);
            rotacaoDir(avo);
        }else if(node == pai->esq && pai == avo->dir){
            rotacaoDir(pai);
            rotacaoEsq(avo);
        }
    }
}

SplayNode* SplayTree::search(SplayNode *node, SplayNode *anterior, int valor){
    if(node == nullptr){
        if (anterior != nullptr) { 
            splay(anterior);
        }
        return nullptr;
    }

    if(valor == node->content){
        splay(node);
        return node;
    }

    if(valor > node->content){
        return search(node->dir, node, valor);
    } else{
        return search(node->esq, node, valor);
    }
}

void SplayTree::insert(SplayNode *node, SplayNode *anterior, int valor){
    if(node == nullptr){
        SplayNode *newNode = new SplayNode(valor, nullptr, nullptr, anterior);
        
        if(valor < anterior->content){
            anterior->esq = newNode;
        } else {
            anterior->dir = newNode;
        }
        
        splay(newNode);
        return;
    }

    if(valor > node->content){
        insert(node->dir, node, valor); 
    } else { 
        insert(node->esq, node, valor);
    }
}

SplayNode* SplayTree::search(int valor){
    return search(this->root, nullptr, valor);
}

void SplayTree::insert(int valor){
    if(this->root == nullptr){
        this->root = new SplayNode(valor, nullptr, nullptr, nullptr);
        return;
    }

    if(search(valor) != nullptr){
        return;
    }

    insert(this->root, nullptr, valor);
}

void SplayTree::remove(int valor) {
    SplayNode* noRemover = search(valor);

    if (noRemover == nullptr || noRemover->content != valor) {
        return;
    }

    SplayNode* L = noRemover->esq;
    SplayNode* R = noRemover->dir;

    // Duas arvores separadas
    if (L != nullptr) L->parent = nullptr;
    if (R != nullptr) R->parent = nullptr;

    delete noRemover;

    if(L == nullptr && R == nullptr) {
        this->root = nullptr;
        return;
    }

    if(L == nullptr && R != nullptr){
        this->root = R;
        return;
    } else if(R == nullptr && L != nullptr){
        this->root = L;
        return;
    }

    SplayNode* aux = L;
    while(aux->dir != nullptr){
        aux = aux->dir;
    }

    splay(aux);
    aux->dir = R;
    
    R->parent = aux;
}

void SplayTree::printInOrder(SplayNode* node) {
    if (node != nullptr) {
        printInOrder(node->esq);
        std::cout << node->content << " ";
        printInOrder(node->dir);
    }
}

void SplayTree::printInOrder() {
    printInOrder(this->root);
    std::cout << std::endl;
}

void SplayTree::destructor(SplayNode* node) {
    if (node == nullptr) return;
    destructor(node->esq);
    destructor(node->dir);
    delete node;
}

void SplayTree::destructor() {
    destructor(this->root);
    this->root = nullptr;
}