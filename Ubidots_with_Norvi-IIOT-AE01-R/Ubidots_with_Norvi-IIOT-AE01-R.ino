#include <WiFi.h>
#include <PubSubClient.h>


#define WIFISSID "" // Put your WifiSSID here
#define PASSWORD "" // Put your wifi password here
#define TOKEN "" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

#define VARIABLE_LABEL_SUBSCRIBE1 "relay1" 
#define VARIABLE_LABEL_SUBSCRIBE2 "relay2" 
#define VARIABLE_LABEL_SUBSCRIBE3 "relay3"
#define VARIABLE_LABEL_SUBSCRIBE4 "relay4"
#define VARIABLE_LABEL_SUBSCRIBE5 "relay5"
#define VARIABLE_LABEL_SUBSCRIBE6 "relay6"

#define DEVICE_LABEL "esp32" // 

#define RELAY1 14
#define RELAY2 12
#define RELAY3 13
#define RELAY4 15
#define RELAY5 2
#define RELAY6 33

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];




WiFiClient ubidots;
PubSubClient client(ubidots);


void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if (strcmp(topic,"/v1.6/devices/esp32/relay1/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY1, HIGH);
    } else {
        digitalWrite(RELAY1, LOW);
    }
  }
   if (strcmp(topic,"/v1.6/devices/esp32/relay2/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY2, HIGH);
    } else {
        digitalWrite(RELAY2, LOW);
    }
  }
  if (strcmp(topic,"/v1.6/devices/esp32/relay3/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY3, HIGH);
    } else {
        digitalWrite(RELAY3, LOW);
    }
  }
if (strcmp(topic,"/v1.6/devices/esp32/relay4/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY4, HIGH);
    } else {
        digitalWrite(RELAY4, LOW);
    }
  }
  if (strcmp(topic,"/v1.6/devices/esp32/relay5/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY5, HIGH);
    } else {
        digitalWrite(RELAY5, LOW);
    }
  }
  if (strcmp(topic,"/v1.6/devices/esp32/relay6/lv")==0){
   if ( (char)payload[0] == '1') {
        digitalWrite(RELAY6, HIGH);
    } else {
        digitalWrite(RELAY6, LOW);
    }
  }
  Serial.write(payload, length);
  Serial.println();
}


void reconnect() 
{
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

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as OUTPUT 
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);  
  pinMode(RELAY6, OUTPUT);
  
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

void loop() 
{
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("wifi disconnected\n");
  
    WiFi.begin(WIFISSID, PASSWORD);
  }
  
 if (!client.connected()) {
  reconnect();
  
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE1);
  client.subscribe(topic);
 
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE2);
  client.subscribe(topic);
  
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE3);
  client.subscribe(topic);

  
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE4);
  client.subscribe(topic);

  
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE5);
  client.subscribe(topic);

  
  sprintf(topic, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE6);
  client.subscribe(topic);
  }

  client.loop();
  delay(1000);
}
