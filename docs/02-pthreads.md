# Tutorial: Pthreads (POSIX Threads)

## O que são Threads?

**Thread** = linha de execução independente dentro de um programa

**Processo vs Thread**:
- Processo: programa completo com sua própria memória
- Thread: "mini-programa" dentro de um processo, compartilha memória

**No nosso jogo**:
- Thread 1: Renderiza a tela
- Thread 2: Spawn de naves
- Thread 3, 4, 5...: Cada nave se movendo
- Threads N+: Cada foguete voando
- Thread final: Carregador de foguetes

## 1. Criar e Executar uma Thread

```cpp
#include <pthread.h>
#include <iostream>

// Função que a thread vai executar
// DEVE retornar void* e receber void*
void* minhaFuncao(void* arg) {
    std::cout << "Thread executando!\n";
    return nullptr;
}

int main() {
    pthread_t thread_id;  // ID da thread

    // Criar thread: pthread_create(&id, atributos, função, argumentos)
    pthread_create(&thread_id, nullptr, minhaFuncao, nullptr);

    // Esperar thread terminar
    pthread_join(thread_id, nullptr);

    std::cout << "Thread terminou!\n";
    return 0;
}
```

**Compilar com pthread**:
```bash
g++ -pthread programa.cpp -o programa
```

## 2. Passar Argumentos para Thread

```cpp
struct DadosThread {
    int id;
    std::string nome;
};

void* funcaoThread(void* arg) {
    // Converter void* de volta para o tipo correto
    DadosThread* dados = (DadosThread*)arg;

    std::cout << "Thread " << dados->id << ": " << dados->nome << "\n";
    return nullptr;
}

int main() {
    pthread_t t1, t2;
    DadosThread dados1 = {1, "Primeira"};
    DadosThread dados2 = {2, "Segunda"};

    pthread_create(&t1, nullptr, funcaoThread, &dados1);
    pthread_create(&t2, nullptr, funcaoThread, &dados2);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    return 0;
}
```

## 3. Problema: Race Condition (Condição de Corrida)

Quando múltiplas threads acessam a mesma variável:

```cpp
int contador = 0;  // Variável COMPARTILHADA

void* incrementar(void* arg) {
    for(int i = 0; i < 100000; i++) {
        contador++;  // PERIGO! Múltiplas threads acessando
    }
    return nullptr;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, incrementar, nullptr);
    pthread_create(&t2, nullptr, incrementar, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    // Esperado: 200000
    // Real: ~150000 (varia!)  <-- PROBLEMA!
    std::cout << "Contador: " << contador << "\n";
    return 0;
}
```

**Por que isso acontece?** `contador++` não é atômico:
1. Ler valor de contador
2. Incrementar
3. Escrever de volta

Thread 1 e 2 podem ler o mesmo valor ao mesmo tempo!

## 4. Solução: Mutex (Mutual Exclusion)

**Mutex** = fechadura para proteger código

```cpp
#include <pthread.h>
#include <iostream>

int contador = 0;
pthread_mutex_t mutex;  // Declarar mutex

void* incrementar(void* arg) {
    for(int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);    // TRANCAR (lock)
        contador++;                    // Seção crítica (só 1 thread por vez)
        pthread_mutex_unlock(&mutex);  // DESTRANCAR (unlock)
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);  // INICIALIZAR mutex

    pthread_t t1, t2;
    pthread_create(&t1, nullptr, incrementar, nullptr);
    pthread_create(&t2, nullptr, incrementar, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    pthread_mutex_destroy(&mutex);  // DESTRUIR mutex

    std::cout << "Contador: " << contador << "\n";  // Agora = 200000!
    return 0;
}
```

## 5. Variáveis de Condição (Condition Variables)

**Problema**: Como fazer uma thread ESPERAR até que algo aconteça?

**Exemplo do jogo**: Carregador deve parar se todos lançadores estão cheios

