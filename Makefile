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
	gcc -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error it.c user_lib/*.c && \
	./a.out

clean:
	rm -rf build
