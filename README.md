# Randomness Essentials: Code Samples Repository

## Overview

This repository is a collection of code samples that demonstrate the crucial role of truly random noise in various computational and engineering contexts. Each sample illustrates a specific use case where high-entropy randomness is indispensable, whether for security, signal processing, artificial intelligence, or randomized algorithms.

The examples are implemented for the Arduino platform, leveraging its capabilities to generate and utilize random noise for a broad spectrum of applications.

## Table of Contents

- [Introduction](#introduction)
- [Applications](#applications)
  - [1. Cryptography and Security](#1-cryptography-and-security)
  - [2. Random Number Generation](#2-random-number-generation)
  - [3. Noise Generation for Signal Processing](#3-noise-generation-for-signal-processing)
  - [4. Randomized Testing and Fuzzing](#4-randomized-testing-and-fuzzing)
  - [5. Randomized Algorithms](#9-randomized-algorithms)
- [Getting Started](#getting-started)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Randomness is a cornerstone of modern computational practices, underpinning various domains ranging from cryptographic security to the generation of unpredictable gameplay mechanics. This repository focuses on the necessity of truly random noise, providing code samples that showcase its application across different fields. The goal is to illustrate the critical importance of non-deterministic randomness and to provide developers with practical implementations for their projects. All of these sketches share the same basic premise - capture or create random noise or events and then do something with it. We will focus on the creating and capturing aspects of these sketches primarily, the remainder of the sketch is simply to illustrate why you'll do so in these applications. 

One aspect of randomization many are familiar with is the lack of it. Spotify for instance has been groaned about since its inception for lacking a truely random sort algorithm. Games are another place, are you bored with how the NPCs interact? That's in large part to their lack of truly random actions. I have prepared a few illustrative examples though these are by no means complete or exhaustive, I have included a sixth `the_ultimate_noise_sketch.ino` that ties all of these items together and makes sort of the "best" noise gathering utility.

## Applications

### 1. Cryptography and Security

**Sample Code**: `key_generation.ino`

Random noise is paramount for generating secure cryptographic keys, [initialization vectors (IVs)](https://en.wikipedia.org/wiki/Initialization_vector), and [nonces](https://en.wikipedia.org/wiki/Cryptographic_nonce). [Pseudo-random number generators (PRNGs)](https://en.wikipedia.org/wiki/Pseudorandom_number_generator) can be [vulnerable if](https://www.schneier.com/wp-content/uploads/2017/10/paper-prngs.pdf) their seed is predictable, compromising the entire encryption process. This example demonstrates the use of random noise generated from an analog pin to seed a cryptographically secure random number generator on an Arduino, ensuring robust encryption keys.

### 2. Random Number Generation

**Sample Code**: `random_number_generation.ino`

Random number generation is integral to [simulations](https://en.wikipedia.org/wiki/Simulation_noise), [probabilistic algorithms](https://dev.to/lilyneema/beginners-guide-statistics-and-probability-in-machine-learning-2c2j), and [statistical sampling methods](https://www.sciencedirect.com/topics/mathematics/random-noise). The sample illustrates the use of truly random noise as a seed for a linear congruential generator (LCG) to produce high-entropy random numbers, enhancing the unpredictability and quality of the results.

### 3. Noise Generation for Signal Processing

**Sample Code**: `white_noise_audio.ino`

[Signal processing](https://www.analog.com/en/lp/001/beginners-guide-to-dsp.html) applications, such as audio testing and synthesis, require truly random noise to generate white noise signals. This code sample demonstrates how to produce white noise on an Arduino, which can be used for testing audio equipment or creating sound effects.

### 4. Randomized Testing and Fuzzing

**Sample Code**: `fuzz_testing.ino`

[Fuzz testing](https://owasp.org/www-community/Fuzzing) involves feeding random inputs into a system to uncover potential vulnerabilities. This example shows how to generate truly random noise inputs to stress test a system, helping to identify edge cases and bugs that might not be detected with deterministic inputs.


### 5. Randomized Algorithms

**Sample Code**: `optimization_randomization.ino`

Randomized algorithms, such as those used in optimization or sorting, often rely on true randomness to explore solution spaces effectively. This sample demonstrates how to implement a simple randomized algorithm on an Arduino, using truly random noise to ensure diverse and unbiased results.

## Getting Started

To run these examples, you will need an Arduino board (preferably one with analog input capabilities) and the Arduino IDE. Simply upload the relevant `.ino` file to your board and observe the output through the Serial Monitor or other connected peripherals.

### Prerequisites

- A desire to learn and hack away to make this code work for your project!
- Arduino IDE installed on your computer and board or you can use WowKi, which is where I'm hosting working examples.
- A basic understanding of Arduino programming and circuit design helps, but I've gone to some lengths to try to make this as beginner friendly as possible.

### Installation

1. Clone this repository:
   `git clone https://github.com/rowingdude/Arduino_Pi_Randomness.git`
2. Open the Arduino IDE.
3. Load the desired `.ino` file into the IDE.
4. Connect your Arduino board to your computer.
5. Upload the sketch to the board.

## Contributing

Contributions to this repository are welcome. If you have additional examples or improvements to the existing code, feel free to open a pull request. Please ensure that your contributions adhere to the style and purpose of the repository.

### Guidelines

- Provide clear documentation and comments in your code.
- Ensure that your code is well-tested and works across different Arduino boards.
- Include a brief description of the application of randomness in your code.

## License

This repository is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details. 

---

This repository is an ongoing project aimed at providing a comprehensive resource for understanding and implementing true randomness in embedded systems. Whether you're working on security, AI, or control systems, these examples serve as a practical guide to integrating randomness into your projects.