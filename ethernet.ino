#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192 , 168, 1, 1);
EthernetServer server(80);
 
const int pinLed1 = A0;
const int pinLed2 = A3;

File webFile;

String json;

void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for debugging

    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    
    Serial.println("Initializing SD card...");

    if (!SD.begin(4)) {

        Serial.println("ERROR - SD card initialization failed!");

        return;    

    }

    Serial.println("SUCCESS - SD card initialized.");

    if (!SD.exists("PAGINA/INDEX.PHP")) {

        Serial.println("ERROR - Can't find index.php file!");

        return;  
    }

    Serial.println("SUCCESS - Found index.php file.");

    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    
    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        String cadena = "";
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    cadena.concat(c);
                    SD.open("PAGINA/CSS/MATERIALIZE.MIN.CSS");
                    SD.open("PAGINA/JS/MATERIALIZE.MIN.JS");
                    SD.open("PAGINA/JS/JQUERY.JS");
                    SD.open("PAGINA/JS/INDEX.JS");
                    webFile = SD.open("PAGINA/INDEX.PHP");
                    if(webFile) {
                      while(webFile.available()) {
                        client.write(webFile.read());   
                      }
                      webFile.close();
                    }

                    int posicion = cadena.indexOf("led1");
                    String command = cadena.substring(posicion);
             
                      if (command == "led1=ON")
                      {
                        digitalWrite(pinLed1, HIGH);
                      }
                      else if (command == "led1=OFF")
                      {
                        digitalWrite(pinLed1, LOW);
                      }
            
                      posicion = cadena.indexOf("led2");
                      command = cadena.substring(posicion);
                      if (command == "led2=ON")
                      {
                        digitalWrite(pinLed2, HIGH);
                      }
                      else if (command == "led2=OFF")
                      {
                        digitalWrite(pinLed2, HIGH);
                      }
            
                      json = "{";
                      
                      json += "\"analog\": [";
                        for(int i = 0; i < 7; i++) {
                          json += "{";
                            json += "\"p\": ";
                            json += "\"A";
                            json += i;
                            json += "\"";
                          json += ",";
                            json += "\"s\": ";
                            json += analogRead(i);
                          json += "}";
                          if(i != 6) {
                            json += ",";
                          }
                        }
                      json += "],";
            
                      json += "\"digital\": [";
                        for(int i = 0; i < 13; i++) {
                          json += "{";
                            json += "\"p\": ";
                            json += "\"D";
                            json += i;
                            json += "\"";
                          json += ",";
                            json += "\"s\": ";
                            json += digitalRead(i);
                          json += "}";
                          if(i != 12) {
                            json += ",";
                          }
                        }
                      json += "]";
                      
                      json += "}";
                      client.println(json);
                      Serial.println(json);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1000);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}
