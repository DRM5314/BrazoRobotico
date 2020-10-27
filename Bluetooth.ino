#include <Servo.h>  // agrega las bibliotecas de servo
Servo myservo1;  // crea un objeto servo para controlar un servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=80, pos2=60, pos3=130, pos4=0;  // definir la variable de 4 servo ángulo y asignar el valor inicial (que es el valor del ángulo de postura de arranque)
char val;

void setup()
{
   // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  Serial.begin(9600); // establece la velocidad en baudios en 9600
}

void loop() 
{
  myservo1.attach(A1);  // establece el pin de control del servo 1 en A1
  myservo2.attach(A0);  // establece el pin de control del servo 2 en A0
  myservo3.attach(6);   // establece el pin de control del servo 3 en D6
  myservo4.attach(9);   // establece el pin de control del servo 4 en D9

  if(Serial.available())   // if receive the data
  {
    val=Serial.read();    // read the received data
    Serial.println(val);
   
    switch(val)   
    {
      case 'B':  T_left();  break;    // ejecuta la función correspondiente cuando recibe el valor
      case 'C':  T_right();  break;
      case 'A':  RF();  break;
      case 'D':  RB();  break;
      case '2':  ZK();  break;
      case '3':  ZB();  break;
      case '1':  LF();  break;
      case '4':  LB();  break;
    }
  }
}
//**************************************************
// girar a la izquierda
void T_left()
{
    pos1=pos1+1;
    myservo1.write(pos1);
    delay(5);
    if(pos1>180)
    {
      pos1=180;
    }
}
//girar a la derechavoid T_right()
{
    pos1=pos1-1;
    myservo1.write(pos1);
    delay(5);
    if(pos1<1)
    {
      pos1=1;
    }
}
//********************************************
//abre garra
void ZK()
{
      pos4=pos4-2;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4<2)
      {
        pos4=0;
      }
}
// cierra garra
void ZB()
{
    pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4>108)
      {
        pos4=108;
      }
}

//******************************************
// la parte superior del brazo se levantará
void RF()
{
    pos2=pos2-1;
    myservo2.write(pos2);
    delay(5);
    if(pos2<0)
    {
      pos2=0;
    }
}
// la parte superior del brazo bajará
void RB()
{
    pos2=pos2+1;
    myservo2.write(pos2);
    delay(5);
    if(pos2>180)
    {
      pos2=180;
    }
}

//***************************************
// el antebrazo se estirarávoid LB()
{
  pos3=pos3+1;
    myservo3.write(pos3);
    delay(5);
    if(pos3>180)
    {
      pos3=180;
    }
}
// el antebrazo retrocederá
void LF()
{
  pos3=pos3-1;
    myservo3.write(pos3);
    delay(5);
    if(pos3<35)
    {
      pos3=35;
    }
}