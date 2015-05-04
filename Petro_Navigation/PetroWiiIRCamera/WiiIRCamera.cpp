#include"WiiIRCamera.h"

WiiIRCamera::WiiIRCamera(uint8_t deviceID, PinName sdata, PinName sclk): myDeviceID(deviceID), i2c(sdata,sclk)
{
    char cmd8[8];
    char cmd3[3];
    char cmd2[2];
    // Init IR Camera sensor
    cmd2[0]=0x30;
    cmd2[1]=0x01;
    i2c.write(myDeviceID, cmd2, 2);    
    
    cmd8[0]=0x00;
    cmd8[1]=0x00;
    cmd8[2]=0x00;
    cmd8[3]=0x00;
    cmd8[4]=0x00;
    cmd8[5]=0x00;
    cmd8[6]=0x00;
    cmd8[7]=0x90;
    i2c.write(myDeviceID, cmd8, 8);    
    wait(0.07); // delay 70ms    
    
    cmd3[0]=0x07;
    cmd3[1]=0x00;
    cmd3[2]=0x41;
    i2c.write(myDeviceID, cmd3, 3);
    wait(0.07); // delay 70ms    
    
    cmd3[0]=0x1A;
    cmd3[1]=0x40;
    cmd3[2]=0x00;
    i2c.write(myDeviceID, cmd3, 3);
    wait(0.07); // delay 70ms    
    
    cmd2[0]=0x33;
    cmd2[1]=0x03;
    i2c.write(myDeviceID, cmd2, 2);    
    
    cmd2[0]=0x30;
    cmd2[1]=0x08;
    i2c.write(myDeviceID, cmd2, 2);    
    
    wait(0.1);
}

void WiiIRCamera::read(int (&blobs)[12])
{       
    char buf[16]={0};    
    int s=0;
    char cmd[1];
    cmd[0]=0x36;
    i2c.write(myDeviceID, cmd, 1);
    i2c.read(myDeviceID, buf, 16); // read the 16-byte result
    
    blobs[0] = buf[1];
    blobs[1] = buf[2];
    blobs[2] = buf[3];
    s=blobs[2];
    blobs[0] += (s & 0x30) <<4;
    blobs[1] += (s & 0xC0) <<2;
    
    blobs[3] = buf[4];
    blobs[4] = buf[5];
    blobs[5] = buf[6];
    s=blobs[5];
    blobs[3] += (s & 0x30) <<4;
    blobs[4] += (s & 0xC0) <<2;
    
    blobs[6] = buf[7];
    blobs[7] = buf[8];
    blobs[8] = buf[9];
    s=blobs[8];
    blobs[6] += (s & 0x30) <<4;
    blobs[7] += (s & 0xC0) <<2;
    
    blobs[9] = buf[10];
    blobs[10]= buf[11];
    blobs[11]= buf[12];
    s=blobs[11];
    blobs[9] += (s & 0x30) <<4;
    blobs[10] += (s & 0xC0) <<2;
} 