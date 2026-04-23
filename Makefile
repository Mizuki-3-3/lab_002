CPP = g++
CPPFLAGS = -Iinclude -Itemplates -Itests -Wall -Wextra -std=c++17

OBJS = assertions.o

TARGET = test_.exe

TESTS = tests/test_append.cpp tests/test_prepend.cpp tests/test_insert.cpp tests/test_map.cpp tests/test_reduce.cpp tests/test_where.cpp tests/test_main.cpp


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(TESTS) $^ -o $@

errors.o: templates/errors.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

assertions.o: tests/assertions.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	del $(OBJS) $(TARGET)

run: test_.exe
	cmd.exe /c start cmd.exe /k test_.exe

rebuild: clean all run

.PHONY: all clean rebuild