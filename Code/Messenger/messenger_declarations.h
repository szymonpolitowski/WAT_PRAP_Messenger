#ifndef MESSENGER_DECLARATIONS_H
#define MESSENGER_DECLARATIONS_H
#include <stdint.h>


const int c_MaxTextMsgLen   = 128;  // Maksymalna liczba znakow w wiadomosci (?tekstowej)

const int c_MaxPacketSize   = 9600; // Maksymalny rozmiar wysylanej paczki


typedef enum
{

    statusInactive      = 0,    // Nieaktywny
    statusActive        = 1,    // Aktywny
    statusDoNotDisturb  = 2,    // Nie przeszkadzac
    statusMaxIndex              //

} UserStatus_e;

typedef enum
{

    msgType_Text        = 0,
    msgType_Picture     = 1,
    msgType_NotDefined  = 2,
    msgType_Status      = 3

}MsgType_e;

typedef struct
{
    uint32_t msgType;           // Rodzaj wiadomosci
    uint32_t addressRx;         // Numer odbiorcy
    uint32_t addressTx;         // Numer nadawcy
    uint64_t timeUTC;           // Czas UTC (sekundy od epoki Linux)
    uint16_t packetSize;        // Rozmiar pakietu
    uint8_t reserved;           // RESERVED - do not use

} __attribute__((packed)) MsgHeader_s;

typedef struct
{
    uint8_t len;                // Dlugosc wiadomosci
    char msg[c_MaxTextMsgLen];  // Wiadomosc tekstowa

} __attribute__((packed)) MsgText_s;

typedef struct
{
    uint8_t picture;            // Numer obrazka

} __attribute__((packed)) MsgPicture_s;

typedef struct
{
    UserStatus_e status;        // Status uzytkownika

} __attribute__((packed)) MsgStatus_s;

typedef struct
{
    MsgHeader_s header;
    MsgText_s msg;
} __attribute__((packed)) PacketMsgText_s;

typedef struct
{
    MsgHeader_s header;
    MsgPicture_s image;
} __attribute__((packed)) PacketImgText_s;

typedef struct
{
    MsgHeader_s header;
    MsgStatus_s status;
} __attribute__((packed)) PacketStatusText_s;


#endif // MESSENGER_DECLARATIONS_H
