# RFID-Based Hostel Gate Pass System
![RFID Hostel Gate Pass](image/  <img width="1904" height="1055" alt="Screenshot 2024-11-19 120439" src="https://github.com/user-attachments/image/1f1cbd07-68ca-40f5-a88d-00233897179d" />
.png) 


## 📌 Project Overview
This project aims to solve the challenges students face when obtaining a gate pass from the hostel warden. It provides a web-based system where students can submit gate pass requests, specifying the reason and destination. The hostel warden can review and approve the requests, allowing students to exit the hostel using an RFID-based authentication system.

## 🚀 Features
- 🏠 **Student Portal**: Students can log in and request a gate pass with a reason and address.
- 🎫 **Warden Dashboard**: Hostel wardens can review, approve, or reject gate pass requests.
- 📡 **RFID Authentication**: Approved students can scan their RFID card to validate their exit.
- 💡 **LED Indication**: LED signals for gate pass approval (Green - Approved, Red - Rejected).
- 📊 **SQL Database**: Stores student requests, approvals, and RFID details.
- 🔗 **ESP32 Integration**: Handles RFID authentication and communicates with the database.

## 🛠️ Technologies Used
- **Hardware**: ESP32, RFID Reader (RC522), LED indicators
- **Backend**: Python (Flask/Django)
- **Database**: MySQL / SQLite
- **Frontend**: HTML, CSS, JavaScript
- **Communication**: Serial / WiFi (ESP32)

## 🔧 How It Works
1. **Student Requests**: Students log in to the website and submit a gate pass request.
2. **Warden Approval**: The hostel warden reviews the request and grants/rejects access.
3. **RFID Authentication**: Upon approval, students scan their RFID card at the exit.
4. **LED Indication**: A green LED signals approval, while a red LED indicates rejection.
5. **Database Logging**: All requests and approvals are stored in the SQL database.

## 📌 Future Enhancements
- SMS/Email notifications for request status updates.
- Mobile app integration for easy access.
- AI-based analysis for monitoring student movements.

## 📄 License
This project is open-source and available for modification.

---
