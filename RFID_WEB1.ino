#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define SS_PIN 21
#define RST_PIN 22
#define LED1_PIN 13
#define LED2_PIN 12
#define BUZZER_PIN 32

MFRC522 rfid(SS_PIN, RST_PIN);
const char* ssid = "DN";
const char* password = "deva2004";
WebServer server(80);

struct Student {
    String name;
    byte uid[4];
    int ledPin;
};

Student students[] = {
    {"DEVA", {241, 246, 174, 2}, LED1_PIN},
    {"NANTHU", {179, 99, 58, 42}, LED2_PIN},
};

const int numStudents = sizeof(students) / sizeof(students[0]);
String attendanceLog = "";
bool scannedUids[numStudents] = {false};
bool loggedIn = false;
String currentUser = "";

WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 0, 60000);

void setup() {
    Serial.begin(115200);
    SPI.begin();
    rfid.PCD_Init();
    WiFi.begin(ssid, password);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    timeClient.begin();
    server.on("/", handleLogin);
    server.on("/attendance", handleAttendance);
    server.on("/submit", handleSubmit);
    server.on("/approved", handleApproved);
    server.begin();
}

void loop() {
    server.handleClient();
    if (loggedIn) {
        if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
            for (int i = 0; i < numStudents; i++) {
                if (compareUid(rfid.uid.uidByte, students[i].uid, sizeof(students[i].uid)) && !scannedUids[i]) {
                    String timestamp = getTimestamp();
                    attendanceLog += "<tr><td>" + students[i].name + "</td><td>" + timestamp + "</td><td>From Location</td><td>To Location</td><td>Reason</td></tr>";
                    Serial.print("Card scanned for: ");
                    Serial.println(students[i].name);
                    scannedUids[i] = true;
                    digitalWrite(students[i].ledPin, HIGH);
                    tone(BUZZER_PIN, 1000);
                    delay(500);
                    noTone(BUZZER_PIN);
                    delay(1000);
                    digitalWrite(students[i].ledPin, LOW);
                    break;
                }
            }
            rfid.PICC_HaltA();
        }
        if (!rfid.PICC_IsNewCardPresent()) {
            resetScannedUids();
        }
    }
}

void handleLogin() {
    String html = R"rawliteral(
    <html lang="en">
    <head>
        <title>Login - RFID Gate Pass</title>
        <style> /* Inline styles for login page */ </style>
    </head>
    <body>
        <h1>ADHIYAMAAN COLLEGE OF ENGINEERING</h1>
        <form action="/submit" method="POST">
            <input type="text" name="name" placeholder="Enter your name" required>
            <input type="text" name="id" placeholder="Enter your ID" required>
            <input type="submit" value="Login">
        </form>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

void handleAttendance() {
    String html = R"rawliteral(
    <html>
    <head>
        <title>Attendance Log</title>
        <style> /* Inline styles for attendance page */ </style>
    </head>
    <body>
        <h1>Attendance Log</h1>
        <table>
            <tr><th>Name</th><th>Timestamp</th><th>From</th><th>To</th><th>Reason</th></tr>
            )rawliteral" + attendanceLog + R"rawliteral(
        </table>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

void handleSubmit() {
    if (server.hasArg("name") && server.hasArg("id")) {
        currentUser = server.arg("name");
        loggedIn = true;
        server.sendHeader("Location", "/attendance");
        server.send(303);
    } else {
        server.send(400, "text/plain", "Bad Request");
    }
}

void handleApproved() {
    String html = R"rawliteral(
    <html lang="en">
    <head>
        <title>Gate Pass Approved</title>
    </head>
    <body>
        <h1>Gate Pass Approved</h1>
        <h2>Your request has been approved!</h2>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

String getTimestamp() {
    timeClient.update();
    return timeClient.getFormattedTime();
}

void resetScannedUids() {
    for (int i = 0; i < numStudents; i++) {
        scannedUids[i] = false;
    }
}

bool compareUid(byte* uid1, byte* uid2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (uid1[i] != uid2[i]) {
            return false;
        }
    }
    return true;
}
