#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char* ssid = "FuckingAwesome";   // Nama SSID WiFi
const char* password = "apiipp.com";    // Password WiFi

const int espled = 2;   // Pin LED indikator koneksi WiFi
const int ledPin1 = 4;  // Pin LED 1 (Dapur)
const int ledPin2 = 5;  // Pin LED 2 (Tamu)
const int ledPin3 = 19; // Pin LED 3 (Makan)

bool dapurLedState = false;
bool tamuLedState = false;
bool makanLedState = false;

void setup() {
    Serial.begin(115200); // Inisialisasi komunikasi serial

    // Set mode pin sebagai OUTPUT
    pinMode(espled, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);

    // Matikan semua LED di awal
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);

    // Koneksi ke WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");

    // Loop hingga terhubung ke jaringan WiFi
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(espled, LOW); // LED indikator berkedip selama koneksi
        delay(1000);
        Serial.print(".");
    }

    digitalWrite(espled, HIGH); // LED indikator menyala jika terhubung
    Serial.println("\nConnected to WiFi network!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // Cetak alamat IP lokal

    // HTTP GET untuk status LED
    server.on("/dapur", HTTP_GET, getDapurLed);
    server.on("/tamu", HTTP_GET, getTamuLed);
    server.on("/makan", HTTP_GET, getMakanLed);

    // HTTP POST untuk mengubah status LED
    server.on("/dapur", HTTP_POST, setDapurLed);
    server.on("/tamu", HTTP_POST, setTamuLed);
    server.on("/makan", HTTP_POST, setMakanLed);

    server.begin();
    Serial.println("Server started");
}

void loop() {
    server.handleClient(); // Handle HTTP client
}

// Mengontrol LED Dapur
void setDapurLed() {
    dapurLedState = !dapurLedState;
    digitalWrite(ledPin1, dapurLedState ? HIGH : LOW);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", dapurLedState ? "ON" : "OFF");
}

// Mengontrol LED Tamu
void setTamuLed() {
    tamuLedState = !tamuLedState;
    digitalWrite(ledPin2, tamuLedState ? HIGH : LOW);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", tamuLedState ? "ON" : "OFF");
}

// Mengontrol LED Makan
void setMakanLed() {
    makanLedState = !makanLedState;
    digitalWrite(ledPin3, makanLedState ? HIGH : LOW);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", makanLedState ? "ON" : "OFF");
}

// Mendapatkan status LED Dapur
void getDapurLed() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", dapurLedState ? "ON" : "OFF");
}

// Mendapatkan status LED Tamu
void getTamuLed() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", tamuLedState ? "ON" : "OFF");
}

// Mendapatkan status LED Makan
void getMakanLed() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", makanLedState ? "ON" : "OFF");
}
