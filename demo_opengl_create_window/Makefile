CC=gcc

CFLAG+=-Wall -O2
LDFLAGS+=-lc -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

BIN:=demo

SRCS+=glad.c main.c
OBJS:=$(patsubst %.c, %.o, $(SRCS))

BUILD_DIR:=build

default:$(BIN)
	mkdir $(BUILD_DIR)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

$(BIN):$(OBJS)

	$(CC) $(LDFLAGS) $(BUILD_DIR)/$^ -o $(BUILD_DIR)/$@

.PHONY:clean
clean:
	#rm -rf *.o $(BIN)
	rm -r $(BUILD_DIR) -f
