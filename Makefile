build:
	mkdir build
	cd build && \
	cmake .. && \
	cmake --build .

clean:
	rm -rf build

run:
	cd build && \
	./start

# fast build (without removing build directory)
fb:
	cd build && \
	cmake .. && \
	cmake --build .

update:
	make clean
	make build

gtest:
	cp build/tests/test_cosin_dist .
	./test_cosin_dist
	rm test_cosin_dist

debug:
	cd build && \
	gdb ./start

testall: 
	make gtest
	cd build && \
	valgrind --tool=memcheck --leak-check=yes ./start

create_report:
	make update
	make gtest
	cd build && \
	lcov -t "tests/test_cosin_dist" -o coverage.info -c -d logic_lib/ && \
	genhtml -o report coverage.info
	cp -r build/report .