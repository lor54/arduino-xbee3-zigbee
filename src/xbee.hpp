#ifndef XBEE_HPP
#define XBEE_HPP

class XBee {
    public:
        static void sendData(String data);
    private:
        static uint8_t* makePacket(String data, uint8_t dest_addr[8]);
};

#endif /* XBEE_HPP */