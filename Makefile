CFLAGS += -g
LDFLAGS += -lcriterion

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I$(shell brew --prefix criterion)/include
	LDFLAGS = -L$(shell brew --prefix criterion)/lib -lcriterion
endif

all: test

.PHONY: test
test: table.c test.c
	$(CC) $(CFLAGS) -g $^ -o $@ $(LDFLAGS)
	./test

.PHONY: clean
clean:
	rm test