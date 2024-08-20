*Note: this also applies to Pis and any other controller board where you have access to the GPIO pins programatically.*

### 1. The resources:

I have prepared a GH Repo with code and Wowki links: https://github.com/rowingdude/Arduino_Pi_Randomness

#### Basic Random Number Generator

-Generates random numbers between 0-100, simulates die rolls, and creates large random numbers up to 1,000,000.
-Uses analogRead(0) to seed the RNG for some unpredictability.
-Great for simple games or basic simulations!


#### Cryptographic Key Generator

-Creates a 128-bit (16-byte) key using Arduino's random() function.
-⚠️ Note: This is for educational purposes only. Don't use this for actual cryptographic applications!
-Demonstrates the concept of key generation in a simple, accessible way.


#### Randomized Quicksort Algorithm

-Implements the Quicksort algorithm with a randomized pivot selection.
-Visualizes the sorting process through Serial output.
-Shows how randomness can improve algorithm performance and prevent worst-case scenarios.

Each sketch demonstrates a different aspect of using randomness in Arduino projects. From simple number generation to more complex applications in cryptography and algorithms, it's amazing how versatile a good RNG can be!
I've included comments in the code explaining the process and some potential improvements (like better seeding methods for the crypto sketch).
What are your thoughts on using randomness in Arduino projects? Any cool applications you've come across or ideas you'd like to share? Let's discuss in the comments!