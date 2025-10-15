#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


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

// Exponenciação modular com aplicação automática de teoremas
int exp_mod_teorema(int base, int exp, int mod, int z, int eh_primo_mod) {
    printf("Aplicando exponenciação modular: %d^%d mod %d\n", base, exp, mod);

    // Verificar condições para aplicar teoremas
    int mdc_base_mod = mdc(base, mod);
    int teorema_aplicado = 0;
    int exp_reduzido = exp;

    // 1. Se mod é primo, aplicar Pequeno Teorema de Fermat
    if (eh_primo_mod) {
        printf("  -> Aplicando Pequeno Teorema de Fermat (mod é primo)\n");
        printf("  -> exp reduzido: %d mod (%d-1) = %d mod %d = %d\n",
               exp, mod, exp, mod-1, exp % (mod-1));
        exp_reduzido = exp % (mod - 1);
        teorema_aplicado = 1;
    }
    // 2. Se mdc(base, mod) = 1, aplicar Teorema de Euler
    else if (mdc_base_mod == 1) {
        printf("  -> Aplicando Teorema de Euler (mdc(%d, %d) = 1)\n", base, mod);
        printf("  -> exp reduzido: %d mod φ(%d) = %d mod %d = %d\n",
               exp, mod, exp, z, exp % z);
        exp_reduzido = exp % z;
        teorema_aplicado = 2;
    }
    // 3. Caso contrário, aplicar Teorema da Divisão Euclidiana para reduzir expoente
    else {
        printf("  -> Aplicando Teorema da Divisão Euclidiana para reduzir expoente\n");
        printf("  -> mdc(%d, %d) = %d ≠ 1, reduzindo expoente diretamente\n", base, mod, mdc_base_mod);
        // Redução simples do expoente
        while (exp_reduzido >= mod) {
            exp_reduzido -= mod;
        }
        teorema_aplicado = 3;
    }

    printf("  -> Teorema aplicado: %d, Expoente reduzido: %d\n", teorema_aplicado, exp_reduzido);

    // Calcular exponenciação modular com expoente reduzido
    int result = 1;
    base = base % mod;
    int original_exp = exp_reduzido;

    printf("  -> Calculando %d^%d mod %d passo a passo:\n", base, exp_reduzido, mod);

    while (exp_reduzido > 0) {
        if (exp_reduzido % 2 == 1) {
            printf("     %d = (%d * %d) mod %d\n", (result * base) % mod, result, base, mod);
            result = (result * base) % mod;
        }
        exp_reduzido = exp_reduzido >> 1;
        if (exp_reduzido > 0) {
            printf("     base = (%d * %d) mod %d = %d\n", base, base, mod, (base * base) % mod);
            base = (base * base) % mod;
        }
    }

    printf("  -> Resultado: %d^%d mod %d = %d\n\n", base, original_exp, mod, result);
    return result;
}

// Exponenciação modular eficiente (versão simplificada para uso interno)
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

// Função de iteração para o método ρ de Pollard: g(x) = (x² + 1) mod n
int iteracao_pollard(int x, int n1) {
    return ((x * x) + 1) % n1;
}

// Funcao para implementacao do metodo ρ de Pollard
int pollard(int ni){
    printf("Método ρ de Pollard para %d\n", ni);
    printf("Função de iteração: g(x) = (x^2 + 1) mod Ni\n");
    printf("Semente: x0 = 2\n");

    int x = 2;
    int y = 2;
    int d = 1;
    int iteracao = 0;

    // Verificar se x0 e ni são coprimos
    int mdc_x0_ni = mdc(x, ni);
    printf("Verificação inicial para garantir que o mdc de x0 e ni é = 1: mdc(%d, %d) = %d\n", x, ni, mdc_x0_ni);

    if (mdc_x0_ni > 1) {
        printf("MDC não é igual a 1, retornando o mdc(x0,ni).\n");
        return mdc_x0_ni;
    }

    printf("Iniciando iterações:\n");

    while (d == 1) {
        iteracao++;
        x = iteracao_pollard(x, ni);  // x = g(x)
        y = iteracao_pollard(iteracao_pollard(y, ni), ni);  // y = g(g(y))

        d = mdc(abs(x - y), ni);

        printf("Iteração %d: x = %d, y = %d, |x-y| = %d, mdc(|x-y|, %d) = %d\n",
               iteracao, x, y, abs(x - y), ni, d);

        if (iteracao > 1000) {  // Prevenção de loop infinito
            printf("Limite de iterações atingido. Retornando -1.\n");
            return -1;
        }
    }

    if (d == ni) {
        printf("Falha: d = ni. Tente outra semente.\n");
        return -1;
    }

    printf("\nFator primo encontrado: %d\n", d);
    printf("Verificação: %d * %d = %d\n\n", d, ni/d, d * (ni/d));
    return d;
}


