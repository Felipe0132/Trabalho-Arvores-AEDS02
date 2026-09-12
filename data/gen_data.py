"""
gen_data.py — Gerador de dados para benchmark das árvores
Gera todos os arquivos .txt necessários em data/strings/, data/integers/ e data/kd/
"""

import os
import random
import string

SEED = 42
random.seed(SEED)

BASE = os.path.dirname(os.path.abspath(__file__))

# ─── Helpers ────────────────────────────────────────────────────────────────

def ensure_dir(path):
    os.makedirs(path, exist_ok=True)

def write_lines(path, lines):
    with open(path, "w") as f:
        f.write("\n".join(str(l) for l in lines) + "\n")
    print(f"  Gerado: {os.path.relpath(path, BASE)} ({len(lines)} linhas)")

def random_string(min_len=5, max_len=15):
    length = random.randint(min_len, max_len)
    return "".join(random.choices(string.ascii_lowercase, k=length))

# ─── Strings (Patricia e Trie) ───────────────────────────────────────────────

def gen_strings():
    print("\n[strings]")
    out = os.path.join(BASE, "strings")
    ensure_dir(out)

    N_INSERT = 1_000_000
    N_OPS    = 1_000

    # Gera pool de strings únicas
    pool = set()
    while len(pool) < N_INSERT + N_OPS * 2:
        pool.add(random_string())
    pool = list(pool)
    random.shuffle(pool)

    insert_pool  = pool[:N_INSERT]
    search_pool  = pool[N_INSERT : N_INSERT + N_OPS]
    remove_pool  = pool[N_INSERT + N_OPS : N_INSERT + N_OPS * 2]

    # Inserção alfabética (sorted)
    alpha = sorted(insert_pool)
    write_lines(os.path.join(out, "insert_alpha.txt"), alpha)

    # Inserção aleatória (shuffled)
    rand_insert = insert_pool[:]  # já está em ordem aleatória (após shuffle)
    write_lines(os.path.join(out, "insert_random.txt"), rand_insert)

    # Busca e remoção (sem restrição de ordem)
    write_lines(os.path.join(out, "search.txt"), search_pool)
    write_lines(os.path.join(out, "remove.txt"), remove_pool)

# ─── Inteiros (Treap e Splay) ────────────────────────────────────────────────

def gen_integers():
    print("\n[integers]")
    out = os.path.join(BASE, "integers")
    ensure_dir(out)

    N_INSERT   = 1_000_000
    N_SEARCH   = 100_000   # 10^5 para busca
    N_REMOVE   = 1_000

    # Pool de inteiros únicos
    full_range = list(range(1, N_INSERT + N_SEARCH + N_REMOVE + 1))
    random.shuffle(full_range)

    insert_pool = full_range[:N_INSERT]
    search_pool = full_range[N_INSERT : N_INSERT + N_SEARCH]
    remove_pool = full_range[N_INSERT + N_SEARCH : N_INSERT + N_SEARCH + N_REMOVE]

    # Crescente
    write_lines(os.path.join(out, "insert_asc_1M.txt"),  sorted(insert_pool))
    # Decrescente
    write_lines(os.path.join(out, "insert_desc_1M.txt"), sorted(insert_pool, reverse=True))
    # Aleatório
    rand_insert = insert_pool[:]  # já shuffled
    write_lines(os.path.join(out, "insert_random_1M.txt"), rand_insert)

    # Busca (10^5) e remoção (10^3)
    write_lines(os.path.join(out, "search_100k.txt"), search_pool)
    write_lines(os.path.join(out, "remove_1k.txt"),   remove_pool)

# ─── Pontos 2D (KD Tree) ────────────────────────────────────────────────────

def gen_kd():
    print("\n[kd]")
    out = os.path.join(BASE, "kd")
    ensure_dir(out)

    N_INSERT = 1_000_000
    N_OPS    = 1_000

    # Gera pontos 2D únicos (x, y) com coordenadas em [0, 2*N_INSERT)
    limit = 2 * N_INSERT
    points_set = set()
    while len(points_set) < N_INSERT + N_OPS * 2:
        x = random.randint(0, limit)
        y = random.randint(0, limit)
        points_set.add((x, y))
    points = list(points_set)
    random.shuffle(points)

    insert_pts = points[:N_INSERT]
    search_pts = points[N_INSERT : N_INSERT + N_OPS]
    remove_pts = points[N_INSERT + N_OPS : N_INSERT + N_OPS * 2]

    def fmt(pts):
        return [f"{x} {y}" for x, y in pts]

    write_lines(os.path.join(out, "insert_1M.txt"), fmt(insert_pts))
    write_lines(os.path.join(out, "search_1k.txt"), fmt(search_pts))
    write_lines(os.path.join(out, "remove_1k.txt"), fmt(remove_pts))

# ─── Main ────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    print("=== Gerando dados de benchmark ===")
    gen_strings()
    gen_integers()
    gen_kd()
    print("\nPronto! Todos os arquivos gerados.")
