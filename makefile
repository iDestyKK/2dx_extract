# 2dx_extract makefile
# For more information on this program, read the top comments in "2dx_extract.c"

# Specify variables
CC = gcc
CFLAGS =
BIN = 2dx_extract
HELPER_DIR = lib
HELPER_FILES = $(HELPER_DIR)/2dx_structs.c $(HELPER_DIR)/2dx_parse.c $(HELPER_DIR)/arg_parse.c
PROG_SRC = 2dx_extract.c

# Perform Awesomeness...
2dx_extract:
	$(CC) $(CFLAGS) -o $(BIN) $(PROG_SRC) $(HELPER_FILES)
