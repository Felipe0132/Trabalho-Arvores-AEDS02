#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/Trie.hpp"

using namespace std;
using namespace chrono;

vector<string> loadWords(const string& path) {
    vector<string> words;
    ifstream file(path);
    string word;
    while (getline(file, word)) {
        if (!word.empty()) words.push_back(word);
    }
    return words;
}

void printSection(const string& title) {
    cout << "\n========================================\n";
    cout << "  " << title << "\n";
    cout << "========================================\n";
}

int main() {
    auto totalStart = high_resolution_clock::now();

    TrieTree tree;
    vector<string> printer;

    vector<string> insertWords = loadWords("../../data/strings/insert.txt");
    vector<string> searchWords = loadWords("../../data/strings/search.txt");
    vector<string> removeWords = loadWords("../../data/strings/remove.txt");

    // ── 100 Inserções ───────────────────────────────────────────
    printSection("INSERCAO (100 palavras)");
    auto start = high_resolution_clock::now();

    for (const string& w : insertWords) {
        tree.insert(w);
    }

    auto end = high_resolution_clock::now();
    cout << "Tempo: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── Impressão após inserção ──────────────────────────────────
    printSection("IMPRESSAO (apos insercao)");
    tree.print(printer);
    for (const string& w : printer) {
        cout << w << "\n";
    }
    cout << "Total de palavras: " << printer.size() << "\n";

    // ── 50 Buscas (antes da remoção) ─────────────────────────────
    printSection("BUSCA (50 palavras — antes da remocao)");
    int found = 0;
    start = high_resolution_clock::now();

    for (const string& w : searchWords) {
        if (tree.search(w)) found++;
    }

    end = high_resolution_clock::now();
    cout << "Encontradas: " << found << "/" << searchWords.size() << "\n";
    cout << "Tempo: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── 25 Remoções ──────────────────────────────────────────────
    printSection("REMOCAO (25 palavras)");
    start = high_resolution_clock::now();

    for (const string& w : removeWords) {
        tree.remove(w);
    }

    end = high_resolution_clock::now();
    cout << "Tempo: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── 50 Buscas (após remoção) ──────────────────────────────────
    printSection("BUSCA (50 palavras — apos remocao)");
    found = 0;
    start = high_resolution_clock::now();

    for (const string& w : searchWords) {
        if (tree.search(w)) found++;
    }

    end = high_resolution_clock::now();
    cout << "Encontradas: " << found << "/" << searchWords.size() << "\n";
    cout << "Tempo: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── Impressão após remoção ──────────────────────────────────
    printSection("IMPRESSAO (apos remocao)");
    printer.clear();
    tree.print(printer);
    for (const string& w : printer) {
        cout << w << "\n";
    }
    cout << "Total de palavras: " << printer.size() << "\n";

    // ── Destrutor ───────────────────────────────────────────────
    printSection("DESTRUTOR");
    start = high_resolution_clock::now();
    tree.destructor();
    end = high_resolution_clock::now();
    cout << "Arvore destruida com sucesso.\n";
    cout << "Tempo do destrutor: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // ── Tempo Total de Execução do Main ────────────────────────
    auto totalEnd = high_resolution_clock::now();
    printSection("TEMPO TOTAL DE EXECUCAO DO MAIN");
    cout << "Tempo total: " << duration_cast<microseconds>(totalEnd - totalStart).count() << " us (" 
         << duration_cast<milliseconds>(totalEnd - totalStart).count() << " ms)\n";

    return 0;
}
