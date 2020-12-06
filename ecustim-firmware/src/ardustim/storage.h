
#define EEPROM_CURRENT_VERSION  1

#define EEPROM_VERSION          1
#define EEPROM_CURRRENT_WHEEL   2
#define EEPROM_CURRENT_RPM_MODE 3
// Note: This is 2 bytes
#define EEPROM_CURRENT_RPM      4 

void loadConfig();
void saveConfig();
