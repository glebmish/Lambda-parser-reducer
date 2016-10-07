# Lamda parser and reducer

This project was made for training purposes. It parses lambda expression to tree of operations and variables.
Operations are abstraction (\x.y) and application (a b). Variables are strings of [a-z] charachters. 

Operations available:
* print - represents expression as a string
* tree - represents expression as a tree
* reduce - reduces expression and gives number of reduces
* steps - step-by-step reducing
* . - do last inputted command
* 'command' . - do command with last inputted expression
* exit - close the programm


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Installing

Clone this repository
```
git clone https://github.com/glebmish/Lambda-parser-reducer
```

To run execute
```
make
./lpr.o
```

to clean directory of all executable files exicute
```
make clean
```

That's all. Now you can use the programm.
Example:
```
print \x.x
tree \x.(\z.a b) y
reduce (\x.x) y
```

## Running the tests
To run tests execute
```
make test
./test.o
```

## Writing the tests

Other tests can be included in testing, it should be added to the test folder and it should follow tests Format

Test files are stored in 'Tests/lambda_examples'
Without extensions are test input, with .ans extension are right answers

Format of files:
* input

Only the lambda expression
```
\x.x
```

* answer

Desired expression view

Desired tree view

'empty line'

Desired reduction steps (expression views of each step)

Example:
```
(\x.x) k
App/-- Abs/-- x 0x12f18d0
   |      |
   |      \__ x 0x12f18d0
   |
   \__ k 0x12f1908
   
(\x.x) k
k
```


## Built With

* g++

## Authors

* **Gleb Mishchenko** - [glebmish](https://github.com/glebmish/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
