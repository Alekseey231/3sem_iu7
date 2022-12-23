CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror  -Wextra -pedantic -O0 -g3 -lm

MAIN_SRCS := list.c graph.c io.c dot.c
TEST_SRCS := 

OBJS := $(MAIN_SRCS:%.c=./out/%.o)

app.exe : $(OBJS) ./out/main.o
	$(CC) $^ -o ./$@ -lm
	

./out/%.o: ./src/%.c ./out/%.d
	$(CC) $(CFLAGS) $< -c -o ./$@


./out/%.d: ./src/%.c
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
