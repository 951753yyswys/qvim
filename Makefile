CXX = g++
CXXFLAGS = -g -O2
TARGET = qvim
SRC_DIR = src

SOURCES = main.cpp \
          $(SRC_DIR)/buffer.cpp \
          $(SRC_DIR)/cursor.cpp \
          $(SRC_DIR)/edit.cpp \
          $(SRC_DIR)/tui.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
