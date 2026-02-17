#!/bin/sh
set -e

WORKDIR="${1:-.}"

find $WORKDIR -type f -name '*.cpp' | sort -V | while read -r cpp_file; do
  # printf "AT $cpp_file: ";
  printf "%-60s" "AT $cpp_file "
  
  cpp_dir="$(dirname "$cpp_file")"

  clang++ -std=c++20 "$cpp_file" -o "./tmp/bin"
  
  found=false

  for test_case in $cpp_dir/testcase/*.in; do
    [ -e "$test_case" ] || continue
    name="$(basename "$test_case" .${test_case##*.})"
    found=true
    ./tmp/bin < "$test_case" > "./tmp/$name.out"
    
    if git diff --no-index --quiet \
      "${test_case%.in}.sol" "./tmp/$name.out"
    then
      printf "P"
    else
      printf -- "- \033[31m[FAIL]\033[0m\n"
      
      git diff --no-index --color=always \
          "${test_case%.in}.sol" "./tmp/$name.out"
      exit 1
    fi
  done
  
  if [ "$found" = false ]; then
  printf "\033[90m[SKIP]\033[0m\n"
else
  printf " \033[32m[PASS]\033[0m\n"
fi
done
echo \033[32mFinished\033[0m