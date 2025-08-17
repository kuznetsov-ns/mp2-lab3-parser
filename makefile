CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./ -I./lib_calc -I./gtest -Wno-missing-field-initializers -Wno-unused-const-variable
LDFLAGS = 

# Исходники
SRC_MAIN = main.cpp lib_calc/parser.cpp
SRC_TEST = test/test_main.cpp test/test_parsing.cpp test/test_stack.cpp \
           lib_calc/parser.cpp gtest/gtest-all.cc

# Объекты
OBJ_MAIN = $(SRC_MAIN:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

# Имя выходного бинаря
TARGET = app
TARGET_TEST = app_test

# Условная сборка: если указать BTEST=1 → собирается версия для тестов
ifeq ($(BTEST),1)
    SRC = $(SRC_TEST)
    OBJ = $(OBJ_TEST)
    TARGET_FINAL = $(TARGET_TEST)
else
    SRC = $(SRC_MAIN)
    OBJ = $(OBJ_MAIN)
    TARGET_FINAL = $(TARGET)
endif

all: $(TARGET_FINAL)

$(TARGET): $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST) $(TARGET) $(TARGET_TEST)

.PHONY: all clean test
