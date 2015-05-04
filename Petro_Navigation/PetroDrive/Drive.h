#ifndef __DRIVE_H__
#define __DRIVE_H__

#include"mbed.h"
class Drive
{
    public:     explicit Drive(PinName leftDrivePin, PinName leftDirectionPin, PinName rightDrivePin, PinName rightDirectionPin);
                void setDrive(float leftDriveSpeed, float rightDriveSpeed);
    private:    PwmOut leftDrive, rightDrive;
                DigitalOut leftDriveEN, rightDriveEN;
                const bool CW;
};

#endif /* __DRIVE_H__ */

/*
#include"Drive.h"

int main()
{
    Drive PetroDrive(p21,p13,p22,p10);
    PetroDrive.setDrive(0.2,0.2);
    wait(2);
    PetroDrive.setDrive(2,2);
    wait(2);
    PetroDrive.setDrive(-0.2,-0.2);
    wait(2);
    PetroDrive.setDrive(-2,-2);
    while(1)
    {
        
    }
}
*/