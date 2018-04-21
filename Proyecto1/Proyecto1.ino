 #include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int vent = 8;
String messaje="";

//Hasta aquí hemos declarado la librería para la LCD y los pines por donde le va a entrar la información.

float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:

  int dato;
  float c;
  dato=analogRead(A0);
  
  c = (500.0 * dato)/1023;

  //Esta fórmula sale de la relación del sensor con los grados. Ésta es fácilmente rastreable por la web pero vamos a intentar explicarla un poco: El sensor de temperatura LM35 responde a variaciones de 10 mV por cada grado centígrado. Si el sensor detecta 1 grado centígrado a la salida del sensor obtendríamos 10 mV. Ejemplo: 26,4ºC = 264 mV = 0.264 V.
//Tenemos que el convertidor de analógico a digital es de 10 bits de resolución, los valores variarán entre 0 y 1023, entonces Vout= (5V*Dato)/1023 siendo  ( 0 < Dato < 1023 ) y para ajustar la escala a grados centígrados: Vout = ((5V*Dato)*100)/1023
  return (c);
}

float kelvin(float cent)
{
  float k;
  k=cent+273.15;
  return(k);
  
}

float fahren(float cent)
{
  float f;
  f=cent*1.8+32;
  return (f);
  

}

float rankin(float cent)
{
  float r;
  r=(cent + 273.15)*1.8;
  return (r);
}

//Hasta aquí hemos declarado las funciones de conversión del dato analógico de entrada del sensor en grados celsius en sus respectivas equivalencias.

