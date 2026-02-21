.PHONY: all dll bapp app bunit unit bfuncional funcional clean

QT = `pkg-config --cflags --libs Qt5Sql`
PIC = -fPIC

all: bapp bunit bfuncional

dll:
	@mkdir -p bin
	@g++ -shared $(PIC) \
	src/lib/domain/*.cpp \
	src/lib/infra/factory/*.cpp \
	src/lib/infra/repository/*.cpp \
	src/lib/infra/persistence/*.cpp \
	src/lib/services/*.cpp \
	$(QT) \
	-o ./bin/libbib.so

bapp: dll
	@g++ $(PIC) -I./src/lib ./src/app/*.cpp -L./bin -lbib $(QT) -o ./bin/app

app:
	@LD_LIBRARY_PATH=./bin ./bin/app

bunit: dll
	@g++ $(PIC) -I./src/lib tests/unit/*.cpp -L./bin -lbib $(QT) -o ./bin/unit_teste

unit:
	@LD_LIBRARY_PATH=./bin ./bin/unit_teste

bfuncional: dll
	@g++ $(PIC) -I./src/lib tests/funcional/*.cpp -L./bin -lbib $(QT) -o ./bin/func_teste

funcional:
	@LD_LIBRARY_PATH=./bin ./bin/func_teste

clean:
	@rm -rf ./bin/*