# Data Structures - Programming Assignments

This repository contains solutions to two programming assignments focused on data structures and algorithms. The assignments cover the implementation of a syntax tree for Polish Notation expressions (PA2) and the simulation of an Ad-Hoc Network (PA3).

## PA2: Token List and Syntax Tree

### Description
In this assignment, a token list and a syntax tree are implemented to parse and execute expressions written in Polish Notation. This notation places operators before their operands, simplifying expression parsing as it eliminates the need for operator precedence or parentheses.

### Features
- **Tokenization**: Converts Polish Notation strings into a linked list of tokens.
- **Parsing**: Builds a syntax tree from the token list.
- **Evaluation**: Computes the value of the expression using the syntax tree.
- **Output**: Prints the expression in both Polish and conventional notation and calculates the result.

## PA3: Ad-Hoc Network Simulation

### Description
This assignment involves simulating an ad-hoc network where nodes can send, receive, and forward packets. Each packet contains a message that can be corrupted during transmission, affecting network integrity.

### Features
- **Packet Integrity**: Hash functions ensure packet integrity.
- **Node Simulation**: Nodes can send, receive, and request resends for corrupted packets.
- **Network Dynamics**: Supports adding and removing nodes, and dynamically calculates paths for packet delivery.
