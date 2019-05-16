
/*
 * Written by Tyler Gerritsen & Simon Schramm
 * vtgerritsen@gmail.com
 * Intervalometer using ATTiny85, TM1637, & rotary encoder
 * NON-OPTOISOLATED
 * 
 * 
 * Written for ATTiny85 @ 1mHz
 * If ATTiny85 is not available in board selection:
 * Preferences -> Additional Board Manager URL's -> add https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
 * Tools -> Board -> Board Manager -> ATTiny series -> Install
 */

/*
 * 
 * 2017-07-09 1.0
 * Functional Intervalometer
 * 
 * 2017-12-18 1.1
 * Session settings saved to EEPROM
 * First bit in EEPROM block is numerator
 * Reset function clears all EEPROM between first and las addresses
 * Zero / Recall user setting can be overridden by holding button on startup
 * 
 * 2018-12-20 1.2.0
 * New 'Swirl' during intervalometer operation
 * Can be turned off by short button press during operation
 * 
 * 2018-09-12 1.2.1
 * Removed optoisolator
 * Now shutter pin toggles between Output-Low and Tri-State (High-Impedance)
 * 
 * 2018-09-13 1.2.2
 * Changed encoder code from polling to interrupt
 * Added pullup to encoder - Improved response of KY-040
 * 
 * 2019-05-16 1.2.3
 * Updated display library
 */
 
 //Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include "TD0G_1637.h"
#include "strings.h"

//Pins
#define CAMERA_PIN 2
#define OPEN_SHUTTER pinMode(CAMERA_PIN, OUTPUT);
#define CLOSE_SHUTTER pinMode(CAMERA_PIN, INPUT);
#define INITIALIZE_SHUTTER_PIN digitalWrite(CAMERA_PIN, 0)

#define ENCODER_PIN_1 3
#define ENCODER_PIN_2 4
#define ENCODER_INPUT PINB >> 3     //For pins 3 & 4, use 'PINB >> 3'

#define CLK 0                       //TM1637 Module
#define DIO 1                       //TM1637 Module
tm1637 display(CLK, DIO);

//UI Settings
#define STRING_SCROLLSTART 300
#define STRING_SCROLL 100
#define STRING_SCROLLEND 250
#define STRING_NOSCROLL 750
#define STRING_MAXLENGTH 10
#define CHAR_BLINKRATE 300
#define BUTTON_DEBOUNCE 150
#define BUTTON_LONGHOLD 800
#define ENCODER_HIGHSPEED 10
#define INTERVALOMETER_DISPLAYCYCLE 10000
#define INTERVALOMETER_SELECTABLEVALUES 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 75, 100, 150, 200, 250, 300, 400, 500, 750, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 7500, 9999, 10000

//EEPROM
#define EEPROM_FIRST_ADDRESS 2    //Addresses 0 & 1 hold user settings
#define EEPROM_LAST_ADDRESS  511  //511 is last available address in ATTiny85
#define EEPROM_BLOCK_SIZE 8       //2 bytes per session setting



const uint8_t CHAR_blank[1] = CHAR_BLANK;
const uint8_t TXT_all[] = TXT_ALL;
const uint8_t TXT_blank[] = {0, 0, 0, 0};
const uint8_t TXT_done[] = TXT_DONE;
const uint8_t TXT_go[] = TXT_GO;
const uint8_t TXT_goArmed[] = TXT_GOARMED;
const uint8_t TXT_brgt[] = TXT_BRGT;
const uint8_t TXT_don1[] = TXT_DON1;
const uint8_t TXT_don0[] = TXT_DON0;
const uint8_t TXT_ocal[] = TXT_OCAL;
const uint8_t TXT_test[] = TXT_TEST;
const uint8_t TXT_open[] = TXT_OPEN;
const uint8_t TXT_close[] = TXT_CLOSE;
const uint8_t TXT_init[] = TXT_INIT;
const uint8_t TXT_shots[] = TXT_SHOTS;
const uint8_t TXT_bulb[] = TXT_BULB;
const uint8_t TXT_inter[] = TXT_INTER;
const uint8_t TXT_up[] = TXT_UP;
const uint8_t TXT_dir0[] = TXT_DIR0;
const uint8_t TXT_dir1[] = TXT_DIR1;
const uint8_t TXT_opt[] = TXT_OPT;
const uint8_t TXT_opt1[] = TXT_OPT1;
const uint8_t TXT_opt2[] = TXT_OPT2;
const uint8_t TXT_optSimon[] = TXT_OPTSIMON;
const uint8_t TXT_optTyler[] = TXT_OPTTYLER;
const uint8_t TXT_timeleft[] = TXT_TOTALTIMELEFT;
const uint8_t TXT_shotsleft[] = TXT_SHOTSLEFT;
const uint8_t TXT_tillnextshot[] = TXT_TILLNEXTSHOT;
const uint8_t TXT_reset[] = TXT_RESET;
const uint8_t TXT_zero[] = TXT_ZERO;
const uint8_t TXT_recall[] = TXT_RECALL;

