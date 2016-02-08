  //################# LIBRARIES ################
  #include <SPI.h>
  #include <WiFi.h>
 
  char ssid[] = "yourNetwork"; //  your network SSID (name) 
  char pass[] = "secretPassword";    // your network password (use for WPA, or use as key for WEP)
  
  // Cloud data
  #define SERVER         "test.ttcloud.net"     // replace with your server
  #define PORT           8082                 // replace with your port
    
  //################ FIWARE VARIABLES ################
  char FIWARE_APIKEY[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  char FIWARE_DEVICE[] = "myArduino";
  char FIWARE_SERVER[] = "test.ttcloud.net";
  int FIWARE_PORT = 8082;
  
  //################ SENSOR VARIABLES ################  
  const int numsensors = 2;
  String measures[numsensors][2];
  // Wait 2s between measures
  int MEASURES_PERIOD = 2000;
  
   // initialize the library instance
  WiFiClient client;
  
  void setup() 
  {  
    // Put your setup code here, to run once:
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
    pinMode(6, OUTPUT); 
    
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  }
  
  
  void loop() 
  {
    // read the analog in value and map it to the range of the analog out:
    readSensors();
    postMeasures();
    
    delay(MEASURES_PERIOD);
  }
   
 

  
  void readSensors()
  {
    
    //Connect Sensor on Analogic PIN A0
    int sensor1 = analogRead(0);
    measures[0][0] = "s1";
    measures[0][1] = String(sensor1);

    //Connect Sensor on Analogic PIN A1
    int sensor2 = analogRead(1);
    measures[1][0] = "s2";
    measures[1][1] = String(sensor2);
  }
  
  
  void postMeasures()
  {
    Serial.println("\nStarting connection to server...");
    
    String body;
    
    // If you get a connection, report back via serial:
    if (client.connect(FIWARE_SERVER, FIWARE_PORT)) {
      Serial.println("connected to server");
      for (int i = 0; i < numsensors; i++){ 
        body= body + String(measures[i][0])+"|"+String(measures[i][1]);
        if (i!=numsensors-1){
            body = body +"#";
        }     
      }
      
    // Make a HTTP request:
    client.println("POST /iot/d?i="+String(FIWARE_DEVICE)+"&k="+String(FIWARE_APIKEY)+"&getCmd=1 HTTP/1.1");    
    client.println("Host:"+String(FIWARE_SERVER)+":"+String(FIWARE_PORT));
    client.println("Content-Length: "+String(body.length()));
    client.println("Connection: close");
    client.println();
    client.println(body);
    Serial.println(body);

    // Parse chain of commands 
    String command="";
    bool command_part= false; 
    while (client.available()){
      char c = client.read();
      if (c == '#'){         
         command_part = false;
      }  
      if (command_part == true){  
        command +=  c ; 
      }
      if (c == '@'){
        command_part = true;
      }
    }

    String aux="";
    
    for (int x = 0 ; x< command.length(); x++){ 
        
        aux = aux + command[x];
        
        if (aux == "ledr|on"){
          digitalWrite(6, HIGH);   
          delay(500);
          //Serial.println(command);
          command=command.substring(7,command.length());
          Serial.println(command.length());
          aux="";
          Serial.println(command);
          x = 0;
          sendAck();
          delay(1000);
        }
        
        if (aux == "ledr|off"){
          digitalWrite(6, LOW);   
          delay(500);
          Serial.println(command);
          command=command.substring(8,command.length());
          aux="";
          Serial.println(command);
          x = 0;
          sendAck();
          delay(1000);  
        }
    }
    
    gsmClient.stop();
    
    }
  }
  
  // Not execute old commands again
  void sendAck(){
    String ack_payload= "";
    ack_payload= String(FIWARE_DEVICE)+"@ledr|OK";
    client.println("POST /iot/d?i="+String(FIWARE_DEVICE)+"&k="+String(FIWARE_APIKEY)+" HTTP/1.1");    
    client.println("Host:"+String(FIWARE_SERVER)+":"+String(FIWARE_PORT));
    client.println("Content-Length: "+String(ack_payload.length()));
    client.println("Connection: close");
    client.println();
    client.println(ack_payload);    
  }

