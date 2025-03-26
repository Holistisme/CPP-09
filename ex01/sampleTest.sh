#!/bin/sh
while IFS= read -r line; do
    ./RPN "$line"
done <<'EOF'
1 2 +
3 4 *
7 2 -
8 4 /
5 1 2 + 4 * + 3 -
7 7 * 7 -
2 3 + 5 *
2 3 + 5 1 - *
7
4 0 /
4 +
3 4 + +
3 4
1 2 3 +
3 a +
x
7 8 ?
2 3 -
2 3 - 5 +
   7   8   +
EOF