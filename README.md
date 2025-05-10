# Questão 9 - Verificação Modular e Exponenciação Modular em C

## Objetivo

Este programa implementa uma função de segurança baseada em verificação modular, utilizando conceitos de congruência, coprimalidade, primalidade, Pequeno Teorema de Fermat, Teorema de Euler e exponenciação modular eficiente. O objetivo é calcular a expressão \( a^x \mod n_1 \), onde a base \( a \) é obtida por uma divisão modular especial, conforme descrito no enunciado.

## Requisitos Matemáticos

O programa segue os seguintes passos matemáticos:

1. **Verifica se G e n são coprimos** usando o Algoritmo de Euclides (MDC).
2. **Calcula o inverso modular de G em Zₙ** usando o Algoritmo de Euclides Estendido.
3. **Obtém a base a** como \( a = (H \times G^{-1}) \mod n \).
4. **Verifica se a e n₁ são coprimos**.
5. **Verifica se n₁ é primo**.
6. **Define x₁**:
   - Se n₁ é primo, \( x_1 = n_1 - 1 \) (Pequeno Teorema de Fermat).
   - Caso contrário, \( x_1 = \varphi(n_1) \) (função totiente de Euler, implementada manualmente).
7. **Decompõe x** na forma \( x = x_1 \times q + r \).
8. **Reescreve a expressão** \( a^x \mod n_1 \) como \( (((a^{x_1})^q \mod n_1) \times (a^r \mod n_1)) \mod n_1 \).
9. **Calcula os valores intermediários** e imprime o resultado final, detalhando cada etapa.

## Funcionamento do Código

O programa é totalmente comentado e imprime explicações matemáticas detalhadas para cada etapa do cálculo, facilitando o entendimento do processo.

### Principais funções implementadas:
- `mdc(a, b)`: Calcula o máximo divisor comum (MDC) de dois números.
- `inverso_modular(a, n)`: Calcula o inverso modular de `a` em relação a `n`.
- `eh_primo(n)`: Verifica se um número é primo.
- `phi(n)`: Calcula a função totiente de Euler de `n` sem usar bibliotecas prontas.
- `exp_mod(base, exp, mod)`: Realiza exponenciação modular eficiente.

## Como compilar e executar

1. Compile o programa:
   ```bash
   gcc questao9.c -o questao9
   ```
2. Execute o programa:
   ```bash
   ./questao9
   ```
3. Siga as instruções na tela e insira os valores solicitados (H, G, n, x, n1).

## Exemplo de uso

```
Digite os valores de H, G, n, x, n1 (separados por espaço): 38 79 252 10 13

1. Verificando se G, e, n são primos entre si (usando MDC):
MDC(G, n) = 1
G e n são coprimos.

2. Calculando o inverso de G em Z_n:
O inverso de 79 módulo 252 é 64.

3. Dividindo H por G em Z_n para encontrar a base a:
a = (H * G^-1) mod n = (38 * 64) mod 252 = 152

4. Verificando se a e n1 são coprimos:
a e n1 são coprimos.

5. Verificando se n1 é primo:
n1 é primo.

6. Aplicando o Pequeno Teorema de Fermat: x1 = n1 - 1

7. Decompondo x na forma x = x1 * q + r:
x = 10 = 12 * 0 + 10

8. Reescrevendo a^x mod n1 como (((a^x1)^q mod n1) * (a^r mod n1)) mod n1

9. Calculando valores intermediários:
a^x1 mod n1 = 1
(a^x1)^q mod n1 = 1
a^r mod n1 = 3

10. Resultado final: ((a^x1)^q * a^r) mod n1 = 3

Explicação matemática detalhada impressa acima.
```

## Observações
- O programa encerra automaticamente se algum requisito matemático não for atendido (por exemplo, se G e n não forem coprimos).
- Todas as funções matemáticas são implementadas do zero, sem uso de bibliotecas externas, conforme exigido no enunciado.

---

**Desenvolvido para a disciplina de MD2 - UNB, 2025.** 