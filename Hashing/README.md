# Hashing Implementation

This directory contains implementations of various hashing techniques in C++. The code demonstrates different collision resolution methods and hash functions.

## Hash Functions

Two hash functions are implemented in `HashFunctions.cpp`:

1. **FNV-1a Hash Function (hash1)**
   - Uses the Fowler-Noll-Vo hash algorithm
   - Has good distribution and low collision rate
   - Uses FNV_OFFSET_BASIS (2166136261) and FNV_PRIME (16777619) constants

2. **DJB2 Hash Function (hash2)**
   - Created by Daniel J. Bernstein
   - Simple but effective hash function
   - Good performance for string keys

3. **Auxiliary Hash Function (auxHash)**
   - Simple sum-of-characters hash function
   - Used for double hashing calculations

## Collision Resolution Methods

### 1. Separate Chaining (`separateChaining.cpp`)

- Each slot of the hash table contains a linked list
- All elements with the same hash value are stored in the linked list
- Performance remains good even with high load factors
- Customizable chain length for performance tuning

### 2. Double Hashing (`DoubleHashing.cpp`)

- Open addressing method using two hash functions
- When a collision occurs, uses a second hash function to determine the next position
- Formula: `(hash1(key) + i * auxHash(key)) % tableSize`
- Provides good distribution across the table
- Avoids clustering problems seen in linear probing

### 3. Custom Probing (`CustomHashing.cpp`)

- Open addressing with a quadratic component
- Uses configurable constants C1 and C2
- Formula: `(hash(key) + i * auxHash(key) * C1 + i² * C2) % tableSize`
- Provides more flexible probing sequence
- Constants can be tuned for performance

## Map Interface

A wrapper class `Map` in `Main.cpp` provides a common interface for all three hashing methods:

- Supports insert, find, and remove operations
- Allows tracking of collisions and probes
- Supports dynamic rehashing

## Performance Analysis

The `Main.cpp` file includes code to test and compare performance metrics:
- Number of collisions
- Average number of probes required for successful searches
- Performance across different table sizes
- Comparison between different hash functions

## Usage

Compile and run the Main.cpp file:

```bash
g++ -o Main Main.cpp
./Main
```

The program will output a performance comparison table showing:
- Collision counts for different hash table sizes
- Average probe counts for search operations
- Comparison between different hash functions
- Comparison between different collision resolution methods
