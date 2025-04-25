scripts = tail-test.sh io-test.sh io-test.c maxwordcount-test.sh print-help.sh
test_dirs = tail_tests2025 io_tests2025 maxwordcount_tests2025
.PHONY: all tail io maxwordcount maxwordcount-dynamic maxwordcount-all help clean

all: tail io maxwordcount-all clean

tail:
	@clear
	@chmod +x tail-test.sh && ./tail-test.sh

io: io-test
	@chmod +x io-test.sh && ./io-test.sh

io-test: io-test.c io.o
	@gcc -o $@ $^

io.o: ../io.c ../io.h
	@gcc -c $< -o $@

maxwordcount:
	@chmod +x maxwordcount-test.sh && ./maxwordcount-test.sh ""

maxwordcount-dynamic:
	@chmod +x maxwordcount-test.sh && ./maxwordcount-test.sh "dynamic"

maxwordcount-all:
	@chmod +x maxwordcount-test.sh && ./maxwordcount-test.sh "all"

help:
	@chmod +x print-help.sh && ./print-help.sh

clean:
	@rm -f io-test *.o

zip:
	@zip -r IJC2025_tests_marocc.zip $(scripts) $(test_dirs) Makefile
	
