COMPILER = clang++ -std=c++17
CFLAGS = -w -I./include -pthread
SRC = main.cpp
TARGET = file_upload_app.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	@$(COMPILER) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	@del /F /Q $(TARGET)
