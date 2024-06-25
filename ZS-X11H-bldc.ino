// Constants
const double BAUD_RATE = 115200;              // Serial port baud rate
const unsigned int BUFFER_SIZE = 16;          // Serial receive buffer size

// Pin declarations for UNO board
const int PIN_PWM = 9;                        // 490Hz pins 3, 9, 10, 11

// Variables used in ReadFromSerial function
String _command = "";                         // Command received in Serial read command
int _data = 0;                                // Data received in Serial read command

void setup() 
{
    // Set PWM pins to outputs
    pinMode(PIN_PWM, OUTPUT);

    // Initialize PWM to off
    analogWrite(PIN_PWM, 0);

    // Initialize serial port
    Serial.begin(BAUD_RATE);
    Serial.println("---- Program Started ----");
}

void loop() 
{
    // Read serial data and set dataReceived to true if command is ready to be processed
    bool dataReceived = ReadFromSerial();

    // Process the received command if available
    if (dataReceived == true)
        ProcessCommand(_command, _data);
}

// Receives string data from the serial port
// Data should be in the format <command>,<data>
// Data should be terminated with a carriage return
// Function returns true if termination character received 
bool ReadFromSerial()
{    
    // Local variables   
    static String cmdBuffer;        // Stores the received command
    static String dataBuffer;       // Stores the received data
    static bool isCommand = true;   // Flag to store received bytes in command or data buffer
    byte recByte;                   // Byte received from the serial port
    
    // Check if any new data is available, if not exit
    if (Serial.available() == false)
        return false;
    
    // Read single byte from serial port
    recByte = Serial.read();
    
    // Check if byte is termination character (carriage return)
    if (recByte == '\r')
    {
        // Save buffers to global variables
        cmdBuffer.toUpperCase();
        _command = cmdBuffer;
        _data = dataBuffer.toInt();
      
        // Write what was received back to the serial port
        Serial.print("Received: "); 
        Serial.print(_command); 
        Serial.print(",");
        Serial.println(_data);
      
        // Clear local variables
        cmdBuffer = "";
        dataBuffer = "";
        isCommand = true;
      
        return true;
    }
    
    // Check if byte is a comma which separates the command from the data
    if ((char)recByte == ',')
    {
        isCommand = false;  // Next byte will be a data byte
        return false;
    }

    // Save data to one of the receive buffers
    if (isCommand)
        cmdBuffer += (char)recByte;
    else
        dataBuffer += (char)recByte;
    
    return false;
}

// Processes the command and data, sends result to serial port
void ProcessCommand(String command, int data)
{  
    // Process PWM command
    if (command == "PWM")
    {
      Serial.print("Setting pwm:  ");
      Serial.println(data);
      analogWrite(PIN_PWM, data);
    }
}

//https://mad-ee.com/controlling-a-hoverboard-motor-with-a-simple-arduino/
//https://github.com/oracid/PID-for-Hoverboard-motor-with-ZS-X11H-controller
