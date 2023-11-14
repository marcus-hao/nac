# nac

**nac** is a simple programming language designed by our group for the submission
of CPT316 assignment.

In nac, only arithmetic operations are supported, in which every statement
must either be an assignment or a print statement.
Multiple statements can be written in the same line by separating them with semicolons.
Single statements do not need to be terminated with a semicolon.

> Note: Currently, only the lexical and syntax analysis phases are implemented
> in nac.

## Example

The following is a simple program written in nac:

```
x := 1 + 3
```

Here is an example of a program with multiple statements:

```
hello := 42 ; print(hello)
```

## Installation and Building

### Dependencies

Please make sure you have the following prerequisites:

- gcc - GNU Compiler Collection (C compiler)
- GNU Make

If you are building this on a Windows machine, please ensure that you have WSL
installed so that you have access to the build tools required.

### Downloading the source code

Clone the repository:

```
git clone https://github.com/marcus-hao/nac
cd nac
```

To update the source code to the latest commit, run the following command in
the nac directory:

```
git pull
```

### Building

To build the nac compiler, simply run:

```bash
make
```

This will produce the `./nac.out` executable which is used to compile
`.nac` files.

### Compiling nac files

To compile `.nac` files, simply execute the generated executable, `./nac.out`
with your selected `.nac` file:

```bash
./nac.out ./examples/test1_pass.nac
```

This will perform lexical and syntax analysis of the `.nac` file.
If there are any errors in the source `.nac` file, then the compiler
will report the error to the user.

## Running Test Cases

Test cases are prepared in the `examples` directory.
To run the test cases individually, run the following:

```bash
./nac.out ./examples/<test_case>.nac
```

If there are any errors during lexical or syntax analysis, the compiler will
output the error to the terminal to report to the user.

To run all the test cases at once, run the following:

```bash
make test
```