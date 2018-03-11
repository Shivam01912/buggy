/*This code is for the silver level competition of
the subject Engineering Design-3 (UTA011)
for this to work this you need to put two IR sensors
beneath the buggy to sense the black line and
one IR sensor above the buggy to sense the gates in the path.

Initially both the sensors below are to be kept on white
or one of them on black and other on white and is started
behind the first line on parking lane then without
any intervention the buggy will complete one round
anti-clockwise and in the second round it will
enter the parking lane and stop on the third line.
*/

int left_motor_1=5;
int left_motor_2=6;
int right_motor_1=7;
int right_motor_2=8;
float duration;
int gray=400;
int both_black=0;
void setup()
{
    pinMode(left_motor_1,OUTPUT);
    pinMode(left_motor_2,OUTPUT);
    pinMode(right_motor_1,OUTPUT);
    pinMode(right_motor_2,OUTPUT);
    pinMode(A0,INPUT);              //This pin is for left IR sensor
    pinMode(A1,INPUT);              //This pin is for right IR sensor
    pinMode(A2,INPUT);              //This pin is for the IR used for gate sensing
}

void forward(){

    //Code to move the buggy forward

    digitalWrite(left_motor_1,HIGH);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,HIGH);
    delay(5);
    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
    delay(10);
}

void left(){

    //Code to move the buggy left

    digitalWrite(left_motor_1,HIGH);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
    delay(5);
    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
    delay(10);
}

void right(){

    //Code to move the buggy right

    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,HIGH);
    delay(2);
    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
    delay(5);
}

void brake(){

    //Code to stop the buggy

    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
}

float ir_left(){

    //Code to read from left IR sensor

    return analogRead(A0);
}

float ir_right(){

    //Code to read from right IR sensor

    return analogRead(A1);
}

float gate_entry(){

    //Code to read from IR sensor used for gate

    return analogRead(A2);
}

void blacks_bypass(){

    //Code to bypass unnecesarry both blacks conditions

    digitalWrite(left_motor_1,HIGH);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,HIGH);
    delay(100);
    digitalWrite(left_motor_1,LOW);
    digitalWrite(left_motor_2,LOW);
    digitalWrite(right_motor_1,LOW);
    digitalWrite(right_motor_2,LOW);
    delay(50);
}

void gate_bypass(){

    //Code to bypass gate

    left_ir=ir_left();
    right_ir=ir_right();
    gate=gate_entry();
    while(gate>gray){
        if(left_ir>gray&&right_ir>gray){
            forward();
        }
        else if(left_ir<gray&&right_ir>gray){
            left();
        }
        else if(left_ir>gray&&right_ir<gray){
            right();
        }
        left_ir=ir_left();
        right_ir=ir_right();
        gate=gate_entry();
    }
}

void loop()
{
    float left_ir=ir_left();
    float right_ir=ir_right();

    float gate=gate_entry();
    if(gate>gray){

        //Here we sense the gate and react accordingly

        brake();
        delay(1500);
        gate_bypass();
    }

    left_ir=ir_left();
    right_ir=ir_right();

    if(both_black!=9){
        if(left_ir>gray&&right_ir>gray){
            forward();
        }
        else if(left_ir<gray&&right_ir>gray){
            left();
        }
        else if(left_ir>gray&&right_ir<gray){
            right();
        }
        else if(both_black==1&&left_ir<gray&&right_ir<gray){

            //This is for entering into the main lane from parking lane

            both_black++;
            digitalWrite(left_motor_1,HIGH);
            digitalWrite(left_motor_2,LOW);
            digitalWrite(right_motor_1,LOW);
            digitalWrite(right_motor_2,HIGH);
            delay(20);
            digitalWrite(left_motor_1,HIGH);
            digitalWrite(left_motor_2,LOW);
            digitalWrite(right_motor_1,LOW);
            digitalWrite(right_motor_2,LOW);
            delay(800);
        }
        else if(both_black!=5&&both_black!=1&&left_ir<gray&&right_ir<gray){

            //Here we bypass all the useless double bypass conditions

            both_black++;
            blacks_bypass();
        }
        else if(both_black==5&&left_ir<gray&&right_ir<gray){

            //This is for entering into the parking lane from main lane

            both_black++;
            digitalWrite(left_motor_1,HIGH);
            digitalWrite(left_motor_2,LOW);
            digitalWrite(right_motor_1,LOW);
            digitalWrite(right_motor_2,LOW);
            delay(700);
        }
    }
    else{
        brake();
    }
}
