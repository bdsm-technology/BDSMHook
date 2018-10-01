.PHONY: all test

all: libsubstrate.so test
test: ${patsubst test/%.cpp,%.test,${wildcard test/*.cpp}}

libsubstrate.so: ${shell ls Substrate/*}
	@g++ Substrate/*.{c,cpp} -o libsubstrate.so -shared -fPIC -fvisibility=hidden
%.test: test/%.cpp libsubstrate.so
	@g++ -o $@ $< -L. -lsubstrate
	@echo TEST: $@
	@LD_LIBRARY_PATH=. ./$@ || (rm $@ && exit 1)