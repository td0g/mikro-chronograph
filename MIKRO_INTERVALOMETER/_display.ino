uint8_t getCurrDigitValue(){
  int temp = param[currParam] / E[currDigit];
  temp %= 10;
  return temp;
}

/*
    Display functions:
    runDisplay    --> controls flow of other functions

    displayTitle  --> called by other functions to activate title
    showParamValue    --> called regularly if no title active, can blink digit
    showString    --> called regularly if title active, can scroll

    printOrientation  --> final function to correct orientation
 */

 void runDisplay(){
  if (titleDisplay > 1) displayTitle();
  else if (currParam < 4) showNumber(param[currParam]);
  else if (currParam == 14) showNumber(timeCal);
}

void displayTitle(){
  switch (currParam){
    case 0: showString(TXT_init, 13); break;
    case 1: showString(TXT_inter, 13); break;
    case 2: showString(TXT_bulb, 14); break;
    case 3: showString(TXT_shots, 16); break;
    case 4: if (intervalometerArmed) showString(TXT_goArmed, 4); else showString(TXT_go, 4); break;
    case 10: showString(TXT_brgt,4); break;
    case 11: showString(TXT_up, 4); break;
    case 12: if (invertWheel) showString(TXT_dir1, 4); else showString(TXT_dir0, 4); break;
    case 13: if (!wheelStyle) showString(TXT_optSimon, 4); else showString(TXT_optTyler, 4); break;
    case 14: showString(TXT_ocal, 4); break;
    case 15: if (shutterOpen) showString(TXT_open, 4); else showString(TXT_close, 4); break;
    case 16: if (recallEEPROM) showString(TXT_zero, 4); else showString(TXT_recall, 4); break;
    case 17: showString(TXT_reset, 4); break;
  }
}

void showNumber(unsigned int altValue){ 
  static uint8_t lastParam = 255;
  static uint16_t lastValue;
  static uint8_t lastDigit;
  static unsigned long blinkTimer;
  static uint8_t blinkOn;

  if (!altValue) altValue = param[currParam];
  if (altValue != lastValue  || lastDigit != currDigit || titleDisplay == 0){
    if (currParam != lastParam || !titleDisplay) display.clearLineState();//display.setMask();
    display.showNumberDec(altValue);
    lastDigit = currDigit;
    lastValue = altValue;
    titleDisplay = 1;
    if (currDigit < 4){
      if (!titleDisplay) display.forceLineState(3-currDigit, 0, 127 * blinkOn);//display.toggleDigitMask(3 - currDigit);
      if (altValue < E[currDigit]){
        byte zero[1] = {63};
        display.setSegments(zero, 1, 3 - currDigit);
      }
    }
  }
  if (millis() > blinkTimer && currDigit < 4) {
      blinkTimer = millis() + CHAR_BLINKRATE;
      blinkOn = 1 - blinkOn;
      if (blinkOn) display.forceLineState(3 - currDigit, 0, 127);
      else display.clearLineState();
  }
  else if (currDigit > 3 && !blinkOn) {blinkOn = 1; display.clearLineState();}
}

void showString(const byte iString[], byte stringLen){
  static const unsigned int firstShiftTime = STRING_SCROLLSTART;
  static const unsigned int nextShiftTime = STRING_SCROLL;
  static const unsigned int noShiftTime = STRING_NOSCROLL;
  static const unsigned int lastShiftTime = STRING_SCROLLEND;
  
  static unsigned long timer;
  static byte shiftRight;
  static byte len;
  static byte segs[4];
  
  if (titleDisplay < 3){
    display.clearLineState();
    titleDisplay = 3;
    shiftRight = 0;
    len = stringLen;
    if (len > 4) timer = millis() + firstShiftTime;
    else timer = millis() + noShiftTime;
    for (byte i = 0; i < 4; i++){
      if (i < len) segs[i] = iString[i];
      else segs[i] = 0; 
    }
    display.setSegments(segs);
  }
  else if (millis() > timer){
    if (shiftRight + 4 < len){
      shiftRight++;
      if (shiftRight + 4 < len) timer += nextShiftTime;
      else timer += lastShiftTime;
      for (byte i = 0; i < 4; i++){
        segs[i] = iString[i + shiftRight];
      }
      display.setSegments(segs);
    }
    else if (currParam < 4 || currParam == 14) titleDisplay = 0; 
  }
}
