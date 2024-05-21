void setup() {
    // Set pin 13 (PB5) as an output
    DDRB |= (1 << DDB5); // DDB5 is the bit in DDRB corresponding to PB5

    // Alternatively, you could use:
    // DDRB = DDRB | (1 << PB5); // Same as DDRB |= (1 << DDB5)
}

void loop() {
    // Turn the LED on
    PORTB |= (1 << PORTB5); // Set PB5 high to turn on the LED

    // Wait for a second
    delay(100);

    // Turn the LED off
    PORTB &= ~(1 << PORTB5); // Set PB5 low to turn off the LED

    // Wait for a second
    delay(100);
}

/*
//Registers
DDR (Data Direction Register): Determines whether each pin is an input or output.
PORT: Controls the output state of each pin (HIGH or LOW).
PIN: Reads the input state of each pin.
//Port Mapping
PORTB: Controls digital pins 8 to 13.
PORTC: Controls analog input pins (A0 to A5).
PORTD: Controls digital pins 0 to 7.
*/
