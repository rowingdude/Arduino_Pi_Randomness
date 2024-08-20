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

### 1. Random Number Generation

**Sample Code**: `random_number_generation.ino`

Random number generation is integral to [simulations](https://en.wikipedia.org/wiki/Simulation_noise), [probabilistic algorithms](https://dev.to/lilyneema/beginners-guide-statistics-and-probability-in-machine-learning-2c2j), and [statistical sampling methods](https://www.sciencedirect.com/topics/mathematics/random-noise). This sketch shows the basic usage of the Arduino `random()` function and how we create a simple tool with it.

See it in action here: [Random Number Generation](https://wokwi.com/projects/406743956591814657)

### 2. Cryptography and Security

**Insecure Key Code**: `key_generation.ino`
**Insecure Key Wowki**: https://wokwi.com/projects/406745991681997825

**Improved Key Generator**: `better_key_generation.ino`
**Improve Key Generator Wowki**: https://wokwi.com/projects/406746112046999553

Random noise is paramount for generating secure cryptographic keys, [initialization vectors (IVs)](https://en.wikipedia.org/wiki/Initialization_vector), and [nonces](https://en.wikipedia.org/wiki/Cryptographic_nonce). [Pseudo-random number generators (PRNGs)](https://en.wikipedia.org/wiki/Pseudorandom_number_generator) can be [vulnerable if](https://www.schneier.com/wp-content/uploads/2017/10/paper-prngs.pdf) their seed is predictable, compromising the entire encryption process. This example demonstrates the use of random noise generated from an analog pin to seed a cryptographically secure random number generator on an Arduino, ensuring robust encryption keys.

The first sketch `key_generation.ino` uses the basic abstracted Arduino functions to build a cryptographic key, but I feel those are not suitable for a truly secure implementation, so we implement in the second, this function:

```
void seedFromPins(int analogPin1, int analogPin2) {
  // 1. Use two pins
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);

  // 2. Take a reading (we can use floats here if memory permits)
  int reading1 = analogRead(analogPin1);
  int reading2 = analogRead(analogPin2);

  // 3. Mask (XOR) the readings against timing 
  long seed = ((long)reading1 << 16) | reading2;
  seed ^= micros();
  
  // 4. Return the value so we can use it elsewhere
  return seed;

}
```

What this second function does it is reads the voltages from two pins (Analog 1 and Analog 2) and uses those to seed the [random() function](https://www.arduino.cc/reference/en/language/functions/random-numbers/random/). This is a MAJOR improvement over the basic function because it uses voltage artifacts as a seed. These are different every time the board powers up, therefore they should produce consistent random noise.


### 2. Randomized Algorithms

**High Level Quicksort**: `abstracted_quick_sort.ino`
**Wowki Abstracted Quicksort**: https://wokwi.com/projects/406747937567750145
**Low Level Quicksort**: `unabstracted_quick_sort.ino`
**Wowki Unabstracted Quicksort**: https://wokwi.com/projects/406748051779724289


Randomized algorithms, such as those used in optimization or sorting, often rely on true randomness to explore solution spaces effectively. This sample demonstrates how to implement a simple randomized algorithm on an Arduino, using truly random noise to ensure diverse and unbiased results.

### Profiling and Optimizing Performance

Since our precious microcontrollers are memory constrained, it's important to strip away as much abstraction as we possibly can. In most projects, you do not use all of the pins. I'd venture to say that most projects use a handful of pins at most, leaving a bundle for sampling. 

With that in mind, let's look at how our direct pin seeding can be lighterweight than simply "choosing" a random number, I compare the "unabstracted" version using direct register and pin manipulations to the abstracted (Arduino library infused) version..

    Memory Usage:

    Unabstracted: Uses less program memory (flash) as it doesn't rely on Arduino library functions.
    Abstracted: Slightly larger program size due to inclusion of Arduino library functions.


    CPU Cycles:

    Unabstracted: Generally faster as it directly manipulates hardware registers.
    Abstracted: Slightly slower due to function call overhead and additional checks in Arduino libraries.


    Timing Precision:

    Unabstracted: More precise timing control, which can be crucial for randomness.
    Abstracted: Less precise timing due to abstractions in the Arduino core.


    Power Consumption:

    Unabstracted: Potentially lower power consumption due to more efficient code execution.
    Abstracted: Slightly higher power consumption due to additional processing.


    Code Readability and Maintainability:

    Unabstracted: More complex and harder to read for beginners, but more controllable.
    Abstracted: Easier to read and maintain, especially for those familiar with Arduino.

    Quantitative Estimate:
    While exact numbers would require benchmarking on specific hardware, we can make some general estimates:

    Memory Savings: The unabstracted version might save about 500-1000 bytes of program memory.
    Speed Improvement: The unabstracted version could be about 10-20% faster for ADC readings and UART transmissions.
    Timing Precision: The unabstracted version could offer nanosecond-level control vs microsecond-level in the abstracted version.

    Real-world Impact:
    For most hobbyist projects, the difference would be negligible. However, sometimes we just want to squeeze out the maximum performance benefit.

I will update this with hardware profiling tests, but for now, thinking about it, this is what I hypothesize will happen.

### Terms used:

Analog-to-Digital Converter (ADC) - A device that converts a continuous physical quantity (like voltage) to a digital number that represents the quantity's amplitude.
Prescaler - A circuit that reduces a high-frequency signal to a lower frequency by integer division. In ADC context, it's used to set the ADC clock frequency relative to the CPU clock.
Linear Congruential Generator (LCG): A simple algorithm for generating pseudorandom numbers. It works by the formula: X(n+1) = (a * X(n) + c) mod m Where X is the sequence of values, and a, c, and m are constants.
Entropy - In the context of cryptography, a measure of the randomness or unpredictability of data. High entropy is crucial for generating secure keys.
Baud Rate - The rate at which information is transferred in a communication channel. In the UART context, it refers to the number of signal or symbol changes that occur per second.
Nibble - 4 bits, or half of a byte.
eXclusive OR (XOR): A logical operation that outputs true only when inputs differ (one is true, the other is false).



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