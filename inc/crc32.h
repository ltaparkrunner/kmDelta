#ifndef CRC32_H
#define CRC32_H
#include <QByteArray>
const int crc32_num = 256;
uint32_t crc32(QByteArray buf, int len);
uint16_t Crc16(QByteArray nData, int wLength);

#endif // CRC32_H
