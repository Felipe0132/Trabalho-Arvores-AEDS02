#include "../include/KDTree.hpp"
#include <iostream>

using namespace std;

KDTree::KDTree(int k) : root(nullptr), k(k) {}

bool KDTree::arePointsEqual(vector<int> point1, vector<int> point2) {
    for (int i = 0; i < k; ++i) {
        if (point1[i] != point2[i]) return false;
    }
    return true;
}

void KDTree::insert(vector<int> point) {
    root = insert(root, point, 0);
}

KDNode* KDTree::insert(KDNode* node, vector<int> point, int depth) {
    // CASO 1: Árvore/Subárvore vazia. Criamos o nó aqui.
    if (node == nullptr) {
        return new KDNode(point);
    }

    // Calcula a dimensão atual (0 para X, 1 para Y, etc)
    int cd = depth % k;

    // CASO 2: O valor na dimensão atual é menor, então vai para a esquerda
    if (point[cd] < node->point[cd]) {
        node->esq = insert(node->esq, point, depth + 1);
    }
    // CASO 3: O valor na dimensão atual é maior ou igual, então vai para a direita
    else {
        node->dir = insert(node->dir, point, depth + 1);
    }

    return node;
}

bool KDTree::search(vector<int> point) {
    return search(root, point, 0);
}

bool KDTree::search(KDNode* node, vector<int> point, int depth) {
    if (node == nullptr) return false;

    if (arePointsEqual(node->point, point)) return true;

    int cd = depth % k;

    if (point[cd] < node->point[cd]) {
        return search(node->esq, point, depth + 1);
    } else {
        return search(node->dir, point, depth + 1);
    }
}

// Retorna o nó com o menor valor na dimensão desejada (d)
KDNode* KDTree::minNode(KDNode* x, KDNode* y, KDNode* z, int d) {
    KDNode* res = x;
    if (y != nullptr && y->point[d] < res->point[d]) res = y;
    if (z != nullptr && z->point[d] < res->point[d]) res = z;
    return res;
}

KDNode* KDTree::findMin(KDNode* node, int d, int depth) {
    if (node == nullptr) return nullptr;

    int cd = depth % k;

    // CASO 1: A dimensão atual é exatamente a dimensão que estamos buscando o mínimo.
    // Como a KD-Tree organiza os menores à esquerda, o mínimo só pode estar na subárvore esquerda ou ser o próprio nó.
    if (cd == d) {
        if (node->esq == nullptr) return node;
        return findMin(node->esq, d, depth + 1);
    }

    // CASO 2: A dimensão atual é diferente.
    // O mínimo pode estar tanto na direita quanto na esquerda. Precisamos buscar em ambas e comparar.
    return minNode(node,
                   findMin(node->esq, d, depth + 1),
                   findMin(node->dir, d, depth + 1), d);
}

void KDTree::remove(vector<int> point) {
    root = remove(root, point, 0);
}

KDNode* KDTree::remove(KDNode* node, vector<int> point, int depth) {
    if (node == nullptr) return nullptr;

    int cd = depth % k;

    // Se encontramos o ponto que queremos remover
    if (arePointsEqual(node->point, point)) {
        // CASO 1: Se o nó tiver um filho à direita
        if (node->dir != nullptr) {
            // Buscamos o menor nó na subárvore direita considerando a dimensão atual
            KDNode* min = findMin(node->dir, cd, depth + 1);
            
            // Copiamos os dados do sucessor para o nó atual
            node->point = min->point;
            
            // Removemos recursivamente o sucessor
            node->dir = remove(node->dir, min->point, depth + 1);
        }
        // CASO 2: Se não tem filho à direita, mas tem à esquerda
        else if (node->esq != nullptr) {
            KDNode* min = findMin(node->esq, cd, depth + 1);
            node->point = min->point;
            
            // Aqui tem um truque da KD-Tree: como não temos direita, pegamos a esquerda,
            // mas colocamos ela na direita para manter a propriedade (maiores na direita).
            node->dir = remove(node->esq, min->point, depth + 1);
            node->esq = nullptr; // A esquerda agora fica vazia
        }
        // CASO 3: É um nó folha (sem filhos)
        else {
            delete node;
            return nullptr;
        }
        return node;
    }

    // Se ainda não achamos o ponto, continuamos a busca
    if (point[cd] < node->point[cd]) {
        node->esq = remove(node->esq, point, depth + 1);
    } else {
        node->dir = remove(node->dir, point, depth + 1);
    }

    return node;
}

void KDTree::printInOrder() {
    printInOrder(root);
    cout << endl;
}

void KDTree::printInOrder(KDNode* node) {
    if (node != nullptr) {
        printInOrder(node->esq);
        
        cout << "(";
        for(int i = 0; i < k; i++){
            cout << node->point[i] << (i == k-1 ? "" : ", ");
        }
        cout << ") ";
        
        printInOrder(node->dir);
    }
}
