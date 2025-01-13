# City Search - Projeto de Exploração de Grafos

Este projeto é uma ferramenta de exploração de grafos projetada para simular a experiência de encontrar caminhos entre cidades usando vários algoritmos de busca. Ele demonstra implementações de DFS, BFS, UCS e A\* para resolver problemas de travessia de grafos de forma eficiente.

![Grafo](imagens/image-grafo.png)

## Funcionalidades

- **DFS (Busca em Profundidade)**: Explora caminhos mergulhando profundamente no grafo.
- **BFS (Busca em Largura)**: Encontra caminhos com o menor número de passos.
- **UCS (Busca de Custo Uniforme)**: Calcula o caminho mais curto com base no custo total.
- **A**\*: Utiliza heurísticas para encontrar o caminho mais curto de forma eficiente.

## Detalhes da Implementação

1. DFS e BFS são implementados usando pilhas e filas, respectivamente, sem recursão.
2. UCS e A\* utilizam uma estrutura de dados do tipo heap para gerenciamento eficiente de prioridades.
3. Todas as estruturas de dados são projetadas para serem opacas e genéricas.
4. Os dados de entrada são lidos a partir de um arquivo de texto estruturado, conforme especificado abaixo.

## Formato de Entrada

O programa aceita um arquivo de entrada com a seguinte estrutura:

1. O algoritmo de busca a ser utilizado (DFS, BFS, UCS ou A\*).
2. Índices das cidades de origem e destino.
3. Número total de cidades e seus detalhes:
   - Nome da cidade (uma palavra, sem espaços ou acentos).
   - Coordenadas GPS (x, y).
   - Número de cidades vizinhas, seguido pelos índices das vizinhas e as distâncias.

Exemplo de arquivo de entrada:

```text
UCS
0 5
6
0 Vitoria 0 0 3 1 16 2 20 3 12
1 Cariacica -16 0 3 0 16 7 10 8 50
2 Serra 16 16 1 0 20
...
```

## Formato de Saída

O programa fornece:

1. A sequência de cidades no caminho identificado ou uma mensagem caso o destino seja inacessível.
2. O custo total do caminho, formatado com duas casas decimais.
3. O número de cidades visitadas durante a busca.

Exemplo de saída:

```text
Caminho: Vitoria -> VilaVelha -> Guarapari -> Iconha
Custo total: 142.00
Cidades visitadas: 9
```

## Como Compilar e Executar

1. Compile o projeto usando GCC:
   ```bash
   gcc -o busca_cidades busca_cidades.c -lm
   ```
2. Execute o programa com um arquivo de entrada:
   ```bash
   ./busca_cidades entrada.txt
   ```

## Estrutura de Arquivos

- `busca_cidades.c`: Arquivo principal contendo a implementação.
- `estruturas.h` e `estruturas.c`: Estruturas de dados personalizadas para o projeto.
- `entrada.txt`: Exemplo de arquivo de entrada para testes.

## Notas

- Os algoritmos foram testados com grafos conectados e desconectados.
- A heurística do A\* utiliza a distância euclidiana como estimativa.

##
