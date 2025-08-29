CC = gcc
CFLAGS = -Wall -g

OSS_SRC = oss.c
USER_SRC = user.c

OSS_BIN = oss
USER_BIN = user

all: $(OSS_BIN) $(USER_BIN)

$(OSS_BIN): $(OSS_SRC)
	$(CC) $(CFLAGS) -o $(OSS_BIN) $(OSS_SRC)

$(USER_BIN): $(USER_SRC)
	$(CC) $(CFLAGS) -o $(USER_BIN) $(USER_SRC)

clean:
	rm -f $(OSS_BIN) $(USER_BIN) *.o

.PHONY: all clean