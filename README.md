# Lab6_Vector_Lab
# Minimat - 3D Vector Calculator

**Author:** Dylan McKinney
**Course:** CPE-2600 Systems Programming

## Description

Minimat is an interactive, command-line vector calculator written in C. It acts like a small "mini-Matlab". You type commands at the `minimat>` prompt to create 3D vectors, store them by name, and do math on them.

The program is split into three layers:

1. **Math layer** (`vect_math.c/.h`) - add, subtract, scalar multiply, dot product, cross product
2. **Storage layer** (`vect_storage.c/.h`) - keeps the vectors in a dynamic array
3. **User interface layer** (`ui.c/.h`) - reads and parses commands and prints all output

`main.c` only decides whether to print the help screen or start the prompt.

## How to Build

Requires `gcc` and `make`.

1. Clean old build files:
   ```
   make clean
   ```
2. Build the program:
   ```
   make
   ```

This creates an executable named `math`.

## How to Run

```
./math
```

### Command Line Options

- `./math` - starts the calculator
- `./math -h` - prints the help screen and exits

To check for memory leaks:

```
valgrind --leak-check=full ./math
```

## Commands

**Note:** separate each item with spaces (for example `c = a + b`, not `c=a+b`).

- `a = 1 2 3` - create or replace vector `a` (commas or spaces both work)
- `a = 1 2` - if z is left out it is set to 0
- `a` - display vector `a`
- `a + b` - add two vectors
- `a - b` - subtract two vectors
- `a * 2` or `2 * a` - scalar multiplication
- `a . b` - dot product (result is a number)
- `a x b` - cross product
- `c = a + b` - do an operation and save the result in `c`
- `list` - show all stored vectors
- `clear` - erase all stored vectors (frees the memory)
- `load file.csv` - load vectors from a CSV file (vectors with the same name are replaced)
- `save file.csv` - save all stored vectors to a CSV file (overwrites the file if it exists)
- `fill 100` - make 100 random test vectors named `v0`, `v1`, `v2`, ...
- `quit` - exit the program

### Example Session

```
minimat> a = 1 2 3
a = 1 2 3
minimat> b = 4, 5, 6
b = 4 5 6
minimat> c = a + b
c = 5 7 9
minimat> a x b
ans = -3 6 -3
minimat> save test.csv
Saved 3 vectors to test.csv
```

### CSV File Format

One vector per line: name, then x, y, z.

```
a,1,2,3
b,4.4,5.5,6
```

## Versions

- **v1.0** - original Lab 5 version (fixed storage, no file I/O)
- **v2.0** - Lab 7 update (dynamic memory, `load`, `save`, and `fill`)