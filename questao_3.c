#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Tau: conta o número total de divisores de N

int tau(int *fatores_primos, int tamanho_fatores_primos)
{
    int divisores = 0;
    for (int i = 0; i < tamanho_fatores_primos; i++)
    {
        if (fatores_primos[i] != 0)
        {
            divisores++;
        }
    }

    return divisores;
}

// Sigma: calcula a soma de todos os divisores de N.

int sigma(int *fatores_primos, int *primos_ate_200, int tamanho_fatores_primos)
{
    int somaDivisores = 0;

    for (int i = 0; i < tamanho_fatores_primos; i++)
    {
        if (fatores_primos[i] != 0)
        {
            somaDivisores += primos_ate_200[i];
        }
    }

    return somaDivisores;
}

int main()
{
    int primos_ate_200[27] = {
        2,
        3,
        5,
        7,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        37,
        41,
        43,
        47,
        53,
        59,
        61,
        67,
        71,
        73,
        79,
        83,
        89,
        97,
        101,
        103,
    };

    int n;

    int fatores_primos[27];

    printf("Digite o número N escolhido para calcularmos a Razão de Eficiência: \n");

    scanf("%d", &n);

    for (int i = 0; i < 27; i++)
    {
        if (n % primos_ate_200[i] == 0)
        {
            fatores_primos[i] = 1;
        }
        else
        {
            fatores_primos[i] = 0;
        }
    }

    int valorTau = tau(fatores_primos, 27);
    int valorSigma = sigma(fatores_primos, primos_ate_200, 27);

    double razaoDeEficiencia = (double)valorSigma / (double)valorTau;

    printf("%.2lf\n", razaoDeEficiencia);
}