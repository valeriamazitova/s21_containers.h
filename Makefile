G=g++ -std=c++17
GCC=$(G) -Wall -Wextra -Werror
LIBS=-lgtest
SOURCES =  test_map.cc test_set.cc test_deque.cc test_stack.cc test_queue.cc test_binary_tree.cc test_vector.cc test_list.cc test_array.cc

clean:
	@-rm -rf test
	@-rm -rf test.info
	@-rm -rf *.gcda
	@-rm -rf *.gcno
	@-rm -rf report
	@-rm -rf leaks*
	@echo .................. im clean now ..................

test: clean
	$(GCC) $(SOURCES) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

gcov_report: clean
	$(GCC) --coverage $(SOURCES) -o test $(LIBS)
	chmod +x *
	./test
	#lcov -t "test" -o test.info --no-external -c -d .
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

leak:
	@echo .................. testing for leaks ..................
	@$(GCC) $(SOURCES) -lgtest -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks


clang-format:
	@echo ------------------ clang-format check -----------------------
	clang-format -n s21_*.h test_*.cc
