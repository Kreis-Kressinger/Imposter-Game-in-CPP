CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = imposter.exe

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp



ifeq ($(OS), Windows_NT)
clean:
	del $(TARGET)
else
clean:
	rm -f $(TARGET)
endif
