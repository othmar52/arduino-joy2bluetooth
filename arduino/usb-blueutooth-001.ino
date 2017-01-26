#include <SoftwareSerial.h>
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <String.h>


// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include "hidjoystickrptparser.h"

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);


int bluetoothTx = 7;
int bluetoothRx = 6;
int ledPin = 13;                 // LED connected to digital pin 13
String data;


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
//USBHub Hub1(&Usb);

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output

  //Setup usb serial connection to computer
  Serial.begin(115200);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("Start");

        if (Usb.Init() == -1)
                Serial.println("OSC did not start.");

        delay(200);

        if (!Hid.SetReportParser(0, &Joy))
                ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop()
{
  //Read from usb serial to bluetooth
  //if(Serial.available())
  //{

  if (Serial.available() > 0) {
    //data = Serial.readString();
    //Serial.println(Serial.read());
    //bluetooth.println(Serial.readString());
    bluetooth.println('A');
  }
    Usb.Task();
    Serial.flush();
    //delay(2000);
    

    //digitalWrite(ledPin, HIGH);   // sets the LED on
    //delay(1000);                  // waits for a second
    //digitalWrite(ledPin, LOW);    // sets the LED off
    //delay(1000);                  // waits for a second  

   

    
 // }

}
