void getEEPROMEEPROMIndex(){
  EEPROMNumerator = EEPROM.read(EEPROM_FIRST_ADDRESS) & 0b10000000;
  EEPROMIndex = EEPROM_FIRST_ADDRESS;
  for (int i = EEPROM_FIRST_ADDRESS + EEPROM_BLOCK_SIZE; i < (EEPROM_LAST_ADDRESS - EEPROM_BLOCK_SIZE); i += EEPROM_BLOCK_SIZE){
    if ((EEPROM.read(i) & 0b10000000) != EEPROMNumerator){
      EEPROMIndex = i;
      i = EEPROM_LAST_ADDRESS;
    }
  }
}


void importEEPROMData(){
  int j = EEPROMIndex;
  for (byte i = 0; i < 4; i++){
    param[i] = EEPROM.read(j) & 0b00111111;
    param[i] *= 256;
    j++;
    param[i] += EEPROM.read(j);
    j++;
    param[i] = max(param[i], paramMin[i]);
  }
}


void incrementEEPROMIndex(){
  if (EEPROMIndex == EEPROM_FIRST_ADDRESS) EEPROM.write(EEPROMIndex, 128 - EEPROMNumerator);
  else EEPROM.write(EEPROMIndex, EEPROMNumerator);
  
  EEPROMIndex += EEPROM_BLOCK_SIZE;
  if (EEPROMIndex + EEPROM_BLOCK_SIZE > EEPROM_LAST_ADDRESS) EEPROMIndex = EEPROM_FIRST_ADDRESS;

  for (byte i = 0; i < 8; i++) lastEEPROMRead[i] = EEPROM.read(i + EEPROMIndex);
}



void exportEEPROMData(){
  byte temp;
  byte j;

  for (byte i = 0; i< 4; i++){
    temp = param[i] >> 8;
    temp = (temp & 0b00111111) + (lastEEPROMRead[j] & 0b10000000);  //2.1
    if (temp != lastEEPROMRead[j]){
      EEPROM.write(j + EEPROMIndex, temp);
      lastEEPROMRead[j] = temp;
    }
    j++;
    temp = param[i];
    if (temp != lastEEPROMRead[j]) {
      EEPROM.write(j + EEPROMIndex, temp);
      lastEEPROMRead[j] = temp;
    }
    j++;
  }
}