```cpp
#include <pthread.h>
#include <iostream>
#include <unistd.h>

int foguetes = 0;
const int MAX_FOGUETES = 5;
pthread_mutex_t mutex;
pthread_cond_t condicao;  // Variável de condição

// Thread que carrega foguetes
void* carregador(void* arg) {
    while(true) {
        pthread_mutex_lock(&mutex);

        // Esperar até ter espaço
        while(foguetes >= MAX_FOGUETES) {
            std::cout << "Carregador esperando... (cheio)\n";
            pthread_cond_wait(&condicao, &mutex);  // ESPERA e LIBERA mutex
        }

        // Carregar foguete
        foguetes++;
        std::cout << "Carregou! Total: " << foguetes << "\n";

        pthread_mutex_unlock(&mutex);
        sleep(1);  // Simula tempo de carregamento
    }
    return nullptr;
}

// Thread que dispara foguetes
void* atirador(void* arg) {
    while(true) {
        sleep(2);  // Espera 2s entre disparos

        pthread_mutex_lock(&mutex);

        if(foguetes > 0) {
            foguetes--;
            std::cout << "Disparou! Restam: " << foguetes << "\n";
            pthread_cond_signal(&condicao);  // ACORDAR carregador
        }

        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condicao, nullptr);

    pthread_t t_carregador, t_atirador;
    pthread_create(&t_carregador, nullptr, carregador, nullptr);
    pthread_create(&t_atirador, nullptr, atirador, nullptr);

    pthread_join(t_carregador, nullptr);
    pthread_join(t_atirador, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condicao);

    return 0;
}
```

## 6. Padrão Comum: Dados Compartilhados

```cpp
// Estrutura para compartilhar entre threads
struct EstadoJogo {
    std::vector<Nave*> naves;
    std::vector<Foguete*> foguetes;
    int lancadores[5];  // 0 = vazio, 1 = carregado
    bool jogoAtivo;
    pthread_mutex_t mutex;
    pthread_cond_t condicaoCarregador;
};

void* threadNave(void* arg) {
    EstadoJogo* estado = (EstadoJogo*)arg;

    while(estado->jogoAtivo) {
        pthread_mutex_lock(&estado->mutex);
        // Modificar estado...
        pthread_mutex_unlock(&estado->mutex);

        usleep(16667);  // ~60 FPS
    }
    return nullptr;
}
```

## 7. Boas Práticas

1. **Sempre inicializar/destruir**:
```cpp
pthread_mutex_init(&mutex, nullptr);
// usar...
pthread_mutex_destroy(&mutex);
```

2. **Lock/Unlock em pares**:
```cpp
pthread_mutex_lock(&mutex);
// fazer algo
pthread_mutex_unlock(&mutex);  // NUNCA esquecer!
```

3. **Seção crítica curta**:
```cpp
// BOM: lock apenas o necessário
pthread_mutex_lock(&mutex);
contador++;
pthread_mutex_unlock(&mutex);
processarDados();  // Não precisa de lock

// RUIM: lock tudo
pthread_mutex_lock(&mutex);
contador++;
processarDados();  // Trava outras threads desnecessariamente
pthread_mutex_unlock(&mutex);
```

4. **Cuidado com Deadlock**:
```cpp
// DEADLOCK: cada thread espera a outra
Thread 1: lock(A) -> espera lock(B)
Thread 2: lock(B) -> espera lock(A)
// NENHUMA progride!

// Solução: sempre travar na mesma ordem
Thread 1: lock(A) -> lock(B) -> unlock(B) -> unlock(A)
Thread 2: lock(A) -> lock(B) -> unlock(B) -> unlock(A)
```

## 8. Resumo para o Projeto

**Para o jogo, você vai precisar**:

1. **pthread_create**: Criar threads de naves, foguetes, carregador
2. **pthread_mutex**: Proteger listas de naves/foguetes, array de lançadores
3. **pthread_cond**: Carregador esperar quando lançadores cheios
4. **pthread_join**: Esperar threads terminarem no fim do jogo

## Compilação

```bash
# SEMPRE adicionar -pthread
g++ -pthread -std=c++11 arquivo.cpp -o programa
```

## Próximo Passo

Agora vamos ver um **exemplo prático completo** combinando tudo isso!
