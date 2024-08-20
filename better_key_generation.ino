#include <avr/io.h>
#include <util/delay.h>

// Function to read analog value with minimal abstraction
uint16_t readAnalog(uint8_t pin) {

/*
    ADC Reading Process
    -------------------
    Pin
        |
        v
    +-------+
    |  ADC  |    ADMUX: Select channel
    |       |    ADCSRA: Start conversion
    | 10-bit|
    |       |    while(converting) { wait }
    +-------+
        |
        v
    Result
*/

  // Set the analog reference (AVcc) and select the channel (pin)
  ADMUX = (0x01 << REFS0) | (pin & 0x07);
  
  // Start the conversion
  ADCSRA |= (1 << ADSC);
  
  // Wait for the conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  // Return the 10-bit ADC value
  return ADC;
}

// Improved seed generation function
uint32_t generateSeed(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5) {

/*
    Seed Generation
    ---------------
    Pin1    Pin2    Pin3    Pin4    Pin5
     |       |       |       |       |
     v       v       v       v       v
    [LSB]   [XOR]   [LSB]   [XOR]   [LSB]
      |       |       |       |       |
      |       |       |       |       |
      v       v       v       v       v
    +---+---+---+---+---+---+---+---+
    |   |   |   |   |   |   |   |   | ... (32 bits total)
    +---+---+---+---+---+---+---+---+
              Seed
*/

  uint32_t seed = 0;
  
  // Generate a 32-bit seed by reading from 5 analog pins multiple times
  for (int i = 0; i < 32; i++) {
    // Shift the existing seed left by 1 and add the least significant bit from pin1
    seed = (seed << 1) | (readAnalog(pin1) & 0x01);
    
    // XOR the seed with the full reading from pin2
    seed ^= readAnalog(pin2);
    
    // Shift left and add LSB from pin3
    seed = (seed << 1) | (readAnalog(pin3) & 0x01);
    
    // XOR with pin4 reading
    seed ^= readAnalog(pin4);
    
    // Shift left and add LSB from pin5
    seed = (seed << 1) | (readAnalog(pin5) & 0x01);
    
    // Add some time variation to make the readings less correlated
    _delay_us(50);
  }
  
  return seed;
}

// Key generation function
void generateKey(uint8_t* key, size_t keyLength) {

/*
    Key Generation
    --------------
        Seed
         |
    +----v----+
    |  LCG    |  Linear Congruential Generator
    |  x*a+c  |  x = seed, a = 1103515245, c = 12345
    +----+----+
         |
         v
    +----+----+
    |10101010 | Take upper bits
    |01010101 |
    |10101010 |
    |01010101 |
    +----+----+
         |
         v
      Key Byte
*/

  // Generate an initial seed using 5 analog pins
  uint32_t seed = generateSeed(0, 1, 2, 3, 4);  // Using analog pins 0-4
  
  // Generate each byte of the key
  for (size_t i = 0; i < keyLength; i++) {
    // Use a linear congruential generator to evolve the seed
    seed = seed * 1103515245 + 12345;
    
    // Use the most significant byte of the upper half of the seed as a key byte
    key[i] = (seed >> 16) & 0xFF;
  }
}

void setup() {

/*
    UART Output
    -----------
    Key Byte
    11110000
     |    |
     v    v
    1111 0000
     |    |
     v    v
    'F'  '0'
     |    |
   +-+-++-+-+
   |   ||   |
   | T || T |  T = Transmit buffer
   | X || X |  X = Transmit (UART)
   |   ||   |
   +-+-++-+-+
     |    |
     v    v
    Serial Output
*/

  // Initialize ADC
  // Enable ADC, set prescaler to 128 (16MHz/128 = 125KHz ADC clock)
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Initialize UART for output (baud rate 9600)
  // Set baud rate
  UBRR0H = 0;
  UBRR0L = 103;

  // Enable transmitter
  UCSR0B = (1 << TXEN0);
  
  // Set frame format: 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  
  // Generate a 16-byte key
  uint8_t key[16];
  generateKey(key, sizeof(key));
  
  // To print the generated key as hexadecimal:

  for (int i = 0; i < sizeof(key); i++) {
    // 1. Wait for the transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0)));
    // 2. Send the high nibble
    UDR0 = "0123456789ABCDEF"[key[i] >> 4];
    // 3. Wait again
    while (!(UCSR0A & (1 << UDRE0)));
    // 4. Send the low nibble
    UDR0 = "0123456789ABCDEF"[key[i] & 0xF];
    // ... Repeat until end of key bits
  }

  // Send a newline character
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = '\n';
}

void loop() {
  // Empty loop - we only generate the key once
}