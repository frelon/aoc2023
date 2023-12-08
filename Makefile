CC=clang
GO=go

.PHONY: all clean

all: day1 day2 day3 day4 day5 day6 day7 day8

day5: src/day5.go
	$(GO) build -o bin/day5 ./src/day5.go

%: src/%.c
	$(CC) -o bin/$@ $^

clean:
	rm ./bin/day*
