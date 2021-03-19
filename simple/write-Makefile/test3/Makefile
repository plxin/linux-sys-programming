
#step 3:
#$@表示目标, $^表示所有依赖, $<表示依赖中的第一个
src = $(wildcard *.c)
pbj = $(patsubst %.c, %.o, $(src))
target = app

$(target):$(obj)
	gcc $^ -o $@

%.o: %.c
	gcc -c $< -o $@
#step 4:
.PHONY:clean
clean:
	-rm -f *.o
	-rm -f app
	
test:
#	@echo "hello"
	@echo $(src)
