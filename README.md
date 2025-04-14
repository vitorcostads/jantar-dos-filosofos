# Jantar dos Filósofos em C

Este projeto é uma implementação do clássico problema do **Jantar dos Filósofos** usando **threads, mutexes e semáforos em C**, como parte dos meus estudos sobre programação concorrente.

## Sobre o problema

O problema modela 5 filósofos que pensam e comem em uma mesa circular. Para comer, cada um precisa de dois garfos (um à esquerda e um à direita). O desafio é garantir que:

- Nenhum filósofo entre em deadlock
- Nenhum filósofo passe fome (starvation)
- O acesso aos garfos seja sincronizado

##  Tecnologias usadas

- Linguagem C
- POSIX Threads (`pthread`)
- Semáforos (`sem_t`)
- Linux Terminal (gcc)

## 🚀 Como compilar e executar

```bash
gcc jantar.c -o jantar -lpthread
./jantar