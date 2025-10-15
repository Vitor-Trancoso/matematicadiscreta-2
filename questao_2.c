#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main()
{
    printf("=== QUESTÃO 2 -> CHAVES PERIÓDICAS ===\n\n");

    printf("Digite o número de ciclos de chaves (N): \n");
    int n;
    scanf("%d", &n);

    int *chaves = (int *)malloc(n * sizeof(int));
    int chaves_recebidas = 0;
    int maior_chave = 0;

    printf("Digite os N ciclos de chaves :\n");
    while (chaves_recebidas != n)
    {
        chaves_recebidas++;

        int temp;
        scanf("%d", &temp);

        if (temp > maior_chave)
        {
            maior_chave = temp;
        }

        chaves[chaves_recebidas - 1] = temp;
    }

    printf("\n");

    printf("Chaves recebidas: \n");

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            printf("%d\n\n", chaves[i]);
        }
        else
        {
            printf("%d ", chaves[i]);
        }
    }

    int menor_mmc = maior_chave;
    int achou_erro = 0;
    while (menor_mmc <= 50)
    {
        achou_erro = 0;

        for (int i = 0; i < n; i++)
        {
            if (menor_mmc % chaves[i] != 0)
            {
                menor_mmc++;
                achou_erro = 1;
                break;
            }
        }
        if (achou_erro == 1)
        {
            continue;
        }

        break;
    }

    if (menor_mmc > 50)
    {
        printf("Não existe ano válido em que todas as chaves possam ser utilizadas simultaneamente dentro do limite de 50 anos.\n\n");
    }
    else
    {
        printf("Primeiro ano sincronizado dentro do limite: %d\n\n", menor_mmc);
    }

    printf("Já que o limite do N é apenas até 10, e sabendo que 2 ≤ Ci ≤ 20, a forma abaixo é bem otimizada,\n");
    printf("resultando em menos operações para encontrar o menor MMC dentre os números C0,...,Ci.\n");
    printf("O algoritmo consiste em testar todos os números entre o maior Ci até 50, testando se ele é divisível por todas as chaves C0,...,Ci.\n");
    printf("Caso seja divisível por todos, ele é o menor MMC.\n\n");

    return 0;
}