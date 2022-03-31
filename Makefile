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