// Função para pré-codificar um caractere (A=11, B=12, ..., Z=36, espaço=00)
int pre_codificar_caractere(char c) {
    if (c == ' ') return 0;  // Espaço = 00 (mas retornamos 0 para processamento)
    if (isalpha(c)) {
        c = toupper(c);
        return (c - 'A') + 11;  // A=11, B=12, ..., Z=36
    }
    return -1;  // Caractere inválido
}

// Função para decodificar um número em caractere
char decodificar_numero(int num) {
    if (num == 0) return ' ';
    if (num >= 11 && num <= 36) {
        return 'A' + (num - 11);
    }
    return '?';  // Número inválido
}

// Função para pré-codificar uma mensagem completa
void pre_codificar_mensagem(char *mensagem, int *codigos, int *tamanho) {
    *tamanho = 0;
    for (int i = 0; mensagem[i] != '\0'; i++) {
        int codigo = pre_codificar_caractere(mensagem[i]);
        if (codigo != -1) {
            codigos[*tamanho] = codigo;
            (*tamanho)++;
        }
    }
}

// Função para decodificar códigos em mensagem
void decodificar_mensagem(int *codigos, int tamanho, char *mensagem) {
    for (int i = 0; i < tamanho; i++) {
        mensagem[i] = decodificar_numero(codigos[i]);
    }
    mensagem[tamanho] = '\0';
}

// Função para criptografar um bloco usando RSA
int criptografar_bloco(int m, int e, int n, int z) {
    printf("Criptografando bloco M = %d com chave pública (%d, %d):\n", m, n, e);
    printf("Fórmula: C ≡ M^e mod n\n");
    int eh_primo_n = eh_primo(n);
    int c = exp_mod_teorema(m, e, n, z, eh_primo_n);
    printf("Bloco criptografado C = %d\n\n", c);
    return c;
}

// Função para descriptografar um bloco usando RSA
int descriptografar_bloco(int c, int d, int n, int z) {
    printf("Descriptografando bloco C = %d com chave privada (%d, %d):\n", c, n, d);
    printf("Fórmula: M ≡ C^d mod n\n");
    int eh_primo_n = eh_primo(n);
    int m = exp_mod_teorema(c, d, n, z, eh_primo_n);
    printf("Bloco descriptografado M = %d\n\n", m);
    return m;
}

// Função para validar entrada dos números N1 e N2
void validar_entrada(int *n1, int *n2) {
    do {
        printf("Digite o numero N1 (entre 100 e 9999): ");
        scanf("%d", n1);
        if (*n1 < 100 || *n1 > 9999) {
            printf("N1 deve estar entre 100 e 9999.\n");
        }
    } while (*n1 < 100 || *n1 > 9999);

    do {
        printf("Digite o numero N2 (entre 100 e 9999, diferente de N1): ");
        scanf("%d", n2);
        if (*n2 < 100 || *n2 > 9999) {
            printf("N2 deve estar entre 100 e 9999.\n");
        } else if (*n2 == *n1) {
            printf("N2 deve ser diferente de N1.\n");
            *n2 = 0; // Força nova leitura
        }
    } while (*n2 < 100 || *n2 > 9999 || *n2 == *n1);
}

