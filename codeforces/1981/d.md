# Codeforces Round 949 (Div. 2) - Problem D

https://codeforces.com/contest/1981/problem/D

## Description

Given $n$, construct a sequence of length $n$, denoted by $a$ with elements $a_1, a_2, ..., a_n$, such that:

- For all $1 \leq i \leq n$, $1 \leq a_i \leq 3 \cdot 10^5$
- For all $1 \leq i < j \leq n - 1$, $a_i \cdot a_{i+1} \neq a_j \cdot a_{j+1}$
- Minimize the number of distinct elements in $a$

## Solution

### Observation 1

$\{...\}$ denotes a multiset

- If $\{a_i, a_{i + 1}\} = \{a_j, a_{j + 1}\}$, then $a_i \cdot a_{i+1} = a_j \cdot a_{j+1}$
- If $\{a_i, a_{i + 1}\} \neq \{a_j, a_{j + 1}\}$, the equality of $a_i \cdot a_{i+1}$ and $a_j \cdot a_{j+1}$ depends on the value of $a$.

By assigning each element in $a$ to a prime number, we get:

$$\{a_i, a_{i + 1}\} \neq \{a_j, a_{j + 1}\} \implies a_i \cdot a_{i+1} \neq a_j \cdot a_{j+1}$$

There may be other ways of assignment also, but we use prime number here.

For any assignment, we can transform it into an anssignment of prime number with the same number of distinct elements. Thus it's possible to choose prime number while still minimizing the number of distinct elements.

### Observation 2

We transform the problem into finding a path of $n-1$ edges in a graph, visiting each edge at most once.

Removing all unvisited edges, the problem is transormed into finding a euler path in a graph. Denote the graph as $G=(V,E)$, we construct this graph such that $|V+E| \geq n$ and minimize $|V|$.
