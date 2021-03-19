# step 1:
# all: add.c sub.c div.c mul.c main.c
#	gcc add.c sub.c div.c mul.c main.c -I./ -o app

# step 2:
#app: add.o sub.o div.o mul.o main.o
#	gcc add.o sub.o div.o mul.o main.o -o app

#add.o: add.c
#	gcc -c add.c

#sub.o: sub.c
#	gcc -c sub.c

#div.o: div.c
#	gcc -c div.c

#mul.o: mul.c
#	gcc -c mul.c

#main.o: main.c
#	gcc -c main.c


#step 3:
#$@表示目标, $^表示所有依赖, $<表示依赖中的第一个
#src = $(wildcard *.c)
#pbj = $(patsubst %.c, %.o, $(src))
#target = app

#$(target):$(obj)
#	gcc $^ -o $@

#%.o: %.c
#	gcc -c $< -o $@
#step 4:
#预处理
CPPFLAGS = -Iinclude
#编译时参数
CFLAGS = -O2 -Wall
#共享库
LDFLAGS =
CC = gcc

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = app1

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY:clean
clean:
	-rm -f *.o
	-rm -f app

#彻底清除生成的过程文件和生成的配置文件
distclean:


install:

test:
#	@echo "hello"
	@echo $(src)
	@echo $(obj)
