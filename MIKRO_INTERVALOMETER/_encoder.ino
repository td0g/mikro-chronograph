ISR(PCINT0_vect)
{
  static uint8_t lastInput;
  static uint8_t lastlastInput;
  static unsigned long _lastTime;
  if (millis() > _lastTime && !lastInput){
      if ((PINB & 0b00011000) == 0b00010000) {
        encoderBuffer++;
        _lastTime = millis() + ENCODER_HIGHSPEED;
      }
      else if ((PINB & 0b00011000) == 0b00001000) {
        encoderBuffer--;
        _lastTime = millis() + ENCODER_HIGHSPEED;
      }
  }
  lastInput = (PINB & 0b00011000);
}


char readEncoder(){
  if (!encoderBuffer) return 0;
  else if (encoderBuffer > 0){
    encoderBuffer--;
    if (invertWheel) return 1;
    return -1;
  }
  else {
    encoderBuffer++;
    if (invertWheel) return -1;
    return 1;
  }
}

void doEncoder(){
  static byte brightness = 7;
  int8_t dir = readEncoder();
  if (dir){
    if (currParam > 9) currDigit = 4;
    
    switch (currParam){
      case 10:
        if (dir == 1 && brightness < 7) brightness++;
        else if (dir && brightness) brightness--;
        display.setBrightness(brightness);
        break;
      case 11:
        invertDisplay = 1 - invertDisplay;
        display.flipDisplay(invertDisplay);
        break;
      case 12:
        invertWheel = 1 - invertWheel;
        titleDisplay = 2;
        break;
      case 13:
        wheelStyle = 1 - wheelStyle;
        titleDisplay = 2;
        break;
      case 14:
        if (dir == 1 & timeCal < 1100) timeCal++;
        else if (timeCal > 901) timeCal--;
        break;
      case 15:
        if (dir == -1 && !shutterOpen) {
          OPEN_SHUTTER;
          delay(200);
          CLOSE_SHUTTER;
        }
        else if (shutterOpen){
          shutterOpen = 0;
          CLOSE_SHUTTER;
        }
        else {
          shutterOpen = 1;
          OPEN_SHUTTER;
        }
        titleDisplay = 2;
        break;
      case 16:
        recallEEPROM = 1 - recallEEPROM;
        titleDisplay = 2;
        break;
      case 17:
        display.setBrightness(0);
        for (int i = EEPROM_FIRST_ADDRESS ; i <= EEPROM_LAST_ADDRESS ; i++) EEPROM.write(i, 0);
        display.setBrightness(7);
        break;
      default:  //Menu 1
  
      //Simon style
      if (!wheelStyle){
        if (currDigit == 4){
          if (!currParam && dir == -1) currParam = 4;
          else currParam += dir;
          if (currParam == 5) currParam = 0;
          titleDisplay = 0;
          displayTitle();
          exportEEPROMData();
        }
        else if (currParam < 4){
          char currDigitValue = getCurrDigitValue() + dir;
          if (currDigitValue == -1) param[currParam] += 9 * E[currDigit];
          else if (currDigitValue == 10) param[currParam] -= 9 * E[currDigit];
          else param[currParam] += dir * E[currDigit];
        }
      }
      
      //Tyler style
      else{
        if (currParam == 4){
          if (!intervalometerArmed) {
            intervalometerArmed++;
            titleDisplay = 2;
          }
          else {
            intervalometerArmed = 0;
            runIntervalometer();
          }
        }
        else {
          titleDisplay = 0;
          if (dir == 1 && param[currParam] == 9999) param[currParam] = paramMin[currParam];
          else if (dir == -1 && param[currParam] == paramMin[currParam]) param[currParam] = 9999;
          else {
            byte i = 0;
            while (param[currParam] > paramValues[i]) i++;
            if (param[currParam] != paramValues[i]) i--;
            param[currParam] = paramValues[i + dir];
          }
        }
      }
    }  
  }
}
