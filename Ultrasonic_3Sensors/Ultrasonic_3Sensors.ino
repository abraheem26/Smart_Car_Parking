


// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "dummy-d18d5-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "GiuXtbp0vwY2pbjFU5nEGf6gLeegOouxpVLNJL4X"
#define WIFI_SSID "HassaanRouter"
#define WIFI_PASSWORD "12345678"

const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

const int trigPin2 = 13;  //D7
const int echoPin2 = 15;  //D8

const int trigPin3 = 5;  //D1
const int echoPin3 = 4;  //D2



long duration;
int distance;
bool car;

long duration2;
int distance2;
bool car2;

long duration3;
int distance3;
bool car3;


void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {

// Clears the trigPin
digitalWrite(trigPin, LOW);

delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);


delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);


// Clears the trigPin
digitalWrite(trigPin2, LOW);

delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);


delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);


// Clears the trigPin
digitalWrite(trigPin3, LOW);

delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin3, HIGH);


delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);


// Calculating the distance
distance= duration*0.034/2;

distance2= duration2*0.034/2;

distance3= duration3*0.034/2;

Serial.print("Distance1: ");
Serial.println(distance);

Serial.print("Distance2: ");
Serial.println(distance2);

Serial.print("Distance3: ");
Serial.println(distance3);


//first distance
if(distance <10){
  car=true;
}

else{
  car=false;
}
//second distance
if(distance2 <10 && distance2>0){
  car2=true;
}


else{
  car2=false;
}

//third distance
if(distance3 <10 && distance3>0){
  car3=true;
}


else{
  car3=false;
}


  // set bool value
  Firebase.setBool("Parking_Spots/Spot_1/availability", not(car));
  Firebase.setInt("Parking_Spots/Spot_1/index", 1);
  
  Firebase.setBool("Parking_Spots/Spot_2/availability", not(car2));
  Firebase.setInt("Parking_Spots/Spot_2/index", 2);
  
  Firebase.setBool("Parking_Spots/Spot_3/availability", not(car3));
  Firebase.setInt("Parking_Spots/Spot_3/index", 3);

  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);


}
