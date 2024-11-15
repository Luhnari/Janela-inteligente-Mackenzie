#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

#define GREEN_LED 5
#define RED_LED 4
#define SERVO 2
#define SENSOR 14

unsigned long lastMsg = 0;
char msg[50];
int count = 0;

void writeServoAngle(int angle) {
  int pulseWidth = map(angle, 0, 180, 1000, 2000);
  digitalWrite(SERVO, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(SERVO, LOW);
  delay(20);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando se conectar ao broker MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Conectado ao broker MQTT");
      client.subscribe("topico/controle");
    } else {
      count++;
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      if (count >= 5) {
        Serial.println("Não foi possível conectar após várias tentativas. Verifique a rede ou o broker.");
        break;
      }
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Conectado ao Wi-Fi");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(SERVO, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int rainValue = analogRead(SENSOR);
  Serial.print("Valor do sensor de chuva: ");
  Serial.println(rainValue);

  if (rainValue < 500) {
    writeServoAngle(180);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Serial.println("Com chuva, servo em 180 graus e LED VERMELHO aceso.");
    delay(2000);

  } else {
    writeServoAngle(0);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("Sem chuva, servo em 0 graus e LED VERDE aceso.");
    delay(2000);
  }

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    sprintf(msg, "Umidade do sensor: %d", rainValue);
    client.publish("topico/sensor", msg);
  }
}
