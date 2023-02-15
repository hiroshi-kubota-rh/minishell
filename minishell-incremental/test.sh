#!/bin/bash

COLOR_RED='\033[0;31m'
COLOR_GRN='\033[0;32m'
COLOR_RESET='\033[0;0m'

assert () {
	printf '[%s]\n' "$1"

	echo -n -e "$1" | LANG=en bash >cmp
	expected=$?

	echo -n -e "$1" | ./minishell >out
	actual=$?

	diff cmp out \
		&& echo -n -e " diff: $COLOR_GRN ok $COLOR_RESET" \
		|| echo -n -e " diff: $COLOR_RED KO $COLOR_RESET"
	[ "$expected" = "$actual" ] \
		&& echo -n -e " status: $COLOR_GRN ok $COLOR_RESET" \
		|| echo -n -e " status: $COLOR_RED KO $COLOR_RESET expected $expected but got $actual "
	echo
}

generate() {
echo '
#include <stdio.h>
int main() { printf("hello from a.out\n"); return 42; }
' | gcc -xc -o a.out -
}

cleanup() {
	rm -f cmp out a.out
}

generate

assert ''
assert '\n'

assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

assert 'bin/cat'
assert 'a.out'
assert 'nosuchfile'
assert './nosuchfile'

assert './main.c'
assert './'
assert '/'
assert '.'

assert 'cat -e main.c'
assert 'echo   hello   world'
assert 'echo  " hello   world  " '
assert "echo  ' hello   world  ' "
assert "echo  ' hello ''  world  ' "
assert "echo  ' hello'  ' world  ' "
assert 'echo ""'
assert "echo ''"
assert "echo \"''\""
assert "echo '\"\"'"

cleanup
