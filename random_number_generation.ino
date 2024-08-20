void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Seed the random number generator
  // We use analogRead on an unconnected pin for some randomness
  randomSeed(analogRead(0));
  
  Serial.println("Random Number Generator");
  Serial.println("----------------------");
}

void loop() {
  // Generate a random number between 0 and 100
  int randomNumber = random(101);
  
  // Generate a random number between 1 and 6 (like a die roll)
  int dieRoll = random(1, 7);
  
  // Generate a larger random number (0 to 1000000)
  long largeNumber = random(1000001);
  
  // Print the random numbers
  Serial.print("Random number (0-100): ");
  Serial.println(randomNumber);
  
  Serial.print("Die roll (1-6): ");
  Serial.println(dieRoll);
  
  Serial.print("Large random number (0-1000000): ");
  Serial.println(largeNumber);
  
  Serial.println(); // Print a blank line for readability
  
  // Wait for 2 seconds before generating new numbers
  delay(2000);
}