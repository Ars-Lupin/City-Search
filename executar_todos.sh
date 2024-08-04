#!/bin/bash

# Caminho para a pasta com os arquivos de entrada
input_dir="./testes"

# Caminho para o programa a ser executado
programa="./principal"

# Verifica se o diretório de entradas existe
if [ ! -d "$input_dir" ]; then
    echo "Diretório de entradas não encontrado: $input_dir"
    exit 1
fi

# Verifica se o programa existe
if [ ! -f "$programa" ]; then
    echo "Programa não encontrado: $programa"
    exit 1
fi

# Itera sobre todos os arquivos na pasta de entradas
for input_file in "$input_dir"/*; do
    if [ -f "$input_file" ]; then
        echo "Executando para o arquivo: $input_file"
        
        # Executa o programa passando o nome do arquivo como entrada
        echo "$input_file" | valgrind "$programa"
        
        # Separador visual para a saída de cada arquivo
        echo "--------------------------------------"
    fi
done
