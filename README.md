# ESP32 Wi-Fi Security Monitoring System

## Project Overview and Resources
The purpose of this project is to build a cybersecurity monitoring device using the ESP32 microcontroller. Many users connect to Wi-Fi networks without knowing if the network is secure or if unauthorized devices are connected.This tool will allow users to monitor nearby networks, view connected devices, and detect unusual activity such as duplicate network names, weak security protocols, or unexpected signal changes. 

* **Hardware:** ESP32 Development Board, Data-capable USB cable.
* **Software:** Arduino IDE, standard `WiFi.h` and `WebServer.h` libraries.

## Step-by-Step Installation/Configuration Instructions
1. Connect the ESP32 to your Mac mini using a data-transfer USB cable.
2. Open the Arduino IDE. In Settings, add `https://dl.espressif.com/dl/package_esp32_index.json` to the Additional Boards Manager URLs.
3. Install the `esp32` package from the Boards Manager.
4. Select the specific ESP32 board model and the corresponding `/dev/cu.usbserial` port.
5. Paste the provided monitoring code into the IDE and click Upload (hold the BOOT button on the ESP32 if the terminal pauses on "Connecting...").
6. Connect your viewing device to the `ESP32_Security_Monitor` Wi-Fi network and navigate to `192.168.4.1` in your browser.

## Troubleshooting Notes and Challenges Encountered
* **Environment Setup:** One anticipated challenge is configuring the ESP32 software environment and ensuring compatibility between the Arduino IDE libraries and the ESP32 board drivers. 
* **Data Optimization:** Since the ESP32 has limited processing power and memory compared to a traditional computer, optimizing performance and organizing the scanned data may take additional effort. Using standard built-in libraries rather than heavy third-party async web servers helped mitigate this.

## Screenshots
<img width="2560" height="1438" alt="Screenshot 2026-05-23 at 9 54 32 AM" src="https://github.com/user-attachments/assets/c98d6661-3d13-4142-974d-ba59317821d9" />
<img width="2560" height="1400" alt="Screenshot 2026-05-23 at 9 57 14 AM" src="https://github.com/user-attachments/assets/96ae8573-5828-4472-bf0c-f71d9b5a0714" />
<img width="2558" height="351" alt="Screenshot 2026-05-23 at 10 01 07 AM" src="https://github.com/user-attachments/assets/4e7b2852-5414-4106-a935-0e27fa2de2dc" />
<img width="477" height="181" alt="Screenshot 2026-05-23 at 9 59 52 AM" src="https://github.com/user-attachments/assets/30e34d01-334e-42fc-b575-7ab16a599f66" />



