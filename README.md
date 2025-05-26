# autocomplete-program
Data structures project: Autocomplete system in C with custom sorting and search.

# Autocomplete Program in C

## Overview
This project is an autocomplete program implemented in C as part of the CS260 Data Structures course. The program provides query suggestions based on a knowledge base of words and their associated frequencies. Given a list of incomplete queries, the program returns the most frequently encountered words that match the initial characters of each query, similar to autocomplete features in search engines and messaging applications,

## Features
The program includes the following features:
1. **Sorting**: Sorts the word list from the knowledge base for efficient searching.
2. **Efficient Search**: Quickly searches for entries that match incomplete query words.
3. **Frequency-Based Sorting**: Ranks suggestions based on frequency to return the most relevant results.
4. **Performance Optimization**: Designed to execute within the provided runtime limits, avoiding built-in sorting functions for a custom sorting approach.

## Files
- **main.c**: The main source file containing the autocomplete program code.
- **Makefile**: Instructions to compile the program.
- **README.md**: This document explaining the project setup and usage.

## Input/Output Specifications
1. **Input Files**:
   - **Knowledge Base File**: Contains a list of query words and their frequencies.
   - **Query List File**: Contains incomplete queries for which the program will provide suggestions.

2. **Output**:
   - For each query, the program outputs up to the top 10 most frequently encountered suggestions.
   - If a query has no matches, the program outputs "No suggestion!".
   - Example format:
     ```
     Query word: [query]
     suggestion1 frequency
     suggestion2 frequency
     ...
     ```

## Usage
### Compilation
To compile the program, use the provided Makefile:
```bash
make
