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

clean:
	rm -rf build
