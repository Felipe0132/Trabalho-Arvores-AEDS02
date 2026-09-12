# Implementação e Análise de Estruturas de Árvores Avançadas

Este repositório contém a implementação em **C++** e a análise experimental de cinco estruturas de dados hierárquicas não convencionais. O objetivo é explorar alternativas às tradicionais árvores de busca (como BST e AVL), analisando suas complexidades, aplicações e desempenho prático frente a diferentes massas de dados.

**Autor:** Felipe Silva (Engenharia de Computação, CEFET-MG)

---

## 🌳 Estruturas Implementadas

1. **Árvore PATRICIA (Radix Tree Compacta):** Otimiza o armazenamento de *strings* através da compressão de caminhos e compartilhamento de prefixos. Evita a alocação de nós desnecessários ao agrupar caracteres consecutivos.
2. **Árvore Trie (Árvore de Prefixos):** Decompõe chaves em caracteres individuais, navegando nó a nó. Muito útil para mecanismos de busca e autocompletar.
3. **Árvore Treap (Tree + Heap):** Combina propriedades de BST com balanceamento probabilístico (*Heap*) por meio de prioridades aleatórias (estocásticas). Evita a degradação de desempenho sem depender de pesadas regras de rotação explícita como a AVL.
4. **Árvore Splay:** Árvore autoajustável baseada na heurística de localidade temporal. A cada acesso, o nó é movido para a raiz (operação *Splay*), garantindo eficiência $O(1)$ amortizada para consultas repetitivas.
5. **KD-Tree (k-dimensional Tree):** Focada no particionamento espacial de dados multidimensionais (neste escopo, 2D). Crucial em problemas de geometria computacional e buscas de vizinhos próximos (*k-NN*).

---

## 🚀 Resultados e Benchmarks

Os testes empíricos foram realizados submetendo as árvores a cenários de estresse de até **1.000.000 (10⁶) inserções** e **1.000 a 100.000 operações de busca**. As métricas coletadas refletem as forças teóricas de cada árvore na prática.

### PATRICIA vs Trie (Processamento de *Strings*)
* A **PATRICIA** foi cerca de **2× mais rápida** na inserção de dados alfabéticos, provando a eficácia da compactação de prefixos contínuos.
* Por outro lado, a **Trie** foi mais eficiente na inserção de dados **aleatórios**, pois dados muito divergentes obrigam a PATRICIA a realizar custosas operações de fracionamento de nós (*splits*).

### Treap vs Splay (Heurísticas e Balanceamento)
* **Inserção Ordenada (Pior caso de BST):** A **Splay** demonstrou uma superioridade esmagadora (redução de até **98.8%** do tempo frente à Treap). Sendo autoajustável e não precisando gerar pesos estocásticos, suas rotações locais lidaram melhor com os dados sequenciais.
* **Busca Repetitiva:** Em uma consulta ao **mesmo elemento** 100.000 vezes, a **Splay** resolveu a tarefa quase instantaneamente ($0ms$). Após a 1ª busca, a heurística promove o nó para a raiz, atestando o custo $O(1)$. A Treap, por exigir travessia, demorou significativamente mais.

### KD-Tree
* Mais de **99%** do tempo consumido ficou na etapa inicial de construção (*build* espacial de 1 milhão de pontos). Entretanto, as consultas e remoções alcançaram altíssima performance, com buscas resolvendo-se na casa de $\approx 2ms$.

---

## 📂 Estrutura do Projeto

O código está isolado, padronizado e organizado para simplificar a visualização técnica:

```text
├── data/
│   └── gen_data.py          # Script Python (gera os 1M de chaves/pontos .txt)
├── output/                  # Registro final de tempo das execuções 
├── trees/
│   ├── KD Tree/
│   │   ├── include/         # .hpp
│   │   ├── src/             # .cpp (main e implementação)
│   │   └── Makefile         # Automação de compilação
│   ├── PATRICIA Tree/       # Mesmo padrão
│   ├── Splay Tree/          # Mesmo padrão
│   ├── Treap/               # Mesmo padrão
│   └── Trie Tree/           # Mesmo padrão
├── run_all.sh               # Pipeline Bash que executa todo o projeto
└── README.md
```

---

## ⚙️ Como Executar

O projeto possui um *pipeline* completamente automatizado via *Shell Script*. Ele encarrega-se de gerar os dados, compilar (usando `-O2`) e executar o *benchmark* de todas as árvores na sequência.

**Pré-requisitos:**
* Compilador `g++` com suporte a `C++20`
* `Python 3` (para o script de carga)
* `make`

**Passo a passo:**
```bash
# 1. Dê permissão de execução ao script automatizado
chmod +x run_all.sh

# 2. Inicie a compilação e simulação
./run_all.sh

# 3. Verifique os relatórios consolidados em:
cat output/output.txt
```

Para rodar e testar estruturas individuais, basta entrar no respectivo subdiretório:
```bash
cd "trees/Splay Tree"
make
./src/output/splay
```