void setup() {
  // Definimos la LCD con dimension 2x16 y definimos los caracteres que deben salir en las filas:
  lcd.begin(16,2);
  lcd.print("C=      ");
  lcd.setCursor(0,1);
  //lcd.print("Temperatura");
  pinMode(9, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  delay(1000);
  pinMode(vent, OUTPUT);
  digitalWrite(vent, LOW);
  Serial.begin(9600);
}

//Hasta aquí hemos definido qué queremos que salga impreso por la pantalla y el tamaño de ésta.
void loop() {
  int caracters = 0;
  // put your main code here, to run repeatedly: 
  float Centigrados = centi();
  float Fahrenheit = fahren (Centigrados);
  float Rankin = rankin (Centigrados);
  float Kelvin = kelvin (Centigrados);
  
  lcd.setCursor(2,0);
  lcd.print(Centigrados);
  
 // lcd.setCursor(10,0);
 // lcd.print(Kelvin);

  if(Centigrados > 27){
    beep(200);
    digitalWrite(vent, HIGH);
  }else{
    digitalWrite(vent, LOW);
  }

if(Serial.available() > 0){
      messaje="";
      while (Serial.available()>0)
      {       
          messaje=messaje+Decimal_to_ASCII(Serial.read()); 
      }  
    }

  caracters = messaje.length(); 
  
  if (messaje!="")
  {
    lcd.setCursor(0,0);
    lcd.print("Clima C=");
    lcd.setCursor(10,0);
    lcd.print(Centigrados); 
    lcd.setCursor(0,1);
    lcd.print(messaje);
  }

  for (int i = 0; i < messaje.length(); i++) 
  {
    lcd.scrollDisplayLeft();
    delay(250);
  }
  for (int i = 0; i < messaje.length(); i++) 
  {
    lcd.scrollDisplayRight();
    delay(250);
  }
  delay(1000);
}

void beep(unsigned char pausa){
            analogWrite(9, 20);
            delay(pausa);                 // Espera
            analogWrite(9, 0);            // Apaga
            delay(pausa);                 // Espera
}

char Decimal_to_ASCII(int entrada){
  char salida=' ';
  switch(entrada){
  case 32: 
  salida=' '; 
  break; 
  case 33: 
  salida='!'; 
  break; 
  case 34: 
  salida='"'; 
  break; 
  case 35: 
  salida='#'; 
  break; 
  case 36: 
  salida='$'; 
  break; 
  case 37: 
  salida='%'; 
  break; 
  case 38: 
  salida='&'; 
  break; 
  case 39: 
  salida=' '; 
  break; 
  case 40: 
  salida='('; 
  break; 
  case 41: 
  salida=')'; 
  break; 
  case 42: 
  salida='*'; 
  break; 
  case 43: 
  salida='+'; 
  break; 
  case 44: 
  salida=','; 
  break; 
  case 45: 
  salida='-'; 
  break; 
  case 46: 
  salida='.'; 
  break; 
  case 47: 
  salida='/'; 
  break; 
  case 48: 
  salida='0'; 
  break; 
  case 49: 
  salida='1'; 
  break; 
  case 50: 
  salida='2'; 
  break; 
  case 51: 
  salida='3'; 
  break; 
  case 52: 
  salida='4'; 
  break; 
  case 53: 
  salida='5'; 
  break; 
  case 54: 
  salida='6'; 
  break; 
  case 55: 
  salida='7'; 
  break; 
  case 56: 
  salida='8'; 
  break; 
  case 57: 
  salida='9'; 
  break; 
  case 58: 
  salida=':'; 
  break; 
  case 59: 
  salida=';'; 
  break; 
  case 60: 
  salida='<'; 
  break; 
  case 61: 
  salida='='; 
  break; 
  case 62: 
  salida='>'; 
  break; 
  case 63: 
  salida='?'; 
  break; 
  case 64: 
  salida='@'; 
  break; 
  case 65: 
  salida='A'; 
  break; 
  case 66: 
  salida='B'; 
  break; 
  case 67: 
  salida='C'; 
  break; 
  case 68: 
  salida='D'; 
  break; 
  case 69: 
  salida='E'; 
  break; 
  case 70: 
  salida='F'; 
  break; 
  case 71: 
  salida='G'; 
  break; 
  case 72: 
  salida='H'; 
  break; 
  case 73: 
  salida='I'; 
  break; 
  case 74: 
  salida='J'; 
  break; 
  case 75: 
  salida='K'; 
  break; 
  case 76: 
  salida='L'; 
  break; 
  case 77: 
  salida='M'; 
  break; 
  case 78: 
  salida='N'; 
  break; 
  case 79: 
  salida='O'; 
  break; 
  case 80: 
  salida='P'; 
  break; 
  case 81: 
  salida='Q'; 
  break; 
  case 82: 
  salida='R'; 
  break; 
  case 83: 
  salida='S'; 
  break; 
  case 84: 
  salida='T'; 
  break; 
  case 85: 
  salida='U'; 
  break; 
  case 86: 
  salida='V'; 
  break; 
  case 87: 
  salida='W'; 
  break; 
  case 88: 
  salida='X'; 
  break; 
  case 89: 
  salida='Y'; 
  break; 
  case 90: 
  salida='Z'; 
  break; 
  case 91: 
  salida='['; 
  break; 
  case 92: 
  salida=' '; 
  break; 
  case 93: 
  salida=']'; 
  break; 
  case 94: 
  salida='^'; 
  break; 
  case 95: 
  salida='_'; 
  break; 
  case 96: 
  salida='`'; 
  break; 
  case 97: 
  salida='a'; 
  break; 
  case 98: 
  salida='b'; 
  break; 
  case 99: 
  salida='c'; 
  break; 
  case 100: 
  salida='d'; 
  break; 
  case 101: 
  salida='e'; 
  break; 
  case 102: 
  salida='f'; 
  break; 
  case 103: 
  salida='g'; 
  break; 
  case 104: 
  salida='h'; 
  break; 
  case 105: 
  salida='i'; 
  break; 
  case 106: 
  salida='j'; 
  break; 
  case 107: 
  salida='k'; 
  break; 
  case 108: 
  salida='l'; 
  break; 
  case 109: 
  salida='m'; 
  break; 
  case 110: 
  salida='n'; 
  break; 
  case 111: 
  salida='o'; 
  break; 
  case 112: 
  salida='p'; 
  break; 
  case 113: 
  salida='q'; 
  break; 
  case 114: 
  salida='r'; 
  break; 
  case 115: 
  salida='s'; 
  break; 
  case 116: 
  salida='t'; 
  break; 
  case 117: 
  salida='u'; 
  break; 
  case 118: 
  salida='v'; 
  break; 
  case 119: 
  salida='w'; 
  break; 
  case 120: 
  salida='x'; 
  break; 
  case 121: 
  salida='y'; 
  break; 
  case 122: 
  salida='z'; 
  break; 
  case 123: 
  salida='{'; 
  break; 
  case 124: 
  salida='|'; 
  break; 
  case 125: 
  salida='}'; 
  break; 
  case 126: 
  salida='~'; 
  break; 
  }
  return salida;
 }
