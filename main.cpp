#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

//#define BOARD GNUBLIN
//#define BOARD RASPBERRY_PI

#include </home/satan/Programming/APIs/gnublin.h>

const char* DC1_old = "0x11";
//unsigned char esc = 0x1B;
unsigned char* DC1 = (unsigned char*) DC1_old;

void sendData(string Data)
{
    gnublin_spi SPI;
    stringstream sData;
    char bcc1=0x11;
    unsigned char bcc;
    unsigned char lang= Data.length();
    sData << bcc1 << lang << Data;
    bcc=0;
    cout << "LANG:" << Data.length() << "\n";
    for (unsigned int i=0; i<sData.str().length(); i++) {

            cout<< sData.str().at(i)<<"|";
            printf("Data[%i]: \t%x\n", i, sData.str().at(i));
            bcc+= sData.str()[i];
            }
    printf("BCC:\t%x\n", bcc);

    sData << bcc;

    cout << "\t-|-" << bcc1 << "~" << lang << "~" << Data <<  "~" << bcc << "\n";

    //cout << "\t-|-" << sData.str() << "\n";
    SPI.send((unsigned char*)sData.str().c_str(),sData.str().length());
}

int main()
{
    gnublin_spi spi;
    unsigned char B_ESC = 0x1B;
    unsigned char A_ESC = 0x23;

    spi.setSpeed(50000);
    spi.setCS(14);
    string send_buffer_2 = "TI"; // # = \x23 + ",""
    string send_buffer_3 = "TI,"; // # = \x23 + ",""
    stringstream Buffer0;
    stringstream Buffer1;
    stringstream Buffer2;
    stringstream Buffer3;
    Buffer0 << B_ESC << send_buffer_2;
    sendData(Buffer0.str());
    sleep(5);
    Buffer1 << B_ESC << send_buffer_3;
    sendData(Buffer1.str());
    sleep(5);
    Buffer2 << A_ESC << send_buffer_2;
    sendData(Buffer2.str());
    sleep(5);
    Buffer3 << A_ESC << send_buffer_3;
    sendData(Buffer3.str());
}
