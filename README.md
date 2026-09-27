# Luna

Luna is a tiny toy compiler. It reads a `.lme` file, and if that file
contains exactly one line like this:

```
cik 42;
```

...it produces a real Linux program that, when run, exits with code `42`.

That's it. That's the whole language. One command, one number.
("cik" means "exit" — it's Turkish.)

## How it works

1. **Tokenizer** — reads your `.lme` file character by character and
   chops it into tokens: the word `cik`, a number, and a semicolon.
2. **Parser** — checks those tokens are in the right order and builds
   a tiny tree out of them (just "exit with this number").
3. **Generator** — turns that tree into x86-64 assembly (the `mov`/`syscall`
   instructions a CPU actually understands).
4. **main.cpp** glues all three together, then hands the generated
   assembly to `nasm` (assembler) and `ld` (linker) to produce a real,
   runnable binary called `out`.

## Requirements

You need these installed:
- A C++ compiler (`g++` or similar)
- `cmake`
- `nasm`
- `ld` (comes with `binutils`, usually already on Linux)

On Ubuntu/WSL you can get everything with:

```
sudo apt update
sudo apt install build-essential cmake nasm
```

## How to run it (idiot-proof steps)

1. Open a terminal in the project folder (the one with `CMakeLists.txt` in it).
2. Build it:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```
   This creates a program called `luna` (or `Luna`) inside the `build` folder.
3. Go back one folder so you can see your `.lme` file:
   ```
   cd ..
   ```
4. Run the compiler on the test file:
   ```
   ./build/luna test.lme
   ```
5. This creates a file called `out` in your current folder. Run it:
   ```
   ./out
   ```
6. Check what exit code it gave you:
   ```
   echo $?
   ```
   It should print whatever number was in `test.lme` (e.g. `42`).

## Writing your own program

Make a new text file, e.g. `myprogram.lme`, with one line:

```
cik 7;
```

Then run:

```
./build/luna myprogram.lme
./out
echo $?
```

You should see `7`.

## Limits

- Only one statement per file: `cik <number>;`
- No variables, no math, no functions, no loops
- This is a learning project, not a real programming language
