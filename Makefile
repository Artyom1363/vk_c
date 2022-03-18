check:
	# ./linters/run.sh
	echo "check"

build:
	mkdir build
	cd build && \
	cmake .. && \
	cmake --build .

test:
	cd build && \
	./tests/test_user
	gcc it.c user_lib/*.c && \
	valgrind --tool=memcheck --leak-check=yes ./a.out

clean:
	rm -rf build
