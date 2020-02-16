# websudoku_cpp
Scraper for generating valid sudoku puzzles along with solutions from websudoku. 

---
[![Build Status](https://travis-ci.com/patrick--/websudoku_cpp.svg?branch=master)](https://travis-ci.com/patrick--/websudoku_cpp)


### Overview
Websudokucpp is a straightforward web scraper for downloading Sudoku puzzles and solutions from [Websudoku.com](https://www.websudoku.com/?). Core HTTP request functionality is implemented using the fantastic [cpp-httplib](https://github.com/yhirose/cpp-httplib) header only library.

To scrape puzzles and solutions, websudokucpp simply makes an HTTP request to Websudoku.com and parses the `<INPUT NAME="cheat"` and `<INPUT ID="editmak">` elements from the resulting HTML.


---
### Building and Running
This project can be built pretty easily - first clone the repo with submodules, then you can make it like any other CMake project.


```console
foo@bar:~$ git clone --recurse-submodules git@github.com:patrick--/websudoku_cpp.git
foo@bar:~$ mkdir build
foo@bar:~$ cd build
foo@bar:~$ cmake ..
foo@bar:~$ make
```

Now, you run the example `main.cpp` file with : 

```console
foo@bar:~$ ./websudoku_cpp
```


---
### Usage 

The default constructor sets difficulty to `Puzzle_difficulty::hard`.
```c++
Websudoku ws = Websudoku();
```

However, you can also create an instance with a specific difficulty. Options are: 
* `Puzzle_difficulty::easy`
* `Puzzle_difficulty::medium`
* `Puzzle_difficulty::hard`
* `Puzzle_difficulty::evil`

```c++
Websudoku ws = Websudoku(Puzzle_difficulty::medium);
```

You can also update the difficulty at any time with:
```c++
ws.set_difficulty_level(Puzzle_difficulty::evil);
```

To actually generate a puzzle you need to issue a download.
```c++
ws.download_new_puzzle();
```

Alternatively, let's say you want to download a puzzle of a different difficulty level, but don't necessarily want to change the difficulty level of your instance.

```c++
ws.download_new_puzzle(Puzzle_difficulty::evil)
```

Once a puzzle is downloaded, you can print it as a string or write it to a file. Both methods have an optional boolean `include_solution` flag that prints or write your puzzle along with the solution.

```c++
std::cout << "Printing puzzle along with solution: " << ws.to_str(true) << "\n";
std::cout << "Writing puzzle with solution to file: " << "\n";
ws.write_to_file("foo.txt",true);
```

The output will look like:


```console
9 7 6 - - - 5 8 - 
- - - 4 - 7 6 2 - 
3 - - 5 6 8 7 - - 
- - - - - - 4 - 8 
- 5 - 1 - 4 - 6 - 
6 - 2 - - - - - - 
- - 5 3 8 6 - - 7 
- 1 7 9 - 2 - - - 
- 6 3 - - - 2 9 5 
------------------
9 7 6 2 1 3 5 8 4 
5 8 1 4 9 7 6 2 3 
3 2 4 5 6 8 7 1 9 
1 3 9 6 2 5 4 7 8 
7 5 8 1 3 4 9 6 2 
6 4 2 8 7 9 3 5 1 
2 9 5 3 8 6 1 4 7 
4 1 7 9 5 2 8 3 6 
8 6 3 7 4 1 2 9 5 
------------------
```