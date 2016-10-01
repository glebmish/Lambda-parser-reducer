# Lamda parser and reducer

This project was made for training purposes. It parses lambda expression to tree of operations and variables.
Operations are abstraction (\x.y) and application (a b). Variables are strings of [a-z] charachters. 

Operations available:
* print - represents expression as a string
* tree - represents expression as a tree
* reduce - reduces expression and gives number of reduces
* steps - step-by-step reducing
* . - do last inputted command
* <command> . - do command with last inputted expression
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
./lbr.out
```

That's all. Now you can use the programm.
Example:
```
print \x.x
tree \x.(\z.a b) y
reduce (\x.x) y
```

## Running the tests
NOT WORKING YET

## Built With

* g++

## Authors

* **Gleb Mishchenko** - [glebmish](https://github.com/glebmish/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
