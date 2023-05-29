# Wemos Based Automation

This project demonstrates a web-based automation system using the ESP8266-based Wemos board. It allows you to control an LED and a Servo motor remotely through a web interface. The system also includes an LCD display and a button, which can be integrated into the project for enhanced functionality.

## Description

The Wemos-based automation system utilizes the ESP8266 WiFi module to connect to a local Wi-Fi network. It sets up a web server that hosts a web application, allowing users to control the connected LED and Servo motor remotely.

The web application provides an intuitive interface where users can interact with the system. It displays the status of the LED and Servo motor, allows users to turn them on/off, and provides a mechanism to add scheduled events for automated control. The LCD display can be used to show relevant information, while the button can trigger specific actions.

## How It Works

1. The Wemos board connects to the local Wi-Fi network using the provided SSID and password.
2. It sets up a web server on port 80 and starts listening for incoming client requests.
3. When a client accesses the root page ("/"), the web server responds with the HTML template that defines the web application interface.
4. The user can interact with the web application by selecting the desired component (e.g., LED) and activity (e.g., turning on/off). They can also set a specific time range for scheduled events.
5. When the user clicks the "Add Event" button, an HTTP request is sent to the server with the selected component, activity, and time information.
6. The server handles the request and updates the web application interface accordingly.
7. The server also performs the corresponding actions based on the received parameters. For example, it turns on/off the LED and adjusts the Servo motor position.
8. The LCD display can show relevant information, such as the current schedule, component status, or system messages.
9. The button can trigger specific actions when pressed, such as toggling the LED or executing a predefined routine.

## Significance

This project showcases the capabilities of the ESP8266-based Wemos board in building web-based automation systems. It provides a practical example of remote control and scheduling of electronic components using a simple and intuitive web interface.

The code can be further extended to integrate additional components, sensors, or actuators, allowing for more complex automation scenarios. It serves as a starting point for developing custom automation systems using the Wemos board and provides a foundation for exploring home automation, IoT applications, and smart device control.

By understanding and customizing this code, you can build your own web-based automation systems tailored to your specific requirements.

## Prerequisites

To use this code and run the project, you need the following:

- ESP8266-based Wemos board
- Arduino IDE or compatible development environment
- ESP8266WiFi, WiFiClient, ESP8266WebServer, and Servo libraries installed

## Setup Instructions

1. Connect the LED and Servo motor to the appropriate pins on the Wemos board.
2. Set up the Wi-Fi credentials by replacing the `ssid` and `password` variables in the code with your network's SSID and password.
3. Upload the code to the Wemos board using the Arduino IDE or compatible development environment.
4. Open the serial monitor to view the assigned IP address of the Wemos board once it connects to the Wi-Fi network.
5. Access the IP address from a web browser to control and monitor the LED and Servo motor.

Note: Additional setup steps may be required depending on the integration of the LCD display and button.

Feel free to modify the code and customize the web
