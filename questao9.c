#include <stdio.h>

// Função para calcular o MDC (Algoritmo de Euclides)
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para verificar se dois números são coprimos
int coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Função para calcular o inverso modular (Algoritmo de Euclides Estendido)
int inverso_modular(int a, int n) {
    int t = 0, newt = 1;
    int r = n, newr = a;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;
        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return -1; // Não existe inverso
    if (t < 0) t += n;
    return t;
}

// Função para verificar se um número é primo
int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

// Função Totiente de Euler φ(n) sem bibliotecas prontas
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// Exponenciação modular eficiente
int exp_mod(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int H, G, n, x, n1;
    printf("Digite os valores de H, G, n, x, n1 (separados por espaço): ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\n1. Verificando se G, e, n são primos entre si (usando MDC):\n");
    printf("MDC(G, n) = %d\n", mdc(G, n));
    if (!coprimos(G, n)) {
        printf("G e n não são coprimos. A divisão modular não é possível.\n");
        return 1;
    } else {
        printf("G e n são coprimos.\n");
    }

    printf("\n2. Calculando o inverso de G em Z_n:\n");
    int Ginv = inverso_modular(G, n);
    if (Ginv == -1) {
        printf("Não existe inverso de G em Z_n.\n");
        return 1;
    } else {
        printf("O inverso de %d módulo %d é %d.\n", G, n, Ginv);
    }

    printf("\n3. Dividindo H por G em Z_n para encontrar a base a:\n");
    int a = (H * Ginv) % n;
    printf("a = (H * G^-1) mod n = (%d * %d) mod %d = %d\n", H, Ginv, n, a);

    printf("\n4. Verificando se a e n1 são coprimos:\n");
    if (!coprimos(a, n1)) {
        printf("a e n1 não são coprimos. Não é possível prosseguir.\n");
        return 1;
    } else {
        printf("a e n1 são coprimos.\n");
    }

    printf("\n5. Verificando se n1 é primo:\n");
    int n1_primo = eh_primo(n1);
    if (n1_primo)
        printf("n1 é primo.\n");
    else
        printf("n1 não é primo.\n");

    int x1;
    if (n1_primo) {
        printf("\n6. Aplicando o Pequeno Teorema de Fermat: x1 = n1 - 1\n");
        x1 = n1 - 1;
    } else {
        printf("\n6. Aplicando o Teorema de Euler: x1 = phi(n1)\n");
        x1 = phi(n1);
        printf("phi(%d) = %d\n", n1, x1);
    }

    printf("\n7. Decompondo x na forma x = x1 * q + r:\n");
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\n8. Reescrevendo a^x mod n1 como (((a^x1)^q mod n1) * (a^r mod n1)) mod n1\n");

    int ax1 = exp_mod(a, x1, n1);
    int ax1q = exp_mod(ax1, q, n1);
    int ar = exp_mod(a, r, n1);
    int resultado = ( (long long)ax1q * ar ) % n1;

    printf("\n9. Calculando valores intermediários:\n");
    printf("a^x1 mod n1 = %d\n", ax1);
    printf("(a^x1)^q mod n1 = %d\n", ax1q);
    printf("a^r mod n1 = %d\n", ar);

    printf("\n10. Resultado final: ((a^x1)^q * a^r) mod n1 = %d\n", resultado);

    printf("\nExplicação matemática detalhada impressa acima.\n");
    return 0;
} 