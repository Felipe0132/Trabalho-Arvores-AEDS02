#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/KDTree.hpp"

using namespace std;
using namespace chrono;

vector<vector<int>> loadPoints(const string& path) {
    vector<vector<int>> points;
    ifstream file(path);
    if (!file.is_open()) { cerr << "[KD] Erro ao abrir: " << path << "\n"; return points; }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        int x, y;
        if (iss >> x >> y) points.push_back({x, y});
    }
    return points;
}

void printSection(const string& title) {
    cout << "\n========================================================\n";
    cout << "  " << title << "\n";
    cout << "========================================================\n";
}

int main() {
    auto totalStart = high_resolution_clock::now();

    cout << "========================================================\n";
    cout << "         BENCHMARK COMPLETO DA KD TREE (2D)\n";
    cout << "         (10^6 insercoes | 10^3 busca | 10^3 remocao)\n";
    cout << "========================================================\n";

    const string OUTPUT_FILE = "../../output/output.txt";

    KDTree tree(2);

    // ── Inserção de 10^6 pontos ───────────────────────────────────────────
    printSection("INSERCAO (10^6 pontos 2D)");
    vector<vector<int>> insertPoints = loadPoints("../../data/kd/insert_1M.txt");
    cout << "--> Inserindo " << insertPoints.size() << " pontos...\n";
    auto start = high_resolution_clock::now();
    for (const auto& pt : insertPoints) tree.insert(pt);
    auto end = high_resolution_clock::now();
    long long ms_insert = duration_cast<milliseconds>(end - start).count();
    cout << "Tempo de insercao: " << ms_insert << " ms\n";

    // ── Busca de 10^3 pontos ──────────────────────────────────────────────
    printSection("BUSCA (10^3 pontos)");
    vector<vector<int>> searchPoints = loadPoints("../../data/kd/search_1k.txt");
    cout << "--> Buscando " << searchPoints.size() << " pontos...\n";
    int found = 0;
    start = high_resolution_clock::now();
    for (const auto& pt : searchPoints) if (tree.search(pt)) found++;
    end = high_resolution_clock::now();
    long long ms_search = duration_cast<milliseconds>(end - start).count();
    cout << "Encontrados: " << found << "/" << searchPoints.size() << "\n";
    cout << "Tempo de busca: " << ms_search << " ms\n";

    // ── Remoção de 10^3 pontos ────────────────────────────────────────────
    printSection("REMOCAO (10^3 pontos)");
    vector<vector<int>> removePoints = loadPoints("../../data/kd/remove_1k.txt");
    cout << "--> Removendo " << removePoints.size() << " pontos...\n";
    start = high_resolution_clock::now();
    for (const auto& pt : removePoints) tree.remove(pt);
    end = high_resolution_clock::now();
    long long ms_remove = duration_cast<milliseconds>(end - start).count();
    cout << "Tempo de remocao: " << ms_remove << " ms\n";

    // ── Escreve no output.txt com total na frente ─────────────────────────
    {
        long long total = ms_insert + ms_search + ms_remove;
        ofstream out(OUTPUT_FILE, ios::app);
        if (out.is_open()) {
            out << "KD:"
                << " total="   << total     << "ms"
                << " insert="  << ms_insert << "ms"
                << " search="  << ms_search << "ms"
                << " remove="  << ms_remove << "ms"
                << "\n";
        }
    }

    auto totalEnd = high_resolution_clock::now();
    printSection("TEMPO TOTAL DE EXECUCAO — KD TREE");
    cout << "Tempo total: " << duration_cast<milliseconds>(totalEnd - totalStart).count() << " ms\n";

    return 0;
}
