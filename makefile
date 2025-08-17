CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./ -I./lib_calc -I./gtest -Wno-missing-field-initializers -Wno-unused-const-variable
LDFLAGS = 

# Папки для сборки
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Исходники
SRC_MAIN = main.cpp lib_calc/parser.cpp
SRC_TEST = test/test_main.cpp test/test_parsing.cpp test/test_stack.cpp \
           lib_calc/parser.cpp gtest/gtest-all.cc

# Преобразуем .cpp → .o в OBJ_DIR
OBJ_MAIN = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_MAIN))
OBJ_TEST = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_TEST))

# Цели
TARGET = $(BIN_DIR)/app
TARGET_TEST = $(BIN_DIR)/app_test

# Условная сборка
ifeq ($(BTEST),1)
    OBJ = $(OBJ_TEST)
    TARGET_FINAL = $(TARGET_TEST)
else
    OBJ = $(OBJ_MAIN)
    TARGET_FINAL = $(TARGET)
endif

all: $(TARGET_FINAL)

# Правило для обычного бинаря
$(TARGET): $(OBJ_MAIN) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для тестового бинаря
$(TARGET_TEST): $(OBJ_TEST) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Общее правило компиляции .cpp → .o
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Директории для сборки
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Тесты: собрать и запустить
test: $(TARGET_TEST)
	./$(TARGET_TEST)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean test
