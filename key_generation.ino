// This sketch is an example of a basic cryptographic key generator for an Arduino using the random() function. The key generated here is a simple symmetric key, NOT intended for use outside of illustrating the concept.
//        
//        Generates a 128-bit cryptographic key using the random() function:
//            16 bytes (128 bits), where each byte is a random number between 0 and 255.
//
//  1. Seed the random number generator using a predefined value, later this will be replaced with a
//      more sophisticated entropy source or method to ensure better randomness.
//
//  2. We generate each byte of the key by calling random(256). This function returns a pseudo-random
//      number between 0 and 255, which is then stored in the cryptoKey array.
//
//  3. Finally, we print the generated key in hexadecimal format to the Serial Monitor for inspection.

#define KEY_LENGTH 16 
byte cryptoKey[KEY_LENGTH];
unsigned long insecureSeed = 123456789; 

void seedRandomGenerator() {
    randomSeed(insecureSeed);
}

void generateCryptoKey() {
    for (int i = 0; i < KEY_LENGTH; i++) {
        cryptoKey[i] = random(256); 
    }
}

void printKey() {
    Serial.print("Generated Key: ");
    for (int i = 0; i < KEY_LENGTH; i++) {
        if (cryptoKey[i] < 0x10) {
            Serial.print("0");
        }

        Serial.print(cryptoKey[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    seedRandomGenerator();
    generateCryptoKey();
    printKey();
}

void loop() {
    
}

