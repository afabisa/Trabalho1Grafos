# Biblioteca para manipulação de Grafos
Esse é o repositório para os trabalhos da disciplina Teoria dos Grafos (2025.2). Desenvolvido por Fabiane Sá de Oliveira e Felipe Marroni
# Como utilizar a biblioteca?

Usar os arquivos `graph_lib.cpp` e `graph_lib.h` para utilizar a biblioteca dentro do arquivo desejado. Então, basta colocar 

```
#include "graph_lib.h"
```

no começo do arquivo para que o compilador reconheça de onde estão vindo as funções que serão utilizadas.

Para compilar, precisamos também explicitar o nome do arquivo ".cpp" que contém as funções da biblioteca.

Todos os arquivos ".txt" de saída serão criados na mesma pasta em que se encontram os dois arquivos necessários para a utilização da biblioteca.

```
g++ arquivo.cpp graph_lib.cpp
```
