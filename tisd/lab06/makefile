CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror  -Wextra -pedantic -O0 -g3

MAIN_SRCS := tree_node.c tree.c io.c effective.c
TEST_SRCS := check_io.c check_main.c

OBJS := $(MAIN_SRCS:%.c=./out/%.o)
TEST_OBJS := $(TEST_SRCS:%.c=./out/unit_tests/%.o)

app.exe : $(OBJS) ./out/main.o
	$(CC) $^ -o ./$@
	
unit_tests.exe : $(OBJS) $(TEST_OBJS)
	$(CC) $^ -o ./$@ -lcheck -lpthread -lrt

./out/%.o: ./src/%.c ./out/%.d
	$(CC) $(CFLAGS) $< -c -o ./$@

./out/unit_tests/%.o: ./unit_tests/%.c ./out/unit_tests/%.d
	$(CC) $(CFLAGS) $< -c -o ./$@
	
./out/%.d: ./src/%.c
	@$(CC) -M $< > $@
	
./out/unit_tests/%.d: ./unit_tests/%.c
	@$(CC) -M $< > $@

D = $(MAIN_SRCS:%.c=./out/%.d)
TEST_D = $(TEST_SRCS:%.c=./out/unit_tests/%.d)

include $(wildcard $(D))
include $(wildcard $(TEST_D))

.PHONY : pvs
pvs :
	make clean
	rm -rf ./pvs
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze -o ./project.log
	plog-converter -a GA:1,2 -t fullhtml ./project.log -o ./pvs

.PHONY : clean
clean :
	$(RM) ./out/*.o ./out/unit_tests/*.o ./*.exe ./out/*.d ./out/unit_tests/*.d ./func_tests/data/*.log ./func_tests/data/pr_out.txt ./func_tests/data/out.txt 

.PHONY : unit
unit : unit_tests.exe
	./unit_tests.exe
