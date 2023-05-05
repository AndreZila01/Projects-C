# Programação e Algoritmos 2022 2023 - [IADE - UE](https://www.iade.europeia.pt/) <!-- omit in toc -->

## Lista de Tarefas

Pretende-se um programa que permite o registo, consulta, e execução de tarefas pessoais.

## Instruções

- `RT Descrição`: Permite registar uma tarefa, e responde com um identificador único para a tarefa.
- `LT` : Permite listar todas as tarefas registadas.
- `MT IdTarefa`: Permite marcar uma tarefa como *completa*. Precisa do identificador único da tarefa a marcar.
- `Q`: Termina o programa.

## Compilação

    gcc -c models/tasks.c
    gcc -c controllers/task_list.c
    gcc -c views/cli.c
    gcc -o main tasks.o task_list.o cli.o main.c

Alternativa

    gcc -Wall -g models/tasks.h models/tasks.c controllers/task_list.h controllers/task_list.c views/cli.h views/cli.c main.c -o main

## Por completar

- [ ] Retirar a limitação de 10 tarefas;
- [ ] Permitir eliminar tarefas;
- [ ] Permitir listar tarefas ordenadamente por estado, id, ou descrição.
