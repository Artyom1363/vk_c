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

update:
	make clean
	make build
	make test

create_report:
	make update
	cd build && \
	lcov -t "tests/test_user" -o coverage.info -c -d user_lib/ && \
	genhtml -o report coverage.info
	cp -r build/report report