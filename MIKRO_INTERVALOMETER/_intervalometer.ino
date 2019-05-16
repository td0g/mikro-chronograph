void runIntervalometer(){
  currParam = 0;
  iShotsLeft = param[3];
  iNextTime = millis() + param[0] * timeCal;
  waitIntervalometer();
  while (iShotsLeft){
    iShotsLeft--;
    OPEN_SHUTTER;
    shutterOpen = 1;
    iNextTime += param[2] * timeCal;
    waitIntervalometer();
    CLOSE_SHUTTER;
    shutterOpen = 0;
    if (iShotsLeft) {
      iNextTime += param[1] * timeCal;
      waitIntervalometer();
    }
  }
  display.clearLineState();
  titleDisplay = 2;
}

void waitIntervalometer(){
  static unsigned long timer;
  static char ivInfoType;
  static byte displayBlank;
  static byte cycle;
  static unsigned int lastNumber;

  byte swirl;
  static unsigned long swirlTimer;
  
  while (millis() < iNextTime){

    switch (readBtn()){    //End session
      case 2:
        iNextTime = millis();
        iShotsLeft = 0;
        break;
      case 1:
        if (swirlTimer == 0b11111111111111111111111111111111) swirlTimer = 0;
        else {swirlTimer = 0b11111111111111111111111111111111; display.clearLineState();}
    }

    switch (readEncoder()){
    case 1:
      cycle = 0;
      displayBlank = 0;
      ivInfoType = (ivInfoType + 1) % 3;   //0 or 1 or 2?
      timer = millis();
      break;
    case -1:
      timer = millis();
      displayBlank = cycle;
      cycle = 1 - cycle;
      if (cycle) ivInfoType = 0;
      else display.setSegments(TXT_blank);
      break;
    }

    if (!displayBlank){
      if (millis() > timer){
        
        titleDisplay = 2;
        timer = millis() + INTERVALOMETER_DISPLAYCYCLE;
        if (cycle) ivInfoType = (ivInfoType + 1) % 3;
      }
      if (titleDisplay > 1) {
        switch (ivInfoType){
          case 0: showString(TXT_shotsleft, 11); break;
          case 1: showString(TXT_tillnextshot, 21); break;
          case 2: showString(TXT_timeleft, 15); break;
        }
      }
      else {
        unsigned long temp;
        switch (ivInfoType){
          case 0: if (lastNumber != iShotsLeft) {display.showNumberDec(iShotsLeft); lastNumber = iShotsLeft;} break;
          case 1: temp = iNextTime - millis(); temp /= timeCal; if (temp != lastNumber){display.showNumberDec(temp); lastNumber = temp;} break;
          case 2:
            temp = iNextTime - millis(); 
            temp /= timeCal;   //Time until next actuation 
            temp += (param[1] + param[2]) * iShotsLeft;
            if (!shutterOpen) temp -= param[1];
            if (lastNumber != temp){
              showNumber(temp);  //Total time remaining
              lastNumber = temp;
            }
            break;
        }
      }
    }
    if (shutterOpen && millis() > swirlTimer && (titleDisplay < 2 || displayBlank)){
      swirlTimer = millis() + 25;
      switch (swirl){
        case 0:display.forceLineState(0, 1, 32); display.forceLineState(1, 255, 1); break;
        case 1: display.forceLineState(1, 1, 2); display.forceLineState(0, 0, 1); break;
        case 2: display.forceLineState(1, 2, 5); display.forceLineState(0, 0, 0); break;
        case 3: display.forceLineState(1, 4, 10); break;
        case 4: display.forceLineState(1, 8, 4); display.forceLineState(0, 0, 8); break;
        case 5: display.forceLineState(1, 0, 8); display.forceLineState(0, 8, 16); break;
        case 6: display.forceLineState(0, 16, 40); display.forceLineState(1, 0, 0); break;
        case 7: display.forceLineState(0, 32, 17); break;
      }
      swirl = (swirl + 1) % 8;
    }
    else if (!shutterOpen && swirl < 8 && !displayBlank){
      swirl = 8;
      display.clearLineState();
    }
  }
}
