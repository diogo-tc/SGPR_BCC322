.PHONY: all dll bapp app bunit unit bfuncional funcional clean

all: bapp bunit bfuncional

dll:
	@mkdir -p bin
	@g++ -shared -fPIC src/lib/domain/*.cpp src/lib/infra/factory/*.cpp src/lib/infra/repository/*.cpp  src/lib/services/*.cpp -o ./bin/libbib.so

bapp: dll
	@g++ -I./src/lib ./src/app/*.cpp -L./bin -lbib -o ./bin/app

app:
	@LD_LIBRARY_PATH=./bin ./bin/app

bunit: dll
	@g++ -I./src/lib tests/unit/*.cpp -L./bin -lbib -o ./bin/unit_teste

unit:
	@LD_LIBRARY_PATH=./bin ./bin/unit_teste

bfuncional: dll
	@g++ -I./src/lib tests/funcional/*.cpp -L./bin -lbib -o ./bin/func_teste

funcional:
	@LD_LIBRARY_PATH=./bin ./bin/func_teste

clean:
	@rm -rf ./bin/*
