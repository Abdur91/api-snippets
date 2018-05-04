/*
 * Twilio Machine to Machine Commands Quickstart on Arduino.
 * 
 * Uses a SIMCom SIM800. Any ATMega328 board should work, just change the 
 * pins and wiring.
 */
#include <SoftwareSerial.h>
#include "SIM800Twilio.hpp"

/* 
 *  Software Serial definitions:
 *  https://www.arduino.cc/en/Reference/SoftwareSerial
 *  
 *  If you get errors, lower the modem baud rate.
 */
#define RX_PIN 2
#define TX_PIN 3
#define MODEM_BAUD 4800

SIM800Twilio modem(RX_PIN, TX_PIN, MODEM_BAUD);

/* One time setup things - serial, modem */
void setup() 
{
        Serial.begin(115200);
        Serial.println("Twilio Programmable Wireless SIM800L Demo");
        modem.begin();
}


/* Endless loop. Add your code here to customize this example. */
void loop() 
{
        /* 
         *  Keep `command` under 160 ASCII characters, or 67 UCS-2 characters.
         *  https://www.twilio.com/docs/glossary/what-sms-character-limit
         */
        String command = "Ahoy, world!";

        /* 
         *  Write a Twilio M2M command. 
         */
        Serial.print("Sending command: ");
        Serial.println(command);
        modem.send_command(command);

        /* 
         *  Read a Twilio M2M command. Note that it will find the lowest 
         *  indexed one with the code as is; in your code. if you cache the 
         *  index you can start the next read_command to move to the next one.
         */
        Serial.println("\r\nLooking for a M2M command...\r\n");
        M2MCommand m2m;

        /* Index to start search for M2M command */
        static uint8_t index = 34; 

        /* Delete any SMS encountered which are not commands? */
        bool delete_non_commands = false;

        /* If you find a command, print out the index, timestamp, and command. */
        if (modem.read_command(m2m, index, delete_non_commands)) {
                Serial.println("----------------------------------------");
                Serial.print("Index: ");
                Serial.println(m2m.index);

                Serial.print("Date: ");
                Serial.println(m2m.date);

                Serial.print("\r\n");
                Serial.println(m2m.command);
        } else {
               Serial.println("Couldn't find a M2M command!"); 
        }

        /* That's all, folks! */
        Serial.println("Finished.");
        while(1) {
                delay(5000);
        }
}

