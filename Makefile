build:
	mkdir build
	cd build && \
	cmake .. && \
	cmake --build .

clean:
	rm -rf build

update:
	make clean
	make build

gtest:
	cd build && \
	./tests/test_cosin_dist

debug:
	cd build && \
	gdb ./start