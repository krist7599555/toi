set -e +x

CPP=./toi19_explorer.cpp
BIN=./toi19_explorer
TESTCASE=2

echo "test $CPP"

g++ -std=c++20 "$CPP" -o "$BIN"

echo

for i in $(seq 1 "$TESTCASE"); do
  echo "case $i"
  "$BIN" <./testcase/$i.in >./testcase/$i.out
  diff --color ./testcase/$i.sol ./testcase/$i.out
  echo Pass
  echo ----
done
