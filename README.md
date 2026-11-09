# C++ Programming Skills Portfolio

This repository contains three C++ coding challenges that have been provided to me.

## Challenges

| Folder | Program | Description |
| --- | --- | --- |
| `Challenge1_CO2` | `challenge1.cpp` | Estimates CO2 emissions from a journey using the distance in miles and the fuel type. |
| `Challenge2_Jokes` | `challenge2.cpp` | Reads jokes from `randomJokes.txt`, selects a random joke and reveals the punchline after user input. |
| `Challenge3_Books` | `challenge3.cpp` | Reads `bookData.txt` and provides a menu to view, borrow and return books. |

## Requirements and how to run the programme

A C++ compiler supporting C++17, such as GCC (`g++`), is required. The commands below are for Windows PowerShell with `g++` available on PATH.

Each challenge is a separate program. Open a terminal in the relevant challenge folder before compiling and running it.

## Challenge 1: CO2 Calculator

In `Challenge1_CO2`, compile and run:

```powershell
g++ -std=c++17 challenge1.cpp -o challenge1.exe
.\challenge1.exe


Enter the distance in miles, then choose `1` for petrol or `2` for diesel.

## Challenge 2: Alexa Joke Program

In `Challenge2_Jokes`, compile and run:

```powershell
g++ -std=c++17 challenge2.cpp -o challenge2.exe
.\challenge2.exe


Keep `randomJokes.txt` in this folder. Type `Alexa, tell me a joke` to request a joke, then press Enter to reveal the punchline. Type `quit` at the request prompt to exit.

## Challenge 3: Book Manager

In `Challenge3_Books`, compile and run:

```powershell
g++ -std=c++17 challenge3.cpp -o challenge3.exe
.\challenge3.exe


Keep `bookData.txt` in this folder. Use menu options `1` to `5` to view all books, view one book, borrow, return or exit. Enter full book IDs, including leading zeros, such as `002`.

Borrowing and returning update availability during the current session. Changes are not saved to the text file, so restarting the program restores the original statuses.

