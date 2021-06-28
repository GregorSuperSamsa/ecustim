#include "Protocol.h"

// // Based on the CRC8 formulas by Dallas/Maxim
// uint8_t Protocol::calculateCRC(const uint8_t *data, uint8_t data_length)
// {
//   uint8_t crc = 0x00;
  
//   while (data_length--) 
//   {
//     uint8_t extract = *data++;
    
//     for (uint8_t tempI = 8; tempI; tempI--) 
//     {
//       uint8_t sum = (crc ^ extract) & 0x01;
//       crc >>= 1;
//       if (sum) 
//       {
//         crc ^= 0x8C;
//       }
//       extract >>= 1;
//     }
//   }

//   return crc;
// }
