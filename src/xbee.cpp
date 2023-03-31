#include "SoftwareSerial.h"

#include "xbee.hpp"

uint8_t* XBee:makePacket(String data, uint8_t dest_addr[8]) {
    int totalLength = data.length();
    uint8_t* buf = malloc(totalLength + 18 * sizeof(uint8_t));

    /* Start delimiter */
    buf[0] = 0x7E;
    
    /* Packet length */
    buf[1] = 0x00;
    buf[2] = (totalLength & 0xff) + 14;

    /* Frame type */
    buf[3] = 0x10; // Transmit Request

    /* Frame ID */
    buf[4] = 0x01;

    /* 64 bit address */
    for(int i = 0; i < 8; i++) buf[5 + i] = dest_addr[i];

    /* 16 bit address */
    buf[13] = 0xFF;
    buf[14] = 0xFE;

    /* Broadcast radius */
    buf[15] = 0x00;

    /* Options */
    buf[16] = 0x00;

    /* Payload */
    for(int i = 0; i < totalLength; i++) buf[17 + i] = (data[i] & 0xFF);

    uint8_t sum = 0x00;
    for(int i = 3; i < totalLength + 17; i++) {
        sum += buf[i];
    }

    /* Checksum */
    buf[totalLength + 17] = 0xFF - sum;

    return buf;
}

void XBee:sendData(SoftwareSerial xbeeSerial, String data, uint8_t dest_addr[8]) {
    uint8_t* packet = makePacket(data, dest_addr);
    for(int i = 0; i < data.length() + 18; i++) xbeeSerial.write(buf[i]);
    free(packet);
}