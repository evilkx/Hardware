#include "DHT.h"
#include <PubSubClient.h>
#include <WiFi.h>

#define WIFI_AP "Shi-WiFi_2.4G"//wifi名称
#define WIFI_PASSWORD "12341234"//wifi密码

#define DHTPIN 19    
#define DHTTYPE DHT11   // DHT 11
char MqttServer[] = "www.chenxiky.com";//搭建的mqtt服务器域名或者ip地址都可以

// 初始化以太网客户端对象 -- WiFiClient.h
WiFiClient espClient;

// 初始化DHT11传感器
DHT dht(DHTPIN, DHTTYPE);

// 初始化MQTT库PubSubClient.h的对象
PubSubClient client(espClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;



void setup() {
  Serial.begin(9600);
  Serial.println("温湿度数据:");
  dht.begin();

  InitWiFi();                                // 连接WiFi
  client.setServer( MqttServer, 1883 );      // 连接WiFi之后，连接MQTT服务器
  lastSend = 0;
}

void loop() {
  
 status = WiFi.status();
  if ( status != WL_CONNECTED) {
    while ( status != WL_CONNECTED) {
      Serial.print("[loop()]Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_AP);
      // 连接WiFi热点
      status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      delay(1000);
    }
    Serial.println("[loop()]Connected to AP");
  }

  if ( !client.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) { // 用于定时1秒钟发送一次数据
    getAndSendTemperatureAndHumidityData(); // 获取温湿度数据发送到MQTT服务器上去
    lastSend = millis();
  }

  client.loop();
}

/*
 * 
 * 读取温湿度数据，然后发送到MQTT服务器上去
 * 
 */
void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");

  // 大概1s读取一次
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // 查看是否读取温湿度失败的
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  String temperature = String(t);
  String humidity = String(h);

  // Just debug messages
  Serial.print( "Sending temperature and humidity : [" );
  Serial.print( temperature ); Serial.print( "," );
  Serial.print( humidity );
  Serial.print( "]   -> " );

  // 构建一个 JSON 格式的payload的字符串
  String payload = "{";
  payload += "\"temperature\":"; payload += temperature; payload += ",";
  payload += "\"humidity\":"; payload += humidity;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  
  // boolean publish(const char* topic, const char* payload);
  
//wendu这个是发表主题 ,你订阅这个主题就可以收到温湿度了
  client.publish( "wendu", attributes );
  
  Serial.print("[publish]-->>");
  Serial.println( attributes );
}

void InitWiFi()
{
  delay(10);
  // 尝试连接WiFi网络
  while ( status != WL_CONNECTED) {
    Serial.print("[InitWiFi]Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_AP);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    delay(1000);
  }
  Serial.println("[InitWiFi]Connected to AP");
}

/**
 * 
 * MQTT客户端断线重连函数
 * 
 */

void reconnect() {
  // 一直循环直到连接上MQTT服务器
  while (!client.connected()) {
    Serial.print("[reconnect]Connecting to MQTT Server ...");
    // 尝试连接connect是个重载函数 (clientId, username, password)
    if ( client.connect("ESP_32", NULL, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ mqtt connect error code = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );// Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
