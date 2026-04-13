CPP = g++
CPPFLAGS = -Iinclude -Isrc -Itests -Wall -Wextra -std=c++17

OBJS = errors.o assertions.o

TARGET = test_.exe


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) tests/test_append.cpp tests/test_prepend.cpp tests/test_insert.cpp tests/test_map.cpp tests/test_reduce.cpp tests/test_where.cpp tests/test_main.cpp $^ -o $@

errors.o: src/errors.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

assertions.o: tests/assertions.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	del $(OBJS) $(TARGET)

run: test_.exe
	cmd.exe /c start cmd.exe /k test_.exe

rebuild: clean all run
.PHONY: all clean rebuild