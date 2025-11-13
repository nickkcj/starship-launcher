# Tutorial: C++ Básico para quem sabe Python/Java

## 1. Compilação vs Interpretação

**Python/Java**: Código é interpretado ou compilado em bytecode em tempo de execução
**C++**: Código é compilado diretamente para código de máquina antes de executar

```bash
# Compilar um programa C++
g++ -o programa programa.cpp
# Executar
./programa
```

## 2. Tipos de Dados

### Declaração de Variáveis

```cpp
// C++ - tipo vem ANTES do nome
int idade = 25;
double altura = 1.75;
std::string nome = "Maria";
bool ativo = true;

// Python (para comparação)
// idade = 25
// altura = 1.75
// nome = "Maria"
```

### Tipos Principais
- `int` - inteiro (4 bytes)
- `long` - inteiro longo (8 bytes)
- `float` - ponto flutuante (4 bytes)
- `double` - ponto flutuante dupla precisão (8 bytes)
- `char` - caractere único
- `bool` - booleano (true/false)

## 3. Ponteiros - O CONCEITO MAIS IMPORTANTE!

**Ponteiro**: uma variável que armazena um ENDEREÇO de memória

```cpp
int x = 10;        // x é uma variável normal com valor 10
int* ptr = &x;     // ptr é um PONTEIRO que guarda o ENDEREÇO de x
                   // & significa "endereço de"

// Para acessar o valor através do ponteiro:
int valor = *ptr;  // * significa "valor apontado por" (dereferencing)
                   // valor agora é 10

// Modificar através do ponteiro:
*ptr = 20;         // Agora x vale 20!
```

**Por que ponteiros são importantes?**
- Em C++, quando passa uma variável para função, copia o valor (como Java com primitivos)
- Com ponteiros, você passa o ENDEREÇO, permitindo modificar o original
- Threads precisam compartilhar dados = ponteiros!

## 4. Referências (alternativa mais segura)

```cpp
int x = 10;
int& ref = x;      // ref é uma REFERÊNCIA a x (apelido)

ref = 20;          // x agora vale 20
                   // Mais simples que ponteiros, mas similar
```

## 5. Structs - Estruturas de Dados

```cpp
// Similar a classes em Python/Java, mas mais simples
struct Nave {
    int x;
    int y;
    int velocidade;
    bool ativa;
};

// Criar e usar:
Nave nave1;
nave1.x = 100;
nave1.y = 0;
nave1.velocidade = 5;

// Com ponteiro:
Nave* pNave = &nave1;
pNave->x = 200;    // -> é usado com ponteiros (equivale a (*pNave).x)
```

## 6. Arrays

```cpp
// Array de tamanho fixo
int numeros[5] = {1, 2, 3, 4, 5};
numeros[0] = 10;

// Array dinâmico (alocação manual)
int* arr = new int[10];    // Aloca memória para 10 inteiros
arr[0] = 5;
delete[] arr;              // IMPORTANTE: liberar memória!

// Ou usar std::vector (similar a lista do Python)
#include <vector>
std::vector<int> lista;
lista.push_back(10);       // Adicionar elemento
lista.push_back(20);
int primeiro = lista[0];
```

## 7. Funções

```cpp
// Protótipo (declaração)
int somar(int a, int b);

// Implementação
int somar(int a, int b) {
    return a + b;
}

// Passar por referência (permite modificar)
void incrementar(int& valor) {
    valor++;
}

int x = 10;
incrementar(x);  // x agora é 11

// Passar por ponteiro
void incrementar2(int* valor) {
    (*valor)++;
}
incrementar2(&x);  // x agora é 12
```

## 8. Gerenciamento de Memória

**SUPER IMPORTANTE!** Em C++, você é responsável pela memória

```cpp
// Alocar
int* ptr = new int;
*ptr = 42;

// SEMPRE liberar quando não precisar mais
delete ptr;

// Para arrays:
int* arr = new int[100];
delete[] arr;  // Note o []

// NÃO liberar = memory leak (vazamento de memória)
```

## 9. Headers e Implementação

C++ separa declaração (`.h`) de implementação (`.cpp`)

**arquivo.h** (header):
```cpp
#ifndef ARQUIVO_H
#define ARQUIVO_H

struct Nave {
    int x, y;
};

void moverNave(Nave* nave);

#endif
```

**arquivo.cpp** (implementação):
```cpp
#include "arquivo.h"

void moverNave(Nave* nave) {
    nave->y++;
}
```

## 10. Compilação de Múltiplos Arquivos

```bash
# Compilar separadamente
g++ -c arquivo1.cpp -o arquivo1.o
g++ -c arquivo2.cpp -o arquivo2.o

# Linkar tudo
g++ arquivo1.o arquivo2.o -o programa

# Ou tudo de uma vez
g++ arquivo1.cpp arquivo2.cpp -o programa
```

## Comparação Rápida: Python vs C++

| Python | C++ |
|--------|-----|
| `x = 10` | `int x = 10;` |
| `def func():` | `void func() {` |
| `lista = []` | `std::vector<int> lista;` |
| `lista.append(5)` | `lista.push_back(5);` |
| `for item in lista:` | `for(auto item : lista) {` |
| Garbage collector | delete manual |

## Próximo Passo

Agora que você entende o básico, vamos para **pthreads** (threads POSIX)!