const unsigned int E[4] = {1, 10, 100, 1000};
unsigned int param [4] = {0, 1, 1, 1};    //init delay, inter delay, bulb, shots
const byte paramMin[4] = {0, 1, 1, 1};
const unsigned int paramValues[] = { INTERVALOMETER_SELECTABLEVALUES };
char currParam;
int8_t currDigit = 4;
unsigned int iShotsLeft;
unsigned long iNextTime;

unsigned long dataTime;
uint8_t wheelStyle;
uint8_t invertWheel;

const unsigned int showTitleTime = 800;
uint8_t invertDisplay = 0;
uint8_t titleDisplay = 0;
uint8_t recallEEPROM;

uint8_t userSettings;

volatile int16_t encoderBuffer;

unsigned int timeCal = 1000;
const byte timeCalAddress = 0;
const byte userSettingsAddress = 1;

const byte shutterPin = CAMERA_PIN;
byte shutterOpen;

byte intervalometerArmed;

int EEPROMIndex;
byte EEPROMNumerator;
byte lastEEPROMRead[8];

//Button pin is tied to 5v w/ 68k, switch w/ 100k -- Reads 1023 released, ~750 depressed

void setup()
{
  //Set pin inputs/outputs, make sure shutter isn't opened
  INITIALIZE_SHUTTER_PIN;
  pinMode(ENCODER_PIN_1, INPUT_PULLUP);
  pinMode(ENCODER_PIN_2, INPUT_PULLUP);
  CLOSE_SHUTTER;
  
  MCUCR = MCUCR & 0b11111101;
  MCUCR = MCUCR | 0b00000001;
  GIMSK = 0b00100000;    // turns on pin change interrupts
  PCMSK = 0b00011000;    // turn on interrupts on pins PB3
  sei();                 // enables interrupts

  //Start ADC on reset pin (button pin)
  ADCSRA = bit(ADEN); //Turn ADC on
  ADMUX = 0; //ADC0 (reset pin), Vcc as reference, no ADLAR adjustment
  bitSet(ADCSRA, ADSC); //Start conversion

  //Start with blank display
  display.setSegments(TXT_blank);
  
  //Check EEPROM integrity, import user settings
  userSettings = EEPROM.read(timeCalAddress);
  if (userSettings && userSettings < 255){  //EEPROM good
    timeCal = userSettings + 850; 
    userSettings = EEPROM.read(userSettingsAddress);
    if (userSettings & 0b00000001) invertDisplay = 1;
    if (userSettings & 0b00000010) wheelStyle = 1;
    if (userSettings & 0b00000100) invertWheel = 1;
    if (userSettings & 0b00001000) recallEEPROM = 1;
  }
  else {timeCal = 1000; EEPROM.write(timeCalAddress, 150); EEPROM.write(userSettingsAddress, 0);}                  //EEPROM corrupted (reset), save default values

  //Turn on display
  display.setBrightness(7); display.flipDisplay(invertDisplay);

  //Setup EEPROM session memory
  getEEPROMEEPROMIndex();
  while (!bit_is_clear(ADCSRA, ADSC)) {};   //Wait for conversion
  if (ADC > 900) {if (!recallEEPROM) importEEPROMData();}
  else if (recallEEPROM) importEEPROMData();
  incrementEEPROMIndex(); exportEEPROMData();

  //Show display, wait for button to release if currently pressed
  displayTitle();
  while (ADC < 900) {runDisplay(); if (bit_is_clear(ADCSRA, ADSC)) bitSet(ADCSRA, ADSC);} //Wait for button to release
}




void loop(){doButton(); runDisplay(); doEncoder();}
