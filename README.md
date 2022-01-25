# Biblioteca de Grafos

Uma biblioteca contendo todas as representações de estruturas de um grafo, podendo ser elas uma árvore, uma lista de adjacência, uma matriz de adjacência ou a representação de um grafo por meio de um map. Alguns algoritmos de busca ou o famoso algoritmo de Djikstra que soluciona o caminho mais curto foram incluidos neste projeto de âmbito educacional.

## Compilação

Para compilar os arquivos de dependência para poder consumir o módulo, utilize a ferramenta **Make** usando o seguinte comando

```
$ make run
```

Similar, caso deseje excluir o objeto do arquivo, use o comando

```
$ make rm
```

## Estudos de Caso

A interface de usuário provida mostrará um menu o qual terá diversas opções para escolha de caso teste, inclusive para seleção de estrutura e do caminho a ser tomado pelo algoritmo de Djikstra (ou DFS, dependendo se o grafo tiver ou não peso). Todos os resultados da amostra terão um arquivo de saída que será criado na pasta *results*, após a seleção de escolhas.

## Informações sobre o consumo da aplicação

As informações referentes ao gasto de memória tanto virtual quanto física, tempo de execução e ao consumo de CPU estarão no arquivo de saída mencionado acima. Este relatório é essencial para uma breve análise dos recursos computacionais requeridos por cada caso teste.

## Contribuição

Caso queira contribuir com este projeto, faça uma pull-request do que deseja alterar, incluir ou excluir dos módulos especificados. Além disso, coloque o motivo de tal pull-request e o porquê.