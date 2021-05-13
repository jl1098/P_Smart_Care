//PROYECTO SMART CARE

#include<ESP8266WiFi.h>
#include<DNSServer.h>
#include<ESP8266WebServer.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include "FirebaseESP8266.h"

// Credenciales Proyecto Firebase
const char *FIREBASE_HOST = "https://smartcare-decac-default-rtdb.firebaseio.com/";
const char *FIREBASE_AUTH = "qgxDLAwRKmM8xCm2SH7xsErG8XYyIfDF6QsiAQlH";
// Firebase Data object in the global scope
FirebaseData firebaseData;

//Variables
//NODOS BASE DE DATOS
String parentPath = "/D1"; //Dispositivo #1
String childPath[2] = {"/HR", "/SpO2"}; //Pulso cardiado, Oxigenación
size_t childPathSize = 2;
//Varibales medición.
int HR = 0;
int SpO2 = 0;


void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFiManager wifiManager;

  //Resetear configuración.
  //wifiManager.resetSettings();

  //wifiManager.autoConnect("NOMBRE","Contraseña"); //Conectar Wi-Fi automaticamente 
  wifiManager.autoConnect("D1"); 

  if(!wifiManager.autoConnect("D1")){
    Serial.println("Fallo en la conexión");
    ESP.reset();
    delay(1000);
  }
  Serial.println("Conectado");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void loop() {
String nodo = "D1";

    //LEER DATOS
    Firebase.getInt(firebaseData, nodo + "/HR", HR);
    Firebase.getInt(firebaseData, nodo + "/SpO2", SpO2");

    //Escribir datos
    Firebase.setInt(firebaseData, nodo + "/HR", HR);
    Firebase.setInt(firebaseData, nodo + "/SpO2", SpO2");


}
