#!/bin/bash

archivos_c=$(find . -maxdepth 1 -type f -name "*.c")

for archivo in $archivos_c; do
  funciones_encontradas=$(grep -E "^(int|float|char|char*|double|void|bool)[[:space:]]+.*" "$archivo")

  if [ -z "$funciones_encontradas" ]; then
    echo "❌ Empty"
  else
    num_funciones=$(echo "$funciones_encontradas" | wc -l)
    echo -e "\e[35m📁 $archivo\e[0m ➡   \e[33m$num_funciones\e[0m \e[31mfuncion/es\e[0m"

    echo "$funciones_encontradas" | while IFS= read -r linea; do
      echo "🔎 Función:  $linea"
    done
  fi

  echo
done
