#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD * 16UL))) - 1)


// UART Initialization
/*
   UART Register Configuration:
   
   UBRR0H:UBRR0L    UCSR0B     UCSR0C
   [   Baud Rate  ] [Tx Enable] [Frame Format]
   [     16 bits  ] [  8 bits ] [   8 bits   ]
          |              |            |
          v              v            v
   +--------------+    +-----+    +----------+
   | Clock Divider|--->|  Tx |--->| 8N1 Mode |
   +--------------+    +-----+    +----------+
          |                            |
          |   +------------------------+
          v   v
    [UART Hardware]
         |
         v
    Serial Output
*/

void uart_init() {
  UBRR0H = (uint8_t)(BAUD_PRESCALER>>8); // This is the HIGH byte of baud rate
  UBRR0L = (uint8_t)(BAUD_PRESCALER);    // This is the LOW byte of baud rate
  
  UCSR0B = (1<<TXEN0); // This enables the transmitter by setting the TXEN0 bit to 1

  // To actually send data, we need to set the frame format
  // By setting USCZ01 and USCZ00 to 1, we get 8 data bits, no parity, and one stop bit.
  // See here for more reference material: https://ucbeginner.com/learn-arduino-uart-serial/
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); 
}

// UART Transmission
/*
   Data Transmission Process:
   
   [Data Byte]
       |
       v
   +-------+
   | UDRE0 |<--- Check if empty
   +-------+
       |
       v
   +-------+
   | UDR0  |<--- Load data
   +-------+
       |
       v
   [Tx Pin]
*/

void uart_transmit(uint8_t data) {
  // First we wait for empty transmit buffer  
  while (!(UCSR0A & (1<<UDRE0))); 
  // and then we move data into the buffer (send it)
  UDR0 = data;
}

void uart_print_string(const char* str) {
  while (*str) uart_transmit(*str++);
}

void uart_print_number(int num) {
  char buffer[7];
  itoa(num, buffer, 10);
  uart_print_string(buffer);
}

void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    uart_print_number(arr[i]);
    uart_transmit(' ');
  }
  uart_transmit('\r');
  uart_transmit('\n');
}

/*
   Linear Congruential Generator (LCG):
   
   [custom_seed] --+
        |          |
        v          |
   +-----------+   |
   | x1664525  |   |
   +-----------+   |
        |          |
        v          |
   +-----------+   |
   |  +1013904223  |
   +-----------+   |
        |          |
        v          |
   [New Seed] -----+
        |
        v
   [Random Number]
*/

static uint32_t custom_seed = 1;

uint32_t custom_random() {
  custom_seed = custom_seed * 1664525 + 1013904223;
  return custom_seed;
}

void custom_random_seed(uint32_t new_seed) {
  custom_seed = new_seed;
}

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// QuickSort Partition
/*
   Partition Process:
   
   [Array]    [Pivot]
     |           |
     v           v
   +---+---+---+---+---+---+---+
   | 64| 34| 25| 12| 22| 11| 90|
   +---+---+---+---+---+---+---+
     ^                       ^
     low                    high
     |                       |
     v                       v
   [i]                     [j]
     -->                 <--
   
   Swap elements until i and j cross
*/

int partition(int arr[], int low, int high) {
  int pivot = arr[low + (custom_random() % (high - low + 1))];
  int i = low - 1;
  int j = high + 1;

  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j) return j;

    swap(&arr[i], &arr[j]);
  }
}

// QuickSort Recursion
/*
   QuickSort Recursive Process:
   
   [Unsorted Array]
         |
         v
   +-------------+
   |  Partition  |
   +-------------+
         |
         v
   +-----+-----+
   |     |     |
   v     v     v
 [Left] [Pivot] [Right]
   |             |
   |   Recurse   |
   +-------------+
*/

void quickSort(int arr[], int low, int high, int size) {
  if (low < high) {
    int pi = partition(arr, low, high);
    
    uart_print_string("Partition around ");
    uart_print_number(arr[pi]);
    uart_print_string(": ");
    print_array(arr, size);

    quickSort(arr, low, pi, size);
    quickSort(arr, pi + 1, high, size);
  }
}

void setup() {
  uart_init();


// ADC Initialization and Reading
/*
   ADC Process:
   
   [Analog Pin]
        |
        v
   +----------+
   |   ADC    |
   | Hardware |
   +----------+
        |
        v
   [Digital Value]
        |
        v
   [Seed RNG]
*/

  // Seed the RNG using ADC noise
  ADCSRA |= (1 << ADEN);        // 1. Enable ADC
  ADCSRA |= (1 << ADSC);        // 2. Start conversion
  while (ADCSRA & (1 << ADSC)); // 3. Wait for completion
  custom_random_seed(ADC);      // 4. Use ADC value as seed

  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr) / sizeof(arr[0]);

  uart_print_string("Original array:\r\n");
  print_array(arr, n);

  uart_print_string("\r\nSorting process:\r\n");
  quickSort(arr, 0, n - 1, n);

  uart_print_string("\r\nSorted array:\r\n");
  print_array(arr, n);
}

void loop() {
  // Empty
}