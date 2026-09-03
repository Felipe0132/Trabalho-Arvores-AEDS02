#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/Treap.hpp"

using namespace std;
using namespace chrono;

vector<int> loadIntegers(const string& path) {
    vector<int> numbers;
    ifstream file(path);
    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

void printSection(const string& title) {
    cout << "\n========================================================\n";
    cout << "  " << title << "\n";
    cout << "========================================================\n";
}

void runBenchmark(const string& scenarioName, const string& insertFilePath, 
                  const vector<int>& searchKeys, const vector<int>& removeKeys) {
    printSection("CENARIO: " + scenarioName);

    TreapTree tree;
    vector<int> insertKeys = loadIntegers(insertFilePath);
    vector<int> printer;

    // ── 1. Inserção de 10^4 (10.000) elementos ───────────────────
    cout << "--> Inserindo " << insertKeys.size() << " elementos...\n";
    auto start = high_resolution_clock::now();
    for (int key : insertKeys) {
        tree.insert(key);
    }
    auto end = high_resolution_clock::now();
    cout << "Tempo de insercao: " << duration_cast<microseconds>(end - start).count() << " us ("
         << duration_cast<milliseconds>(end - start).count() << " ms)\n";

    // ── 2. Impressão após Inserção ───────────────────────────────
    tree.print(printer);
    cout << "Total de elementos na arvore (apos insercao): " << printer.size() << "\n";
    cout << "Primeiros 5 elementos (em ordem): ";
    for (size_t i = 0; i < min(printer.size(), (size_t)5); ++i) cout << printer[i] << " ";
    cout << "\nUltimos 5 elementos (em ordem): ";
    for (size_t i = (printer.size() >= 5 ? printer.size() - 5 : 0); i < printer.size(); ++i) cout << printer[i] << " ";
    cout << "\n";

    // ── 3. Busca de 10^2 (100) elementos (antes da remoção) ──────
    cout << "\n--> Buscando " << searchKeys.size() << " elementos (antes da remocao)...\n";
    int found = 0;
    start = high_resolution_clock::now();
    for (int key : searchKeys) {
        if (tree.search(key) != nullptr) found++;
    }
    end = high_resolution_clock::now();
    cout << "Encontrados: " << found << "/" << searchKeys.size() << "\n";
    cout << "Tempo de busca: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── 4. Remoção de 10^2 (100) elementos ───────────────────────
    cout << "\n--> Removendo " << removeKeys.size() << " elementos...\n";
    start = high_resolution_clock::now();
    for (int key : removeKeys) {
        tree.remove(key);
    }
    end = high_resolution_clock::now();
    cout << "Tempo de remocao: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── 5. Busca de 10^2 (100) elementos (após remoção) ──────────
    cout << "\n--> Buscando " << searchKeys.size() << " elementos (apos remocao)...\n";
    found = 0;
    start = high_resolution_clock::now();
    for (int key : searchKeys) {
        if (tree.search(key) != nullptr) found++;
    }
    end = high_resolution_clock::now();
    cout << "Encontrados: " << found << "/" << searchKeys.size() << "\n";
    cout << "Tempo de busca: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── 6. Impressão após Remoção ────────────────────────────────
    tree.print(printer);
    cout << "Total de elementos na arvore (apos remocao): " << printer.size() << "\n";

    // ── 7. Destrutor ─────────────────────────────────────────────
    start = high_resolution_clock::now();
    tree.destructor();
    end = high_resolution_clock::now();
    cout << "Arvore destruida com sucesso em: " << duration_cast<microseconds>(end - start).count() << " us\n";
}

int main() {
    auto totalStart = high_resolution_clock::now();

    cout << "========================================================\n";
    cout << "         BENCHMARK COMPLETO DA ARVORE TREAP             \n";
    cout << "========================================================\n";

    vector<int> searchKeys = loadIntegers("../../data/integers/search_100.txt");
    vector<int> removeKeys = loadIntegers("../../data/integers/remove_100.txt");

    // Executa os 3 cenários de entrada de 10^4 (10.000) elementos:
    runBenchmark("1. ENTRADA ALEATORIA (RANDOM)", 
                 "../../data/integers/insert_random_10k.txt", searchKeys, removeKeys);

    runBenchmark("2. ENTRADA CRESCENTE (ASCENDING)", 
                 "../../data/integers/insert_asc_10k.txt", searchKeys, removeKeys);

    runBenchmark("3. ENTRADA DECRESCENTE (DESCENDING)", 
                 "../../data/integers/insert_desc_10k.txt", searchKeys, removeKeys);

    auto totalEnd = high_resolution_clock::now();
    printSection("TEMPO TOTAL DE EXECUCAO DO BENCHMARK");
    cout << "Tempo total: " << duration_cast<microseconds>(totalEnd - totalStart).count() << " us ("
         << duration_cast<milliseconds>(totalEnd - totalStart).count() << " ms)\n";

    return 0;
}
