#include"WiiIRCamera.h"
#include"Drive.h"

#define IR_DIST_cm 3.175
#define DISTANCE_DESIRED 50
#define AXIS_DESIRED 512
#define DESIRED_Y_AXIS 768/2
#define MOTOR_SENSITIVITY_FACTOR 0.5
#define MAX_DISTANCE_DETECTABLE 120

#define SERVO_START  2.25/20.0
#define SERVO_END  0.65/20.0
#define SERVO_MID (SERVO_START + SERVO_END)/2

Serial pc(USBTX, USBRX);
DigitalOut myled2(LED2);
PwmOut servo(p24);

WiiIRCamera cam(0xB0,p28, p27);
Drive petroDrive(p21,p13,p22,p10);

typedef struct
{
    float leftDriveSpeed;
    float rightDriveSpeed;
}DriveSpeed;

typedef struct
{
    float currentDistance;
    int currentXCoordinate;
    bool valid;
}Orientation;

Orientation getOrientation(const int (&blobs)[12])
{
    const float tan22_5=0.414;
    Orientation currentOrientation;
    float eucl_dist, cm_per_pixel;
    eucl_dist=sqrt((float)(((blobs[3]-blobs[0])*(blobs[3]-blobs[0]))+((blobs[4]-blobs[1])*(blobs[4]-blobs[1]))));
    if(eucl_dist==0||(blobs[0]==1023)||(blobs[1]==1023)||(blobs[3]==1023)||(blobs[4]==1023))
    {
        myled2=1;
        currentOrientation.valid=0;
        return currentOrientation;
    }
    else
    {
        currentOrientation.valid=1;
        myled2=0;
    }
    cm_per_pixel=IR_DIST_cm/eucl_dist;
    currentOrientation.currentDistance=(1024*cm_per_pixel)/(2*tan22_5);
    currentOrientation.currentXCoordinate=blobs[0]+(blobs[3]-blobs[0]);
    return currentOrientation;
}

DriveSpeed getDriveparameters(Orientation currentOrientation)
{
    DriveSpeed drive;
    float directionoffset=0, speed;
    speed=(currentOrientation.currentDistance - DISTANCE_DESIRED)/(float)(MAX_DISTANCE_DETECTABLE*MOTOR_SENSITIVITY_FACTOR);
    speed=(speed>1)?1:speed;
    speed=(speed<-1)?-1:speed;
    directionoffset=(currentOrientation.currentXCoordinate - AXIS_DESIRED)/(float)AXIS_DESIRED;
    directionoffset=(directionoffset>1)?1:directionoffset;
    directionoffset=(directionoffset<-1)?-1:directionoffset;
    pc.printf("Speed:%f\n\r",speed);
    pc.printf("DirectionOffset:%f\n\r",directionoffset);
    drive.leftDriveSpeed=(speed - directionoffset)/(float)2;
    drive.rightDriveSpeed=(speed + directionoffset)/(float)2;
    //drive.leftDriveSpeed=(speed - directionoffset);
    //drive.rightDriveSpeed=(speed + directionoffset);
    return drive;
}

void updateCameraOrientation(const int (&blobs)[12])
{
    float midY, yout, servoDrive;
    midY=blobs[1]+(blobs[4]-blobs[1]);
    yout=((midY - DESIRED_Y_AXIS)/(float)DESIRED_Y_AXIS)*SERVO_MID;
    servoDrive=(SERVO_MID + yout);
    servo=servoDrive;
}

int main()
{
    int IRBlobs[12]={0};
    DriveSpeed driveParameters;
    Orientation currentOrientation;
    pc.baud(115200);
    servo.period_ms(20);
    
    printf("Hello\n\r");
    while(1)
    {
        cam.read(IRBlobs);
        currentOrientation=getOrientation(IRBlobs);
        if(!currentOrientation.valid)
        {
            petroDrive.setDrive(0, 0);
            continue;
        }
        pc.printf("%d,%d,%d,%d\n\r", IRBlobs[0], IRBlobs[1], IRBlobs[3], IRBlobs[4]);
        pc.printf("Actual Distance:%f\tActual Y:%d\n\r",currentOrientation.currentDistance, currentOrientation.currentXCoordinate);    
        driveParameters=getDriveparameters(currentOrientation);
        petroDrive.setDrive(driveParameters.leftDriveSpeed, driveParameters.rightDriveSpeed);
        pc.printf("%d,%d,%d,%d\n\r", IRBlobs[0], IRBlobs[1], IRBlobs[3], IRBlobs[4]);         
        pc.printf("Actual Distance:%f\tLeftSpeed:%f\tRightSpeed:%f\n\r",currentOrientation.currentDistance,driveParameters.leftDriveSpeed,driveParameters.rightDriveSpeed);
        //updateCameraOrientation(IRBlobs);
        wait(0.050);
    }    
}