/*
To Do
User defined sensitivity
*/

#ifndef __WII_IR_CAMERA__
#define __WII_IR_CAMERA__

#include"mbed.h"
class WiiIRCamera
{
    public:     explicit WiiIRCamera(uint8_t deviceID, PinName sclk, PinName sdata);
                void read(int (&blobs)[12]);  
    private:    const uint8_t myDeviceID;
                I2C i2c;    
};

#endif /* __WII_IR_CAMERA__ */

/*
#include"WiiIRCamera.h"

#define IR_DIST_cm 3.175
#define DISTANCE_DESIRED 30
#define MOTOR_SENSITIVITY_FACTOR 1
#define MAX_DISTANCE_DETECTABLE 60

#define CW 0
#define CCW !CW

Serial pc(USBTX,USBRX);
DigitalOut myled2(LED2);

DigitalOut motor1Dir(p13);
DigitalOut motor2Dir(p10);

PwmOut motor1(p21);
PwmOut motor2(p22);

int main()
{
    pc.baud(115200);
    pc.printf("Hello\n\r");
    float eucl_dist, cm_per_pixel, currentDistance, speed, motorSpeed;
    const float tan22_5=0.414;
     
    pc.printf("Initializing camera..."); 
    WiiIRCamera cam(0xB0,p28, p27);
    pc.printf("complete\n");
    int irBlobs[12]={0};
    while(1)
    {
        cam.read(irBlobs);
        eucl_dist=sqrt((float)(((irBlobs[3]-irBlobs[0])*(irBlobs[3]-irBlobs[0]))+((irBlobs[4]-irBlobs[1])*(irBlobs[4]-irBlobs[1]))));
        if(eucl_dist==0||(irBlobs[0]==1023)||(irBlobs[1]==1023)||(irBlobs[3]==1023)||(irBlobs[4]==1023))
        {
            myled2=1;
            continue;
        }
        else
        {
            myled2=0;
        }
        cm_per_pixel=IR_DIST_cm/eucl_dist;
        currentDistance=(1024*cm_per_pixel)/(2*tan22_5);
        
        speed=(DISTANCE_DESIRED - currentDistance)/(MAX_DISTANCE_DETECTABLE*MOTOR_SENSITIVITY_FACTOR);
        motorSpeed=speed;
        if(speed>0)
        {
            motor1Dir=CCW;
            motor2Dir=CCW;
        }    
        else
        {
            motor1Dir=CW;
            motor2Dir=CW;
            motorSpeed=-motorSpeed;
        }
        motor1=motorSpeed;
        motor2=motorSpeed;
        
        //pc.printf("\r%d,%d,%d,%d,%d,%d,%d,%d\n", irBlobs[0], irBlobs[1], irBlobs[3], irBlobs[4], irBlobs[6], irBlobs[7], irBlobs[9], irBlobs[10]);         //Matlab Debug
        pc.printf("%d,%d,%d,%d\n\r", irBlobs[0], irBlobs[1], irBlobs[3], irBlobs[4]);         
        pc.printf("Eucl Distance:%f\t",eucl_dist);
        pc.printf("Actual Distance:%f\tSpeed:%f\tMotorSpeed:%f\n\r",currentDistance,speed,motorSpeed);
        wait(0.050);
    }
}
*/