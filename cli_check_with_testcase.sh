set -e +x

TESTCASE=3
CPP=./toi14_technology.cpp
BIN=./toi14_technology

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

function check() {

}
