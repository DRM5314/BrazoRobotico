#include <Servo.h> // Agregamos las librerías servo
Servo servo1; // Creamos los objetos servo para controlar un servo
Servo servo2;
Servo servo3;
Servo servo4;
int pos1=80, pos2=60, pos3=130, pos4=0; // Definimos posiciones (en grados) por defecto
const int derecha_X = A2; // Definimos para usar el pin A2
const int derecha_Y = A5; // Definimos para usar el pin A5
const int derecha_clave = 7; // Definimos un valor bandera en el pin 7?El cual es el valor de Z?
const int izquierda_X = A3; // Definimos para usar el pin A3
const int izquierda_Y = A4; // Definimos para usar el pin A4
const int izquierda_clave = 8; // Definimos un valor bandera en el pin 8?El cual es el valor de Z?
int x1,y1,z1; // Definimos las variables para guardar la informacion del Joystick
int x2,y2,z2;

//configuraciones
void setup()
{
// Inicializamos nuestros motores en las posiciones predefinidas
servo1.write(pos1);
delay(1000);
servo2.write(pos2);
servo3.write(pos3);
servo4.write(pos4);
delay(1500);
pinMode(derecha_clave, INPUT); // Configuramos las teclas derecha e izquierda como entradas
pinMode(izquierda_clave, INPUT);
Serial.begin(9600); // Configuramos los baudios en 9600
}

//funcionamiento
void loop()
{
servo1.attach(A1); // Colocamos el pin de control del servo 1 en A1
servo2.attach(A0); // Colocamos el pin de control del servo 2 en A0
servo3.attach(6); //Colocamos el pin de control del servo 3 en el pin 6
servo4.attach(9); // Colocamos el pin de control del servo 1 en el pin 9
x1 = analogRead(derecha_X); // Leemos el valor en X del Joystick 1
y1 = analogRead(derecha_Y); // Leemos el valor en Y del Joystick 1
z1 = digitalRead(derecha_clave); // Leemos el valor en Z del Joystick 1
x2 = analogRead(izquierda_X); // Leemos el valor en X del Joystick 2
y2 = analogRead(izquierda_Y); // Leemos el valor en Y del Joystick 2
z2 = digitalRead(izquierda_clave); // Leemos el valor en Z del Joystick 2
//delay(5); //Este delay lo podemos dejar o no. Es para asegurarnos que se lean los valores correctamente
// Metodo para controlar la garra
garra();
// Metodo para girar el brazo completo
girar();
// Metodo para subir el brazo
brazoSuperior();
// Metodo para bajar el brazo
brazoInferior();
}

//funcion garra
void garra()
{
if(x2<50) // Si movemos el Joystick izquierdo hacia la derecha
    {
        pos4=pos4-2; //el ángulo actual del servo 4 resta 2 ?cambia el valor que restas, así cambia la velocidad de cierre de la garra?
        //Serial.println(pos4);
        servo4.write(pos4); // El servo 4 opera la accion, la garra se cierra gradualmente.
        delay(5);
    if(pos4<2) // si el valor de pos4 es menor a 2, la garra en 37 grados que hemos probado está cerrado.
        { //?debería cambiar el valor basado en el hecho?
            pos4=2; // Detenemos la resta cuando reduce a 2
        }
    }
if(x2>1000) // Si movemos el Joystick izquierdo hacia la izquierda
    {
    pos4=pos4+8; // El angulo actual del servo4 mas 8?Dependiendo lo que sumamos es la velocidad?
    //Serial.println(pos4);
    servo4.write(pos4); // El servo 4 realiza el movimiento y la garra se abre gradualmente.
    delay(5);
    if(pos4>108) // Aqui declaramos el limite de angulo de apertura de la garra abierta
         {
            pos4=108;
         }
    }
}

//******************************************************
// Metodo para Girar
void girar()
{
if(x1<50) // Si presionamos el Joystick derecho hacia la derecha
    {
    pos1=pos1-1; //La pos1 disminuye en 1
    servo1.write(pos1); // El servo realiza la accion y se el brazo se mueve hacia la derecha
    delay(5);
    if(pos1<1) // El limite del angulo al girarlo a la derecha
        {
        pos1=1;
        }
}
if(x1>1000) // Si movemos el Joystick derecho hacia la izquierda
    {
    pos1=pos1+1; //A la posicion 1 le vamos sumando 1 grado.
    servo1.write(pos1); // El brazo se mueve hacia la izquierda
    delay(5);
    if(pos1>180) // Aqui determinamos el límite del angulo al mover el brazo hacia la izquierda
        {
        pos1=180;
        }
}
}

//**********************************************************/
//Brazo superior
void brazoSuperior()
{
if(y1>1000) // Si movemos el Joystick derecho hacia arriba
    {
    pos2=pos2-1;
    servo2.write(pos2); // El brazo comieza a suibr
    delay(5);
    if(pos2<0) // Delimitamos el angulo al subir
        {
        pos2=0;
        }
}
if(y1<50) // Si presionamos el Joystick derecho hacia abajo
{
    pos2=pos2+1;
    servo2.write(pos2); // El brazo comenzara a ir hacia abajo
    delay(5);
    if(pos2>180) // Delimitamos hasta donde se puede bajar el brazo
        {
        pos2=180;
        }
    }
}
//*************************************************************/

// Brazo inferior
void brazoInferior()
{
if(y2<50) // Si movemos el Joystick izquierdo hacia arriba
    {
    pos3=pos3+1;
    servo3.write(pos3); // El brazo inferior comenzara a estirarse
    delay(5);
    if(pos3>180) // Delimitamos el angulo de estiramiento
        {
        pos3=180;
        }
    }
if(y2>1000) // Si presionamos el joystick izquierdo hacia abajo
    {
    pos3=pos3-1;
    servo3.write(pos3); // El brazo inferior comenzara a retroceder
    delay(5);
    if(pos3<35) // Delimitamos el angulo de retroceso
        {
        pos3=35;
        }
    }
}
