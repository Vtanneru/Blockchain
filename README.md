# Proof of Work Algorithm
This program demonstrates the Proof of Work (PoW) algorithm, which is used in blockchain technology to verify transactions and add new blocks to the chain. The PoW algorithm requires a certain amount of computational effort to be expended by the node that wants to add a new block to the chain. The node must solve a cryptographic puzzle by finding a nonce that, when combined with the block header, produces a hash value that meets a certain target difficulty level.

## Dependencies
This program requires the following libraries:
  * iostream
  * iomanip
  * string
  * ctime
  * chrono
  * random
  * cstring
  * openssl/sha.h
  * vector
  * gnuplot_i.hpp
  
### How to Use
  * Clone this repository to your local machine.
  * Compile the program using a C++ compiler that supports the above libraries.
  * Run the executable file.
  * The program will output the difficulty target, block header, nonce, and time taken to solve the puzzle for various difficulty levels.
T * he program will also generate a graph of difficulty level vs. time taken to solve the puzzle.

#### Limitations
  * This program only demonstrates the basic concept of the PoW algorithm and is not intended to be used in real-world blockchain applications.
  * The program does not take into account the energy consumption and hardware requirements of solving the PoW puzzle.
  * The program uses a fixed block header and nonce range, which does not reflect the dynamic and decentralized nature of real-world blockchain networks.
