CC = g++ -std=c++17
CCFLAGS = -Wall -Werror -Wextra
TEST_LIBS = -lgtest

all: test

clean:
	rm -rf *.o *.a *.out *.log *.gcda *.gcno *.info gcov_report test report

test: clean
	$(CC) $(CCFLAGS) tests/*.cc -o test $(TEST_LIBS)
	./test

leaks: clean
	$(CC) $(CCFLAGS) tests/*.cc $(TEST_LIBS) -o test
	leaks --atExit -- ./test

valgrind: clean test
	CK_FORK=no valgrind --track-origins=yes --leak-check=full --log-file="valgrind.log" --leak-resolution=med --show-leak-kinds=all -s ./test

check_style:
	find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

gcov_report: clean
	$(CC) $(CC_FLAGS) --coverage tests/*.cc -o gcov_report $(TEST_LIBS) 
	chmod +x *
	./gcov_report
	lcov -t "gcov_report" -o gcov_report.info --no-external --ignore-errors mismatch -c -d .
	genhtml -o report/ gcov_report.info
	open ./report/index.html