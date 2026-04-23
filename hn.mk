CXX = g++
CXXFLAGS = -Iinclude -Itemplates -std=c++17 -I"C:/FTXUI/include"
LDFLAGS = -L"C:/FTXUI/lib"
LDLIBS = -lftxui-component -lftxui-dom -lftxui-screen

TARGET = main
SRC = main.cpp interface.cpp templates/errors.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	del $(TARGET).exe

run: main.exe
	cmd.exe /c start cmd.exe /k main.exe

rebuild: clean all run

.PHONY: all clean rebuild