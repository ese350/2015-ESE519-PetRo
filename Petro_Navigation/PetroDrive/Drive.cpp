#include"Drive.h"

Drive::Drive(PinName leftDrivePin, PinName leftDirectionPin, PinName rightDrivePin, PinName rightDirectionPin):leftDrive(leftDrivePin), rightDrive(rightDrivePin), leftDriveEN(leftDirectionPin), rightDriveEN(rightDirectionPin),CW(0)
{}

void Drive::setDrive(float leftDriveSpeed, float rightDriveSpeed)
{
    if(leftDriveSpeed>0)
    {
        leftDriveEN=CW;
        leftDrive=(leftDriveSpeed>1)?1:leftDriveSpeed;
    }
    else
    {
        leftDriveEN=!CW;
        leftDrive=(leftDriveSpeed<-1)?1:-leftDriveSpeed;
    }
    
    if(rightDriveSpeed>0)
    {
        rightDriveEN=CW;
        rightDrive=(rightDriveSpeed>1)?1:rightDriveSpeed;
    }
    else
    {
        rightDriveEN=!CW;
        rightDrive=(rightDriveSpeed<-1)?1:-rightDriveSpeed;
    }
}