uint8_t readBtn(){  //Return 1 if short pressed & released, Return 2 if long pressed PRIOR to release
  static unsigned long debounceTimer;
  static byte buttonPos;
  if (bit_is_clear(ADCSRA, ADSC)){  //ADC conversion is complete
    bitSet(ADCSRA, ADSC);
    if (ADC < 900 && millis() > debounceTimer){   //Button depressed
      if (!buttonPos){ buttonPos = 1; debounceTimer = millis() + BUTTON_LONGHOLD;}
      else if (buttonPos == 1){buttonPos = 2; return 2;}
    }
    else if (buttonPos && ADC > 899) {
      debounceTimer = millis() + BUTTON_DEBOUNCE;
      if (buttonPos == 1) {buttonPos = 0; return 1;}
      buttonPos = 0;
    }
    return 0;
  }
}
  
void doButton(){
  switch (readBtn()){
    case 2: currParam = 10; titleDisplay = 2; break;          //Long button press
    case 1:                                                   //Short button press
      if (currParam > 4){
        currParam++;
        titleDisplay = 2;
        if (currParam == 15 && EEPROM.read(timeCalAddress) != (timeCal - 850))EEPROM.write(timeCalAddress, timeCal - 850);                    //Save Timecal to EEPROM
        else if (currParam == 16) {shutterOpen = 0; CLOSE_SHUTTER;}
        else if (currParam == 18) {EEPROM.write(userSettingsAddress, invertDisplay + wheelStyle * 0b00000010 + invertWheel * 0b00000100 + recallEEPROM * 0b00001000); currParam = 0;}  //Save all other user settings to EEPROM
      }
    
      //Tyler style, menu 1
      else if (wheelStyle) {currParam = (currParam + 1) % 5; intervalometerArmed = 0; titleDisplay = 2; exportEEPROMData();}
    
      //Simon style, menu 1
      else if (currParam == 4) runIntervalometer();
      else {
        if (titleDisplay < 3) currDigit++; currDigit %= 5; if (currDigit == 4) exportEEPROMData();
        if (currDigit == 4 && paramMin[currParam] > param[currParam]) param[currParam] = paramMin[currParam];
        titleDisplay = 0; 
      }
    break;
  }
}
