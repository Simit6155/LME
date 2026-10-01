# LME

![GitHub stars](https://img.shields.io/github/stars/Simit6155/LME?style=for-the-badge&logo=github)
![GitHub forks](https://img.shields.io/github/forks/Simit6155/LME?style=for-the-badge&logo=github)
![GitHub issues](https://img.shields.io/github/issues/Simit6155/LME?style=for-the-badge&logo=github)
![Last commit](https://img.shields.io/github/last-commit/Simit6155/LME?style=for-the-badge&logo=github)
![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

## Table of Contents

- [About](#about)
- [How it works](#how-it-works)
- [Requirements](#requirements)
- [Quick test (just want to try it right now?)](#quick-test-just-want-to-try-it-right-now)
- [Building it yourself](#building-it-yourself)
- [Writing your own program](#writing-your-own-program)
- [Project structure](#project-structure)
- [Current limits](#current-limits)
- [License](#license)

## About

LME stands for **Luna Machine Executable**.

I made Luna to actually understand how compilers work instead of just reading about it. It's a real compiler, just a very small one.

It reads a `.lme` file with one line like this:

```
cik 42;
```

and turns it into an actual Linux executable. Run that executable, and it exits with code `42`.

That's the whole language for now. One command, one number. `cik` means "exit" in Turkish.

## How it works

Three parts, and each one does one job:

1. **Tokenizer** — reads the `.lme` file character by character and chops it into tokens. `cik 42;` becomes three tokens: `cik`, `42`, `;`.
2. **Parser** — checks those tokens are in the right order and builds a small tree out of them.
3. **Generator** — walks that tree and writes out real x86-64 assembly.

`main.cpp` wires all three together. Once the assembly is written, `nasm` assembles it and `ld` links it into a runnable binary called `out`.

## Requirements

Grab these before trying anything:

- A C++ compiler (`g++` works fine)
- `cmake`
- `nasm`
- `ld` (comes with `binutils`, already on most Linux setups)

On Ubuntu or WSL, one line gets you everything:

```bash
sudo apt update && sudo apt install build-essential cmake nasm
```

## Quick test (just want to try it right now?)

If you grabbed the prebuilt `luna` binary and `test.lme` from the [Releases](../../releases) page, you don't need to build anything. Just do this:

```bash
chmod +x luna
./luna test.lme
./out
echo $?
```

You should see a number get printed — that's the exit code Luna's compiler produced. If `test.lme` contains `cik 42;`, you'll see `42`.

## Building it yourself

Clone it first:

```bash
git clone https://github.com/Simit6155/LME.git
cd LME
```

Then build it with cmake:

```bash
mkdir build
cd build
cmake ..
make
```

This drops a binary called `luna` inside the `build` folder. Go back to the project root so you can see the test file:

```bash
cd ..
```

Now compile the test program:

```bash
./build/luna test.lme
```

That generates a file called `out` in the current folder. Run it:

```bash
./out
```

Then check what exit code it gave you:

```bash
echo $?
```

That number should match whatever was in `test.lme`.

## Writing your own program

Make a new file, say `myprogram.lme`, with one line:

```
cik 7;
```

Compile and run it the same way:

```bash
./build/luna myprogram.lme
./out
echo $?
```

You should get `7` back.

## Project structure

```
.
├── CMakeLists.txt
├── LICENSE
├── .gitignore
├── src
│   ├── generation.h
│   ├── main.cpp
│   ├── parser.h
│   └── tokenization.h
└── test.lme
```

Everything that matters lives in `src`:

- `tokenization.h` — splits source code into tokens
- `parser.h` — turns tokens into a parse tree
- `generation.h` — turns the tree into assembly
- `main.cpp` — glues the three stages together

## Current limits

Luna is intentionally tiny right now. It only understands:

```
cik <number>;
```

No variables, no math, no functions, no loops — none of that yet. The point of this project was learning how source code actually turns into a running program, not building a full language.

## License

MIT. Do whatever you want with it.
