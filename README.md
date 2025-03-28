# RFID Web-Based Hostel Gate Pass System

## 📌 Project Overview
The **RFID Web-Based Hostel Gate Pass System** is designed to automate and secure the hostel entry and exit process using **RFID (Radio Frequency Identification) technology**. The system integrates **ESP32, RFID reader (RC522), and a web-based platform** to ensure seamless gate pass management.

## 🎯 Features
- **RFID-based authentication** for students and hostel staff.
- **Web dashboard** for real-time monitoring and managing gate passes.
- **Automated logging** of entry and exit with timestamps.
- **Admin panel** for student record management.
- **Database integration** (MySQL) for storing pass details.

## 🛠️ Tech Stack
- **Hardware:** ESP32, RFID RC522, LED, (for gate control)
- **Frontend:** HTML, CSS, JavaScript (with Bootstrap)
- **Backend:** PHP, Node.js 
- **Database:** MySQL 
- **Communication:** HTTP requests / MQTT (for IoT integration)

## 🔧 Installation & Setup
### 1️⃣ Hardware Setup
1. Connect **RC522 RFID Reader** to ESP32:
   - SDA → GPIO 5
   - SCK → GPIO 18
   - MOSI → GPIO 23
   - MISO → GPIO 19
   - RST → GPIO 22
   - GND → GND
   - 3.3V → 3.3V
2. Connect **Servo Motor** to ESP32 for gate operation.
3. 
#### **ESP32 Code Upload**
1. Install **Arduino IDE** and ESP32 board drivers.
2. Upload the **rfid_esp32.ino** file after configuring Wi-Fi and server details.

## 📸 Screenshots
#![Screenshot]("C:\Users\Dell\OneDrive\Pictures\Screenshots\Screenshot 2024-11-19 120439.png")

## 🚀 Future Enhancements
- Mobile app integration.
- Face recognition-based authentication.
- Cloud-based database support.

---
### 📩 Need Help?
Feel free to raise an issue or reach out for collaboration!

