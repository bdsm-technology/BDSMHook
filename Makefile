libsubstrate.so: ${shell ls Substrate/*}
	@g++ Substrate/*.{c,cpp} -o libsubstrate.so -shared -fPIC -fvisibility=hidden