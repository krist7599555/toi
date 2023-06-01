set -e
set +x

g++ -std=c++20 toi19_merge.cpp -o toi19_merge

for i in {1..3}; do
  echo TESTCASE $i
  ./toi19_merge <./testcase/$i.in >./testcase/$i.out
  diff --color ./testcase/$i.sol ./testcase/$i.out
  echo Pass
  echo ----
done
