
#include "base64.hpp"

typedef uint8_t u8;
/// VARIABLES 
unsigned char input_buffer[128];
unsigned char input_length;
unsigned char output_buffer[128];
unsigned char output_length;


/// FUNCTIONS 
void Display_Message_Format()
{
    Serial.println("\nTo encode string format type like : e MESSAGE");
    Serial.println("\nTo decode encoded string type like : d BASE64");
}
void Print_Buffer(unsigned char * buff)
{
    Serial.println((char *) buff);
}
void Encode_Decode_Message()
{
  if(input_length > 2 && input_buffer[0] == 'e' && input_buffer[1] == ' ') 
  {
        encode_base64(input_buffer + 2, input_length - 2, output_buffer);
        input_buffer[input_length] = '\0';
        Serial.print("Input : ");
        Print_Buffer(input_buffer);
        Serial.print("\nOutput : ");
        Print_Buffer(output_buffer);
        Serial.print("\n");
        input_length = 0;
  } 
      
  else if (input_length > 2 && input_buffer[0] == 'd' && input_buffer[1] == ' ') 
      
  {
    output_length = decode_base64(input_buffer + 2, input_length - 2, output_buffer);
    output_buffer[output_length] = '\0';
        
        
    Serial.print("\n");
    Serial.print("Decoded Message: ");
    Print_Buffer(output_buffer);
      
    input_length = 0;
    } else 
    {
        Display_Message_Format();
        input_length = 0;
    }
  
}



/// MAIN PROGRAM

void setup() {
  input_length = 0;
  
  Serial.begin(9600); // shouldnt be too high
  Serial.println("Welcome to my arduino!");
}




void loop() {
   

  // Send data only when data has been recieved
  while(Serial.available() != 0)
  { 
    unsigned char next = Serial.read();
  
    // check for a character value is 255 this would be a non ascii value, 
    if(next == 0xff) 
    {
      Serial.print("!255!"); 
      delay(1);
    }
    // This happens when enter is hit
    else if(next == '\n') 
    {
      
        Encode_Decode_Message();
      
    }
        
    else 
    {
        input_buffer[input_length++] = next;
    }
  }
  
}
