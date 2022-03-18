# vk_c
this repo for technopark c/c++
to start tests make this:
mkdir build
cd build
cmake ..
make
./tests/test_user

# after this you can generate html report
lcov -t "tests/test_user" -o coverage.info -c -d user_lib/
genhtml -o report coverage.info
cd report
python3 -m http.server 8000

# to make analise code you may run from root dir:
make check
