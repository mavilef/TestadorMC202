#!/bin/bash

# Colors
ESC_SEQ="\x1b["
COL_RESET=$ESC_SEQ"39;49;00m"
COL_RED=$ESC_SEQ"31;01m"
COL_GREEN=$ESC_SEQ"32;01m"
COL_YELLOW=$ESC_SEQ"33;01m"
COL_BLUE=$ESC_SEQ"34;01m"
COL_MAGENTA=$ESC_SEQ"35;01m"
COL_CYAN=$ESC_SEQ"36;01m"
COL_BOLD=$ESC_SEQ";1m"

#read -p "Digite o nome do executavel. (Exemplo:edicao) :" executable
printf "${COL_BOLD}%-2s${COL_RESET}\n" "Testador Insano v1.0"
printf "\n"


files=(*.c)
if [ ! -f "$files" ]; then
    echo "Faltando arquivo com extensão .c"
    exit 1;
fi

# Compilando o programa:

echo "Compilando o programa..."

gcc -Wall -pedantic -O2 -std=gnu99 -g *.c -o testador -lm
executable=testador

if [ $? -ne 0 ] ; then
    echo "Erro na compilação. Abortando testes."
    exit
fi



name=$(echo *.tgz | cut -f 1 -d '.')
mkdir -p $name
tar -xzf *.tgz -C $name


mkdir -p res
for inputname in $name/*.in
do
	input=$(basename $inputname)
	input=$(echo $input | cut -f 1 -d '.')

	./$executable <$name/$input.in > res/$input.res 
	diff $name/$input.out  res/$input.res>"res/$input.dif"
	
	if [ $? -eq 0 ]; then
		printf "%-30s" "$input"
		printf "["
        printf "${COL_GREEN}%-2s${COL_RESET}" "OK"
        printf "]\n"
    else
    	printf "%-30s" "$input"
		printf "["
        printf "${COL_RED}%-2s${COL_RESET}" "Erro"
        printf "]\n"
        echo ">>> Saida esperada (Sqtpm):"
        cat "res/$input.dif"
        
        echo
    fi
done

rm -rf $name/*
rm -r $name

rm -rf res/*
rm -r res

