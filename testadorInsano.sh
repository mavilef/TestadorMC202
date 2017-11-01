#!/bin/bash

read -p "Digite o nome do executavel. (Exemplo:edicao) :" executable

tar -xzf ./*.tgz
name=$(echo *.tgz | cut -f 1 -d '.')


for inputname in $name/*.in
do
	input=$(basename $inputname)
	./
done
