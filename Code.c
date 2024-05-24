#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

pthread_mutex_t mutex;
char *ruaA[5] = {"  ", "  ", "  ", "  ", "  "};
char *ruaB[5] = {"  ", "  ", "  ", "  ", "  "};
char *ruaX = "  ";
bool sinalA = false;
bool sinalB = false;
int auxA = 0, auxB = 0;

void print_semaforo()
{
    printf("Sinal A: %s\n",
           sinalA ? "\033[32mGreen\033[39m" : "\033[31mRed\033[39m");
    printf("Sinal B: %s\n",
           sinalB ? "\033[32mGreen\033[39m" : "\033[31mRed\033[39m");
}

void *transito(void *arg)
{
    while (1)
    {

        printf("\n\n");
        printf("                rua 1\n");
        printf("              +      +\n");
        printf("              |  %s  |\n", ruaA[0]);
        printf("              +------+\n");
        printf("              |  %s  |\n", ruaA[1]);
        printf("      +--+----+%s------%s+----+--+\n", sinalA ? "\033[32m" : "\033[31m", "\033[39m");
        printf("rua 4 %s | %s %s|\033[39m  %s  | %s | %s  rua 2\n", ruaB[0], ruaB[1], sinalB ? "\033[32m" : "\033[31m", ruaX, ruaB[3], ruaB[4]);
        printf("      +--+----+------+----+--+\n");
        printf("              |  %s  |\n", ruaA[3]);
        printf("              +------+\n");
        printf("              |  %s  |\n", ruaA[4]);
        printf("              +      +\n");
        printf("                rua 3\n\n\n");

        print_semaforo();

        usleep(500000);
        system("clear");
    }

    pthread_exit(0);
}

void *threadA(void *arg)
{
    while (1)
    {
        if (auxA == 0)
        {
            ruaA[4] = "  ";
            ruaA[0] = "C1";
            auxA++;
        }
        else if (auxA == 1)
        {
            ruaA[0] = "  ";
            ruaA[1] = "C1";
            auxA++;
        }
        else if (auxA == 2)
        {
            pthread_mutex_lock(&mutex);
            sinalA = true;
            sinalB = false;
            ruaA[1] = "  ";
            ruaX = "C1";
            auxA++;
            usleep(500000);
            ruaX = "  ";
            sinalA = false;
            ruaA[3] = "C1";
            auxA++;
            pthread_mutex_unlock(&mutex);
        }
        else if (auxA == 4)
        {
            ruaA[3] = "  ";
            ruaA[4] = "C1";
            auxA = 0;
        }

        usleep(500000);
    }
}

void *threadB(void *arg)
{
    while (1)
    {
        if (auxB == 0)
        {
            ruaB[4] = "  ";
            ruaB[0] = "C2";
            auxB++;
        }
        else if (auxB == 1)
        {
            ruaB[0] = "  ";
            ruaB[1] = "C2";
            auxB++;
        }
        else if (auxB == 2)
        {
            pthread_mutex_lock(&mutex);
            sinalB = true;
            sinalA = false;
            ruaB[1] = "  ";
            ruaX = "C2";
            auxB++;
            usleep(500000);
            ruaX = "  ";
            sinalB = false;
            ruaB[3] = "C2";
            auxB++;
            pthread_mutex_unlock(&mutex);
        }
        else if (auxB == 4)
        {
            ruaB[3] = "  ";
            ruaB[4] = "C2";
            auxB = 0;
        }

        usleep(500000);
    }
}

int main()
{
    system("clear");
    pthread_t t1, t2, t_transito;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t_transito, NULL, transito, NULL);
    pthread_create(&t1, NULL, threadA, NULL);
    pthread_create(&t2, NULL, threadB, NULL);

    pthread_join(t_transito, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