int main() {
    printf("=== QUESTÃO 1 -> SISTEMA RSA COM FATORAÇÃO P DE POLLARD ===\n\n");
    printf("Sabendo que cada Ni deve ser produto de primos distintos,\n");
    printf("garantindo que o metodo ρ de Pollard seja eficiente:\n");

    int n1, n2;
    validar_entrada(&n1, &n2);

    printf("\nNumeros inseridos: N1 = %d, N2 = %d\n\n", n1, n2);

    // Etapa 1: Fatoração usando método ρ de Pollard
    printf("=== ETAPA 1: FATORACAO USANDO METODO ρ DE POLLARD ===\n\n");

    int p = pollard(n1);
    if (p == -1) {
        printf("Erro na fatoração de N1. Abortando.\n");
        return 1;
    }

    int q = pollard(n2);
    if (q == -1) {
        printf("Erro na fatoração de N2. Abortando.\n");
        return 1;
    }

    printf("Fatores primos encontrados:\n");
    printf("p (fator de N1) = %d\n", p);
    printf("q (fator de N2) = %d\n\n", q);

    // Etapa 2: Geração das Chaves RSA
    printf("=== ETAPA 2: GERACAO DAS CHAVES RSA ===\n\n");

    // Cálculo do módulo n = p × q
    int n = p * q;
    printf("Calculo do modulo n = p × q = %d × %d = %d\n", p, q, n);

    // Cálculo do totiente de Euler z(n) = (p-1) × (q-1)
    int z = (p - 1) * (q - 1);
    printf("Totiente de Euler z(n) = (p-1) × (q-1) = (%d-1) × (%d-1) = %d × %d = %d\n",
           p, q, p-1, q-1, z);

    // Escolha do expoente público E (menor E > 1 tal que mdc(E, z(n)) = 1)
    int e = 2;
    while (!coprimos(e, z)) {
        e++;
        if (e >= z) {
            printf("Erro: Não foi possível encontrar expoente público válido.\n");
            return 1;
        }
    }
    printf("Expoente publico E (menor E > 1 coprimo com z(n)): E = %d\n", e);
    printf("Verificacao: mdc(%d, %d) = %d\n", e, z, mdc(e, z));

    // Cálculo do expoente privado d (inverso modular de e mod z)
    printf("\nCalculo do expoente privado d (inverso modular de e mod z):\n");
    int d = inverso_modular(e, z);
    if (d == -1) {
        printf("Erro: Não foi possível calcular o inverso modular.\n");
        return 1;
    }
    printf("d ≡ e^(-1) mod z\n");
    printf("d = %d\n", d);
    printf("Verificacao: (%d × %d) mod %d = %d\n", e, d, z, (e * d) % z);

    // Impressão das chaves
    printf("\n=== CHAVES RSA GERADAS ===\n");
    printf("Chave publica: (%d, %d)\n", n, e);
    printf("Chave privada: (%d, %d)\n\n", n, d);

    // Etapa 3: Criptografia e Descriptografia
    printf("=== ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA ===\n\n");

    // Entrada da mensagem
    char mensagem_original[1000];
    printf("Digite a mensagem para criptografar (apenas letras e espaços): ");
    getchar(); // Consumir o newline pendente
    fgets(mensagem_original, sizeof(mensagem_original), stdin);
    // Remover newline do final
    mensagem_original[strcspn(mensagem_original, "\n")] = 0;

    printf("Mensagem original: \"%s\"\n\n", mensagem_original);

    // Pré-codificação da mensagem
    printf("=== PRÉ-CODIFICAÇÃO DA MENSAGEM ===\n");
    printf("Sistema: A=11, B=12, ..., Z=36, espaço=00\n\n");

    int codigos[1000];
    int tamanho_mensagem;
    pre_codificar_mensagem(mensagem_original, codigos, &tamanho_mensagem);

    printf("Mensagem pré-codificada: ");
    for (int i = 0; i < tamanho_mensagem; i++) {
        printf("%02d ", codigos[i]);
    }
    printf("\n\n");

    // Criptografia
    printf("=== CRIPTOGRAFIA ===\n");
    int blocos_criptografados[1000];
    for (int i = 0; i < tamanho_mensagem; i++) {
        blocos_criptografados[i] = criptografar_bloco(codigos[i], e, n, z);
    }

    printf("Mensagem criptografada completa: ");
    for (int i = 0; i < tamanho_mensagem; i++) {
        printf("%d ", blocos_criptografados[i]);
    }
    printf("\n\n");

    // Descriptografia
    printf("=== DESCRIPTOGRAFIA ===\n");
    int blocos_descriptografados[1000];
    for (int i = 0; i < tamanho_mensagem; i++) {
        blocos_descriptografados[i] = descriptografar_bloco(blocos_criptografados[i], d, n, z);
    }

    printf("Blocos descriptografados: ");
    for (int i = 0; i < tamanho_mensagem; i++) {
        printf("%02d ", blocos_descriptografados[i]);
    }
    printf("\n\n");

    // Reconversão para texto
    char mensagem_descriptografada[1000];
    decodificar_mensagem(blocos_descriptografados, tamanho_mensagem, mensagem_descriptografada);

    printf("=== RESULTADO FINAL ===\n");
    printf("Mensagem descriptografada: \"%s\"\n", mensagem_descriptografada);

    // Verificação de integridade
    if (strcmp(mensagem_original, mensagem_descriptografada) == 0) {
        printf("✓ SUCESSO: A mensagem descriptografada é idêntica à mensagem original!\n");
    } else {
        printf("✗ ERRO: A mensagem descriptografada não corresponde à original.\n");
    }

    printf("\n=== FIM DO SISTEMA RSA ===\n");

    return 0;
}