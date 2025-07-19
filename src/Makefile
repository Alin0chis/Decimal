CC ?= gcc
CFLAGS ?= -Wall -Werror -Wextra -std=c11
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage
LINUX_LIBS=-lcheck -lm -lpthread -lrt -lsubunit
OS=$(shell uname -s)
green=\033[0;32m
reset=\033[0m

all: clean s21_decimal.a

test: clean s21_decimal.a
	@$(CC) $(CFLAGS) -c decimal_tests.c
	@mv *.o ./functions/
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) -lcheck ./functions/decimal_tests.o s21_decimal.a -o test
else
	@$(CC) $(CFLAGS) ./functions/decimal_tests.o s21_decimal.a -o test $(LINUX_LIBS)
endif
	@./test

gcov_report: clean test_gcov
	@./test_gcov.out >> /dev/null
	@lcov -t "" -o coverage.info --no-external -c -d ./ >> /dev/null
	@genhtml -q coverage.info -o ./ >> /dev/null
	@mv *.gcda *.gcno ./functions/
	@echo "${green}Coverage report is in ./index.html${reset}"
ifeq ($(OS), Darwin)
	@open ./index.html
endif

s21_decimal.a:
	@$(CC) $(CFLAGS) -c arithmetic_operations/*.c converts/*.c bit_operations/*.c comparison_operators/*.c supporting_operations/*.c other_functions/*.c
	@mv *.o ./objects/
	@ar rcs $@ ./objects/*.o
	@ranlib $@

test_gcov: s21_decimal.a
ifeq ($(OS), Darwin)
	@$(CC) $(GCOV_FLAGS) $(CFLAGS) */s21_*.c decimal_tests.c s21_decimal.a -lcheck -o test_gcov.out
else
	@$(CC) $(CFLAGS) */s21_*.c decimal_tests.c s21_decimal.a -o test_gcov.out $(LINUX_LIBS) $(GCOV_FLAGS)
endif

clean:
	@rm -rf *.o *.a test *.png ./functions/*.gcda ./functions/*.gcno *.html *.info *.css *.out cmd_line ./src/tests/*.html ./src/*.html ./objects/*.o ./functions/*.o
	@echo "${green}Successfully cleaned${reset}"

.PHONY: clean test s21_decimal.a gcov_report

