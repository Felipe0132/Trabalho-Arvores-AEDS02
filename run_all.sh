#!/bin/bash
# run_all.sh — Compila e executa o benchmark completo de todas as árvores
# Gera: output/output.txt com os tempos de cada árvore

set -e

ROOT="$(cd "$(dirname "$0")" && pwd)"

echo "============================================================"
echo "  BENCHMARK COMPLETO — AEDS2 Árvores"
echo "============================================================"

# ── 0. Gerar dados (se necessário) ──────────────────────────────────────────
echo ""
echo "[0/6] Verificando/gerando dados..."
python3 "$ROOT/data/gen_data.py"

# ── 1. Limpar output anterior ────────────────────────────────────────────────
echo ""
echo "[1/6] Limpando output anterior..."
mkdir -p "$ROOT/output"
> "$ROOT/output/output.txt"

# ── 2. PATRICIA ──────────────────────────────────────────────────────────────
echo ""
echo "[2/6] Compilando e executando PATRICIA..."
cd "$ROOT/trees/PATRICIA Tree"
mkdir -p src/output
make -s
./src/output/patricia

# ── 3. TRIE ───────────────────────────────────────────────────────────────────
echo ""
echo "[3/6] Compilando e executando TRIE..."
cd "$ROOT/trees/Trie Tree"
mkdir -p src/output
make -s
./src/output/trie

# ── 4. TREAP ──────────────────────────────────────────────────────────────────
echo ""
echo "[4/6] Compilando e executando TREAP..."
cd "$ROOT/trees/Treap"
make -s
./src/output/treap

# ── 5. SPLAY ──────────────────────────────────────────────────────────────────
echo ""
echo "[5/6] Compilando e executando SPLAY..."
cd "$ROOT/trees/Splay Tree"
make -s
./src/output/splay

# ── 6. KD TREE ────────────────────────────────────────────────────────────────
echo ""
echo "[6/6] Compilando e executando KD TREE..."
cd "$ROOT/trees/KD Tree"
make -s
./src/output/kdtree

# ── Resultado final ───────────────────────────────────────────────────────────
echo ""
echo "============================================================"
echo "  RESULTADO — output/output.txt"
echo "============================================================"
cat "$ROOT/output/output.txt"
echo ""
echo "Benchmark concluido!"
