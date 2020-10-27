#include <PS2X_lib.h>  //for v1.6

/******************************************************************
* establecer pines conectados al controlador PS2:
 * - 1e columna: original
 * - 2e colmun: ¿Stef?
 * reemplace los números de pin por los que usa
 ******************************************************************/
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

/******************************************************************
* seleccionar modos del controlador PS2:
 * - presiones = lectura analógica de pulsadores
 * - estruendo = estruendo del motor
 * descomente 1 de las líneas para cada selección de modo
 ******************************************************************/
// # definir presiones true
#define pressures   false
//#definir rumble      true
#define rumble      false

PS2X ps2x; // crear PS2 clase controladora

// en este momento, la biblioteca NO admite controladores conectables en caliente, lo que significa
// siempre debes reiniciar tu Arduino después de conectar el controlador,
// o llama a config_gamepad (pins) nuevamente después de conectar el controlador.


int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
 
  Serial.begin(57600);
  
  delay(300);  // retardo añadido para dar tiempo al módulo ps2 inalámbrico antes de configurarlo
   
  // ¡¡¡CAMBIOS para v1.6 AQUÍ !!! **************PRESTA ATENCIÓN*************
  
  // configurar pines y configuraciones: GamePad (reloj, comando, atención, datos, presiones ?, ¿retumbar?) verifica si hay error


  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop() {
  /* Debe leer Gamepad para obtener nuevos valores y establecer valores de vibración
     ps2x.read_gamepad (motor pequeño encendido / apagado, fuerza del motor más grande de 0-255)
     si no habilita el ruido, use ps2x.read_gamepad (); sin valores
     Deberías llamar a esto al menos una vez por segundo
   */ 
  if(error == 1) //skip loop if no controller found
    return; 
  
  if(type == 2){ //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller 
   
    if(ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if(ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if(ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if(ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if(ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed"); 

    if(ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          // será TRUE siempre que se presione el botón
      Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");
 
    if(ps2x.Button(PSB_START))         // será TRUE siempre que se presione el botón
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
    
    if(ps2x.Button(ORANGE_FRET)) {     // imprime el valor de la barra SI ES VERDADERO
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
  }
  else { // Controlador DualShock
    ps2x.read_gamepad(false, vibrate); // leer el controlador y configurar el motor grande para que gire a la velocidad de 'vibración'
    
    if(ps2x.Button(PSB_START))         // será TRUE siempre que se presione el botón
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) {      // será TRUE siempre que se presione el botón
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

    vibrate = ps2x.Analog(PSAB_CROSS);  // esto establecerá la velocidad de vibración del motor grande en función de la fuerza con la que presione el botón azul (X)
    if (ps2x.NewButtonState()) {        // será VERDADERO si cualquier botón cambia de estado (de encendido a apagado o de apagado a encendido)
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");        
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE))               // será VERDADERO si el botón SOLO se presionó
      Serial.println("Circle just pressed");
    if(ps2x.NewButtonState(PSB_CROSS))               // será VERDADERO si el botón SOLO se presionó O se soltó
      Serial.println("X just changed");
    if(ps2x.ButtonReleased(PSB_SQUARE))              // será VERDADERO si el botón SOLO se soltó
      Serial.println("Square just released");     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { // Imprimir valores de barra si cualquiera es VERDADERA
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); // Joystick izquierdo, eje Y. Otras opciones: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }     
  }
  delay(50);  
}