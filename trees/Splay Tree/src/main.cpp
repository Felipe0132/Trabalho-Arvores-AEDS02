#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/Splay.hpp"

using namespace std;
using namespace chrono;

vector<int> loadIntegers(const string& path) {
    vector<int> numbers;
    ifstream file(path);
    if (!file.is_open()) { cerr << "[SPLAY] Erro ao abrir: " << path << "\n"; return numbers; }
    int num;
    while (file >> num) numbers.push_back(num);
    return numbers;
}

void printSection(const string& title) {
    cout << "\n========================================================\n";
    cout << "  " << title << "\n";
    cout << "========================================================\n";
}

struct BenchResult {
    long long ms_insert;
    long long ms_search;
    long long ms_remove;
};

BenchResult runScenario(const string& name, const string& insertPath,
                         const vector<int>& searchKeys, const vector<int>& removeKeys) {
    printSection("CENARIO: " + name);

    SplayTree tree;
    vector<int> insertKeys = loadIntegers(insertPath);

    cout << "--> Inserindo " << insertKeys.size() << " elementos...\n";
    auto start = high_resolution_clock::now();
    for (int k : insertKeys) tree.insert(k);
    auto end = high_resolution_clock::now();
    long long ms_insert = duration_cast<milliseconds>(end - start).count();
    cout << "Tempo de insercao: " << ms_insert << " ms\n";

    int found = 0;
    cout << "--> Buscando " << searchKeys.size() << " elementos distintos...\n";
    start = high_resolution_clock::now();
    for (int k : searchKeys) if (tree.search(k) != nullptr) found++;
    end = high_resolution_clock::now();
    long long ms_search = duration_cast<milliseconds>(end - start).count();
    cout << "Encontrados: " << found << "/" << searchKeys.size() << "\n";
    cout << "Tempo de busca: " << ms_search << " ms\n";

    cout << "--> Removendo " << removeKeys.size() << " elementos...\n";
    start = high_resolution_clock::now();
    for (int k : removeKeys) tree.remove(k);
    end = high_resolution_clock::now();
    long long ms_remove = duration_cast<milliseconds>(end - start).count();
    cout << "Tempo de remocao: " << ms_remove << " ms\n";

    tree.destructor();
    return {ms_insert, ms_search, ms_remove};
}

// Insere 10^6 elementos aleatórios e busca o MESMO elemento 10^5 vezes.
// Na Splay: após a 1ª busca o elemento sobe para a raiz → buscas seguintes são O(1).
long long runRepeatedSearch(int target, int repetitions) {
    printSection("CENARIO: BUSCA REPETIDA (mesmo elemento x10^5)");

    SplayTree tree;
    vector<int> insertKeys = loadIntegers("../../data/integers/insert_random_1M.txt");

    cout << "--> Inserindo " << insertKeys.size() << " elementos (random)...\n";
    for (int k : insertKeys) tree.insert(k);

    // Garante que o alvo existe na árvore
    tree.insert(target);

    cout << "--> Buscando o elemento " << target
         << " exatamente " << repetitions << " vezes...\n";
    int found = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++)
        if (tree.search(target) != nullptr) found++;
    auto end = high_resolution_clock::now();
    long long ms = duration_cast<milliseconds>(end - start).count();

    cout << "Encontrado: " << found << "/" << repetitions << " vezes\n";
    cout << "Tempo total: " << ms << " ms\n";
    cout << "Tempo medio por busca: " << (ms * 1000.0 / repetitions) << " us\n";
    cout << "[SPLAY] Apos a 1a busca, o elemento fica na raiz => buscas seguintes O(1)!\n";

    return ms;
}

int main() {
    auto totalStart = high_resolution_clock::now();

    cout << "========================================================\n";
    cout << "         BENCHMARK COMPLETO DA ARVORE SPLAY\n";
    cout << "         (10^6 insercoes | 10^5 busca | 10^3 remocao)\n";
    cout << "========================================================\n";

    const string OUTPUT_FILE = "../../output/output.txt";

    vector<int> searchKeys = loadIntegers("../../data/integers/search_100k.txt");
    vector<int> removeKeys = loadIntegers("../../data/integers/remove_1k.txt");

    auto r_asc  = runScenario("CRESCENTE (ASC)",   "../../data/integers/insert_asc_1M.txt",    searchKeys, removeKeys);
    auto r_desc = runScenario("DECRESCENTE (DESC)", "../../data/integers/insert_desc_1M.txt",   searchKeys, removeKeys);
    auto r_rand = runScenario("ALEATORIO (RAND)",  "../../data/integers/insert_random_1M.txt", searchKeys, removeKeys);

    // Busca repetida do mesmo elemento 10^5 vezes
    const int TARGET = 500000;
    const int REPS   = 100000;
    long long ms_repeat = runRepeatedSearch(TARGET, REPS);

    // ── Escreve no output.txt ──────────────────────────────────────────────
    {
        long long total = r_asc.ms_insert + r_desc.ms_insert + r_rand.ms_insert
                        + r_rand.ms_search + r_rand.ms_remove + ms_repeat;
        ofstream out(OUTPUT_FILE, ios::app);
        if (out.is_open()) {
            out << "SPLAY:"
                << " total="         << total            << "ms"
                << " insert_asc="    << r_asc.ms_insert  << "ms"
                << " insert_desc="   << r_desc.ms_insert << "ms"
                << " insert_rand="   << r_rand.ms_insert << "ms"
                << " search="        << r_rand.ms_search  << "ms"
                << " remove="        << r_rand.ms_remove  << "ms"
                << " search_repeat=" << ms_repeat         << "ms"
                << "\n";
        }
    }

    auto totalEnd = high_resolution_clock::now();
    printSection("TEMPO TOTAL DE EXECUCAO — SPLAY");
    cout << "Tempo total: " << duration_cast<milliseconds>(totalEnd - totalStart).count() << " ms\n";

    return 0;
}
