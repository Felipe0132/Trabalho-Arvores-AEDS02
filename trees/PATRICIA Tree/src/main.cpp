#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/PATRICIA.hpp"

using namespace std;
using namespace chrono;

vector<string> loadWords(const string& path) {
    vector<string> words;
    ifstream file(path);
    if (!file.is_open()) { cerr << "[PATRICIA] Erro ao abrir: " << path << "\n"; return words; }
    string word;
    while (getline(file, word)) if (!word.empty()) words.push_back(word);
    return words;
}

void printSection(const string& title) {
    cout << "\n========================================\n";
    cout << "  " << title << "\n";
    cout << "========================================\n";
}

int main() {
    auto totalStart = high_resolution_clock::now();

    cout << "========================================\n";
    cout << "   BENCHMARK PATRICIA (Radix Tree)\n";
    cout << "========================================\n";

    const string DATA_ALPHA  = "../../data/strings/insert_alpha.txt";
    const string DATA_RANDOM = "../../data/strings/insert_random.txt";
    const string DATA_SEARCH = "../../data/strings/search.txt";
    const string DATA_REMOVE = "../../data/strings/remove.txt";
    const string OUTPUT_FILE = "../../output/output.txt";

    vector<string> searchWords = loadWords(DATA_SEARCH);
    vector<string> removeWords = loadWords(DATA_REMOVE);

    long long ms_alpha = 0, ms_search = 0, ms_remove = 0, ms_random = 0;

    // ── Cenário 1: Inserção Alfabética ────────────────────────────────────
    printSection("CENARIO 1: INSERCAO ALFABETICA (10^6 palavras)");
    {
        RadixTree tree;
        vector<string> insertWords = loadWords(DATA_ALPHA);
        cout << "--> Inserindo " << insertWords.size() << " palavras (ordem alfabetica)...\n";

        auto start = high_resolution_clock::now();
        for (const string& w : insertWords) tree.insert(w);
        auto end = high_resolution_clock::now();
        ms_alpha = duration_cast<milliseconds>(end - start).count();
        cout << "Tempo de insercao (alfa): " << ms_alpha << " ms\n";

        int found = 0;
        cout << "--> Buscando " << searchWords.size() << " palavras...\n";
        start = high_resolution_clock::now();
        for (const string& w : searchWords) if (tree.search(w)) found++;
        end = high_resolution_clock::now();
        ms_search = duration_cast<milliseconds>(end - start).count();
        cout << "Encontradas: " << found << "/" << searchWords.size() << "\n";
        cout << "Tempo de busca: " << ms_search << " ms\n";

        cout << "--> Removendo " << removeWords.size() << " palavras...\n";
        start = high_resolution_clock::now();
        for (const string& w : removeWords) tree.remove(w);
        end = high_resolution_clock::now();
        ms_remove = duration_cast<milliseconds>(end - start).count();
        cout << "Tempo de remocao: " << ms_remove << " ms\n";

        tree.destructor();
    }

    // ── Cenário 2: Inserção Aleatória ─────────────────────────────────────
    printSection("CENARIO 2: INSERCAO ALEATORIA (10^6 palavras)");
    {
        RadixTree tree;
        vector<string> insertWords = loadWords(DATA_RANDOM);
        cout << "--> Inserindo " << insertWords.size() << " palavras (ordem aleatoria)...\n";

        auto start = high_resolution_clock::now();
        for (const string& w : insertWords) tree.insert(w);
        auto end = high_resolution_clock::now();
        ms_random = duration_cast<milliseconds>(end - start).count();
        cout << "Tempo de insercao (rand): " << ms_random << " ms\n";

        tree.destructor();
    }

    // ── Escreve no output.txt com total na frente ──────────────────────────
    {
        long long total = ms_alpha + ms_search + ms_remove + ms_random;
        ofstream out(OUTPUT_FILE, ios::app);
        if (out.is_open()) {
            out << "PATRICIA:"
                << " total="        << total    << "ms"
                << " insert_alpha=" << ms_alpha  << "ms"
                << " insert_random="<< ms_random << "ms"
                << " search="       << ms_search << "ms"
                << " remove="       << ms_remove << "ms"
                << "\n";
        }
    }

    auto totalEnd = high_resolution_clock::now();
    printSection("TEMPO TOTAL DE EXECUCAO — PATRICIA");
    cout << "Tempo total: " << duration_cast<milliseconds>(totalEnd - totalStart).count() << " ms\n";

    return 0;
}
