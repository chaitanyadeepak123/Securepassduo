# SECUREPASS DUO: GSM & RFID OTP-Based Authentication System

## Overview

**SECUREPASS DUO** is a two-factor authentication access control system built using the **LPC2148 ARM7 microcontroller**. It combines **RFID-based user identification** with **GSM-based OTP verification** to improve security. After a valid RFID scan, a one-time password (OTP) is sent to the user's registered mobile number. Access is granted only if the correct OTP is entered within the allowed time.

## Key Features

* Two-factor authentication (RFID + OTP)
* RFID user identification
* Dynamic OTP generation
* GSM-based SMS OTP delivery
* RTC-based OTP timeout
* LCD status display
* Matrix keypad for OTP entry
* Relay-controlled door lock
* Interrupt-driven UART communication
* Administrator configuration mode

## Problem Statement

Traditional RFID systems are vulnerable if an RFID card is lost, stolen, or duplicated. This project enhances security by adding OTP verification, ensuring only authorized users can gain access.

## Hardware

* LPC2148 ARM7 Development Board
* RFID Reader & RFID Card
* GSM Modem (M660A)
* 16×2 LCD
* 4×4 Matrix Keypad
* Relay Module
* Power Supply

## Software

* Embedded C
* Keil uVision IDE
* Flash Magic

## Working

1. Scan RFID card.
2. Verify the card ID.
3. Generate a dynamic OTP using RTC.
4. Send the OTP via GSM.
5. User enters the OTP through the keypad.
6. If the OTP is correct, the relay unlocks the door; otherwise, access is denied.

## Modules

* RFID Authentication
* GSM Communication
* RTC Management
* LCD Display
* Keypad Interface
* UART Interrupt Handling
* Admin Configuration

## Technologies Used

* LPC2148 ARM7
* Embedded C
* UART Communication
* RFID
* GSM
* RTC
* LCD & Keypad Interfacing
* Interrupt Programming

## Applications

* Smart Home Security
* Office & Corporate Access
* Laboratories
* Educational Institutions
* Industrial Security
* Server Rooms

## Future Enhancements

* Fingerprint Authentication
* Face Recognition
* IoT & Wi-Fi Integration
* Cloud-Based Access Logs
* Mobile App Monitoring

## Conclusion

SECUREPASS DUO provides a secure, reliable, and cost-effective access control solution by combining RFID authentication with GSM-based OTP verification. The project demonstrates real-time embedded system design and hardware-software integration for enhanced security applications.
