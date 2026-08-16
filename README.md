# ESP32 Wi-Fi Hardware Control Panel

## Project Overview

- Built a Wi-Fi-enabled hardware control system using ESP32.
- Created a web-based control panel that can be accessed from a laptop or phone.
- The system allows remote control of an LED and SG90 servo through Wi-Fi.

## Features

- LED ON/OFF control through a web browser.
- SG90 servo OPEN/CLOSE control.
- Servo angle control from 0° to 180°.
- ESP32 acts as a web server.
- Browser communicates with ESP32 using HTTP requests.
- Control works over a local Wi-Fi network.

## Hardware Used

- ESP32 Development Board
- SG90 Mini Servo Motor
- LED
- 220Ω/330Ω resistor
- Breadboard
- Jumper wires
- Laptop/Phone
- Wi-Fi hotspot/router

## Pin Connections

- LED → GPIO 13
- Servo signal → GPIO 18
- Servo power → VIN/5V
- Servo GND → GND

## Software Used

- Arduino IDE
- ESP32 Arduino Core
- ESP32Servo Library
- HTML
- CSS
- JavaScript

## How It Works

- ESP32 connects to a Wi-Fi network.
- ESP32 receives a local IP address.
- A web server runs directly on the ESP32.
- The IP address is opened in a browser.
- The browser displays the control panel.
- Clicking a button sends an HTTP request to the ESP32.
- ESP32 processes the request and controls the corresponding hardware.
- LED is controlled through GPIO.
- Servo position is controlled through PWM.

## Concepts Learned

- ESP32 Wi-Fi communication
- IP addressing
- HTTP requests
- HTTP endpoints
- Client-server architecture
- ESP32 web server
- GPIO control
- PWM and servo control
- HTML/CSS/JavaScript basics
- Embedded hardware-software integration
- IoT fundamentals
- Serial Monitor debugging

## Project Outcome

- Successfully controlled an LED remotely through a web browser.
- Successfully controlled an SG90 servo remotely through the web interface.
- Implemented adjustable servo angle control from 0° to 180°.
- Successfully established communication between a laptop and ESP32 over Wi-Fi.

## Future Improvements

- Add authentication for secure access.
- Add sensors and real-time monitoring.
- Add MQTT communication.
- Add data logging.
- Add more actuators and devices.
- Develop a more advanced mobile-friendly dashboard.

## Key Learning

- This project helped me understand how a microcontroller can communicate wirelessly with a user interface and convert web commands into real-world hardware actions.
- It gave me practical experience combining Embedded Systems, Wi-Fi communication and IoT.
