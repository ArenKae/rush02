# Rush 02

<p align="center"> <img src="https://github.com/ArenKae/ArenKae/blob/main/42%20badges/Rush02.png" alt="Rush02 badge"/> </p>

## Overview

This repository contains my implementation of **Rush 02**, one of the collaborative, time-constrained projects from the _Piscine_ at 42 School.

Rushes are designed to push students to work efficiently in teams and produce a functional solution under strict constraints. Compared to standard exercises, they are intentionally more demanding in both design and execution.

## Project Description

The objective is straightforward: build a program that converts a numeric value into its written English form — a classic technical interview exercise.

The constraint is what makes it interesting: implementing this in C with a highly restricted set of allowed functions.

## Notes on this implementation
💻 Developed and tested on **Ubuntu 24.04.2 LTS**

This version was rewritten independently as a personal exercise.

-   I reused parts of my own libraries for convenience:

    -   [libft](https://github.com/ArenKae/libft)
    -   [ft_printf](https://github.com/ArenKae/ft_printf)
    -   [get_next_line](https://github.com/ArenKae/get_next_line)
    
    These are not available during the actual Piscine, where everything must be implemented from scratch.
    
-   This implementation does **not comply with the [42 Norm](https://github.com/MagicHatJo/-42-Norm/blob/master/norme.en.pdf)**.
-   A **C++ version** is also included, mainly to revisit the language, but also to illustrate how much simpler the problem becomes with access to the standard library.

## Usage

Clone the repository and navigate to the directory corresponding to the desired language, then compile:
```bash
make
```
Run the program:
```bash
./rush02 [number]
```
### Examples
```bash
./rush02 42
> 42
> forty two  
  
./rush02 2147483647
> 2 147 483 647
> two billion one hundred forty seven million four hundred eighty three thousand six hundred forty seven
```
> [!NOTE]  
> The input must be a **positive integer**, without separators.

## Dictionary Support

The program relies on an external dictionary file mapping numeric values to their written equivalents.

To use a custom dictionary:
```bash
./rush02 [dictionary_file] [number]
```
