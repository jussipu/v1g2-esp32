#ifndef PACKETDECODER_H
#define PACKETDECODER_H

#include <string>
#include <vector>

// Packet config
#define PACKETSTART 0xAA
#define PACKETEND 0xAB
#define REQVERSION 0x01
#define DEST_V1 0x0A // send packets to the v1 device id
//#define DEST_V1_LE 0x06
#define REMOTE_SENDER 0x04 // originate packets from 0x04 - "third party use"
#define PACKET_ID_REQVERSION 0x01
#define PACKET_ID_REQSERIALNUMBER 0x03
#define PACKET_ID_REQUSERBYTES 0x11
#define PACKET_ID_REQSWEEPSECTIONS 0x22
#define PACKET_ID_REQTURNOFFMAINDISPLAY 0x32
#define PACKET_ID_REQTURNONMAINDISPLAY 0x33
#define PACKET_ID_REQMUTEON 0x34
#define PACKET_ID_REQMUTEOFF 0x35
#define PACKET_ID_REQCURRENTVOLUME 0x37
#define PACKET_ID_REQSTARTALERTDATA 0x41
#define PACKET_ID_REQBATTERYVOLTAGE 0x62

using alertsVector = std::vector<std::string>;

struct Config {
    bool xBand;
    bool kBand;
    bool kaBand;
    bool laserBand;
    std::string muteTo;
    bool bogeyLockLoud;
    bool rearMute;
    bool kuBand;
    bool euro;
    bool kVerifier;
    bool rearLaser;
    bool customFreqDisabled;
    bool kaAlwaysPrio;
    bool fastLaserDetection;
    int kaSensitivityBit0;
    int kaSensitivityBit1;
    std::string kaSensitivity;
    bool startupSequence;
    bool restingDisplay;
    bool bsmPlus;
    int autoMuteBit0;
    int autoMuteBit1;
    std::string autoMute;
};

extern Config globalConfig;

class PacketDecoder {
private:
    std::string packet;
public:
    PacketDecoder(const std::string& packet);

    std::string decode(int lowSpeedThreshold, int currentSpeed);
    std::string decodeDisplayData();
    //std::string decodeAlertData(const std::vector<alertTable>& alerts);
    void decodeAlertData(const alertsVector& alerts);
};

class Packet {
public:
    static uint8_t calculateChecksum(const uint8_t *data, size_t length);
    static uint8_t* constructPacket(uint8_t destID, uint8_t sendID, uint8_t packetID, uint8_t *payloadData, uint8_t payloadLength, uint8_t *packet);
    static uint8_t* reqStartAlertData();
    static uint8_t* reqVersion();
    static uint8_t* reqSweepSections();
    static uint8_t* reqSerialNumber();
    static uint8_t* reqTurnOffMainDisplay();
    static uint8_t* reqTurnOnMainDisplay();
    static uint8_t* reqBatteryVoltage();
    static uint8_t* reqMuteOff();
    static uint8_t* reqMuteOn();
    static uint8_t* reqCurrentVolume();
    static uint8_t* reqUserBytes();
};

#endif // PACKETDECODER_H