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
- [Getting started](#getting-started)
- [How to run it](#how-to-run-it)
- [Writing your own program](#writing-your-own-program)
- [Project structure](#project-structure)
- [Current limits](#current-limits)
- [Contributors](#contributors)
- [Contributing](#contributing)
- [License](#license)

## About

LME stands for **Luna Machine Executable**.

Luna is a small compiler project I made to learn more about how compilers actually work.

It reads a `.lme` file containing one line like this:

``` id="50n68i"
cik 42;
```

and turns it into a real Linux executable. When you run that executable, it exits with code `42`.

That's basically the whole language right now: one command and one number.

`cik` means `exit` in Turkish.

## How it works

There are three main parts:

1. **Tokenizer** — reads the `.lme` file character by character and splits it into tokens. For `cik 42;`, those are `cik`, `42`, and `;`.
2. **Parser** — checks that the tokens are in the expected order and figures out what the program is supposed to do.
3. **Generator** — takes the parsed result and generates x86-64 assembly from it.

`main.cpp` connects everything together. The generated assembly is passed to `nasm`, then `ld` links it into the final executable called `out`.

## Requirements

You'll need:

- A C++ compiler (`g++` or similar)
- `cmake`
- `nasm`
- `ld` (usually included with `binutils`)

If you're using Ubuntu or WSL:

``` id="rbqzmk"
sudo apt update
sudo apt install build-essential cmake nasm
```

## Getting started

Clone the repo:

```bash id="t9ngv5"
git clone https://github.com/Simit6155/LME.git
cd LME
```

Then follow the steps below.

## How to run it

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

``` id="qkn5zp"
cik 7;
```

Then run:

``` id="p8zxuv"
./build/luna myprogram.lme
./out
echo $?
```

You should see `7`.

## Project structure

``` id="a3ty8w"
.
├── CMakeLists.txt
├── LICENSE
├── gitignore
├── src
│   ├── generation.h
│   ├── main.cpp
│   ├── parser.h
│   └── tokenization.h
└── test.lme
```

The project is pretty small, so most of the important stuff is in `src`:

- `tokenization.h` handles tokenizing the source code
- `parser.h` handles parsing
- `generation.h` generates the assembly
- `main.cpp` puts everything together

## Current limits

LME is still very small. Right now it only understands:

``` id="dh5p6z"
cik <number>;
```

There are no variables, math, functions, loops, or anything like that yet.

I mostly made this to understand the basic process of going from source code to an actual executable.

## Contributors

Everyone who has contributed to the project:

<p align="left">
<a href="https://github.com/Simit6155" title="Simit6155"><img src="https://avatars.githubusercontent.com/u/198788214?v=4&s=64" width="64" height="64" alt="Simit6155" style="border-radius:50%" /></a>
</p>

[See the full list of contributors →](https://github.com/Simit6155/LME/graphs/contributors)

## Contributing

If you want to contribute, feel free to fork the repo and open a pull request.

Basic flow:

1. **Fork** the repository
2. **Clone** your fork: `git clone https://github.com/Simit6155/LME.git`
3. **Create a branch**: `git checkout -b feature/your-feature`
4. Make your changes
5. **Commit** them: `git commit -m 'feat: add some feature'`
6. **Push** your branch: `git push origin feature/your-feature`
7. Open a pull request

Try to keep the code style consistent with the rest of the project.

## License

This project is licensed under the **MIT License**.
