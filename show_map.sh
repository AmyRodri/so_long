#!/bin/bash

# Verifica se o nome do arquivo foi passado
if [ -z "$1" ]; then
    echo "Uso: ./show_map.sh <arquivo.ber>"
    exit 1
fi

FILE="$1"

# Verifica se o arquivo existe
if [ ! -f "$FILE" ]; then
    echo "Arquivo '$FILE' não encontrado!"
    exit 1
fi

# Lê linha por linha e aplica cores
while IFS= read -r line; do
    for (( i=0; i<${#line}; i++ )); do
        c="${line:$i:1}"
        case "$c" in
            1)  echo -ne "\033[90m$c\033[0m" ;;  # cinza
            0)  echo -ne "\033[37m$c\033[0m" ;;  # branco
            P)  echo -ne "\033[34m$c\033[0m" ;;  # azul
            E)  echo -ne "\033[31m$c\033[0m" ;;  # vermelho
            C)  echo -ne "\033[33m$c\033[0m" ;;  # amarelo
            *)  echo -ne "$c" ;;
        esac
    done
    echo
done < "$FILE"