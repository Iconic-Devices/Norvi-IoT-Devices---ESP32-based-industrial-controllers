#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "" // Put your WifiSSID here
#define PASSWORD "" // Put your wifi password here
#define TOKEN "" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
//it should be a random and unique ascii string and different from all other devices


#define VARIABLE_LABEL1 "input1"// Assing the variable label
#define VARIABLE_LABEL2 "input2"
#define VARIABLE_LABEL3 "input3"
#define VARIABLE_LABEL4 "input4"
#define VARIABLE_LABEL5 "input5"
#define VARIABLE_LABEL6 "input6"
#define VARIABLE_LABEL7 "input7"
#define VARIABLE_LABEL8 "input8"

#define DEVICE_LABEL "esp32" // Assig the device label
#define INPUT1 18
#define INPUT2 39
#define INPUT3 34
#define INPUT4 35
#define INPUT5 19
#define INPUT6 21
#define INPUT7 22
#define INPUT8 23

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_sensor1[10];
char str_sensor2[10];
char str_sensor3[10];
char str_sensor4[10];
char str_sensor5[10];
char str_sensor6[10];
char str_sensor7[10];
char str_sensor8[10];
/****************************************
   Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.write(payload, length);
  Serial.println();
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as OUTPUT
  pinMode(INPUT1, INPUT);
  pinMode(INPUT2, INPUT);
  pinMode(INPUT3, INPUT);
  pinMode(INPUT4, INPUT);
  pinMode(INPUT5, INPUT);
  pinMode(INPUT6, INPUT);
  pinMode(INPUT7, INPUT);
  pinMode(INPUT8, INPUT);
  Serial.println();
  Serial.print("Wait for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
}

void loop() {

  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("wifi disconnected\n");
  
    WiFi.begin(WIFISSID, PASSWORD);
  }
  
  if (!client.connected()) {
    reconnect();

  }
  float sensor1 = (!digitalRead(INPUT1));
  float sensor2 = (!digitalRead(INPUT2));
  float sensor3 = (!digitalRead(INPUT3));
  float sensor4 = (!digitalRead(INPUT4));
  float sensor5 = (!digitalRead(INPUT5));
  float sensor6 = (!digitalRead(INPUT6));
  float sensor7 = (!digitalRead(INPUT7));
  float sensor8 = (!digitalRead(INPUT8));

   
  dtostrf(sensor1, 4, 2, str_sensor1);
  dtostrf(sensor2, 4, 2, str_sensor2);
  dtostrf(sensor3, 4, 2, str_sensor3);
  dtostrf(sensor4, 4, 2, str_sensor4);
  dtostrf(sensor5, 4, 2, str_sensor5);
  dtostrf(sensor6, 4, 2, str_sensor6);
  dtostrf(sensor7, 4, 2, str_sensor7);
  dtostrf(sensor8, 4, 2, str_sensor8);

  
  sprintf(topic, "%s%s", "/v1.6/devices/",DEVICE_LABEL);
  
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":%s,",VARIABLE_LABEL1,str_sensor1 );
  sprintf(payload, "%s \"%s\":%s,", payload,VARIABLE_LABEL2, str_sensor2); // Adds the variable label
  sprintf(payload, "%s \"%s\":%s}", payload, VARIABLE_LABEL3, str_sensor3); 
  client.publish(topic, payload);
  
  sprintf(payload, "{\"%s\":%s,",VARIABLE_LABEL4,str_sensor4 );
  sprintf(payload, "%s \"%s\":%s,", payload,VARIABLE_LABEL5, str_sensor5); // Adds the variable label
  sprintf(payload, "%s \"%s\":%s}", payload, VARIABLE_LABEL6, str_sensor6); 
  client.publish(topic, payload);
  
  sprintf(payload, "{\"%s\":%s,",VARIABLE_LABEL7,str_sensor7 );
  sprintf(payload, "%s \"%s\":%s}", payload,VARIABLE_LABEL8, str_sensor8);
  client.publish(topic, payload);
  


  Serial.println("\nPublishing data to Ubidots Cloud");
  Serial.print("Value of Sensor1 is:- ");   Serial.println(sensor1);
  Serial.print("\nValue of Sensor2 is:- "); Serial.println(sensor2);
  Serial.print("\nValue of Sensor3 is:- "); Serial.println(sensor3);
  Serial.print("\nValue of Sensor4 is:- "); Serial.println(sensor4);
  Serial.print("\nValue of Sensor5 is:- "); Serial.println(sensor5);
  Serial.print("\nValue of Sensor6 is:- "); Serial.println(sensor6);
  Serial.print("\nValue of Sensor7 is:- "); Serial.println(sensor7);
  Serial.print("\nValue of Sensor8 is:- "); Serial.println(sensor8);
  
  Serial.println("\nPublishing data to Ubidots Cloud");

  client.loop();
  delay(1000);
}
