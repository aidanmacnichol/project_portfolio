#include<Servo.h>
Servo x, y, fire;
int width = 640;
int height = 480;
int xpos = 1500;
int xposprev = 1500;
int ypos = 1500;
int yposprev = 1500;
int firepos = 54; //54 minimum 150 max

boolean change = false;
unsigned long timer = 0;

void setup() {
    Serial.begin(9600);
    x.attach(9);
    y.attach(10);
    fire.attach(8);
    x.writeMicroseconds(xpos);
    y.writeMicroseconds(ypos);
    fire.write(firepos);
}


//to get finer control convert servo.write to
//servo.writeMicrosecond() to use decimals
//these values are between 1000 and 2000 (1500)
//is the center

const int angle = 3;

void loop() {
    //for reading data from the serial input
    if(Serial.available() > 0){
        int x_mid, y_mid;
        if(Serial.read() == 'X'){
            x_mid = Serial.parseInt();
                if(Serial.read() =='Y')
                    y_mid = Serial.parseInt();
 }

 xposprev = xpos;
 yposprev = ypos;
 //adjust the servos if the centroid
 //is not within the box
if(x_mid > width / 2 + 20){
    xpos -= angle;
}
if(x_mid < width / 2 - 20){
    xpos += angle;
}
if(y_mid < height / 2 + 20){
    ypos -= angle;
}
if(y_mid > height / 2 - 20){
    ypos += angle;
}

 //so the servos dont move past their
 //maximum values
if (xpos >= 2000)
    xpos = 2000;
else if (xpos <= 1000)
    xpos = 1000;
if (ypos >= 2000)
    ypos = 2000;
else if (ypos <= 1000)
    ypos = 1000;

if(ypos == yposprev && xpos == xposprev){
    change = false;
} else {
    change = true;
}


if(change == false){
    if(millis() - timer >= 1000){
        firepos = 150;
}
} else{
timer = millis();
firepos = 54;
}

//move the servos!
x.writeMicroseconds(xpos);
y.writeMicroseconds(ypos);
fire.write(firepos);

 }
}
