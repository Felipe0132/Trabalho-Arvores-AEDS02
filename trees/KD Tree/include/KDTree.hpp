#pragma once
#include <vector>

using namespace std;

struct KDNode {
    vector<int> point; // Armazena as coordenadas do ponto
    KDNode* esq;
    KDNode* dir;

    KDNode(vector<int> pt) : point(pt), esq(nullptr), dir(nullptr) {}
};

class KDTree {
    private:
        KDNode* root;
        int k; // Quantidade de dimensões (ex: 2 para X,Y)

        // Funções auxiliares recursivas
        KDNode* insert(KDNode* node, vector<int> point, int depth);
        bool search(KDNode* node, vector<int> point, int depth);
        KDNode* remove(KDNode* node, vector<int> point, int depth);
        
        // Funções para encontrar o menor valor em uma dimensão específica (necessário para remoção)
        KDNode* findMin(KDNode* node, int dim, int depth);
        KDNode* minNode(KDNode* x, KDNode* y, KDNode* z, int dim);
        
        bool arePointsEqual(vector<int> point1, vector<int> point2);
        void printInOrder(KDNode* node);

    public:
        KDTree(int k); // Construtor que recebe a dimensão (k)
        void insert(vector<int> point);
        bool search(vector<int> point);
        void remove(vector<int> point);
        void printInOrder();
};
