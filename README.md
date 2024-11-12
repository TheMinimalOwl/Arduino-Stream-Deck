# Stream Deck with Arduino

This repository contains the code and documentation to create a **custom Stream Deck** using an **Arduino** and a touch LCD screen. The Stream Deck is a programmable button device that allows you to launch applications, execute macros, and control various functions on your PC, making it ideal for streamers, content creators, and automation enthusiasts.

## Features

- **Touch LCD Screen**: Intuitive interface to interact with the buttons.
- **Customizable Buttons**: Assign different functions to each button, such as launching applications, controlling volume, managing Discord, etc.
- **Visual Feedback**: Custom icons for each button, providing an attractive visual experience.
- **Bluetooth**: Wireless communication with the PC to execute commands remotely.
- **Dynamic User Interface**: Menu system to navigate between different button sets.

## Components

- **Arduino Mega 2560** (Others can be used, but with limited functions)
- **TFT LCD Touchscreen** (480x320 preferably)
- **Bluetooth Module** (optional, can connect via USB)
- **RTC DS1307** (optional, for showing real time)
- **LED Strip** (optional, for visual effects)
- **Additional Physical Buttons** (optional, for extra functions)
- **Rotary Encoders** (optional, for additional control)

## Installation and Setup

1. **Clone this repository** to your local machine:
    ```bash
    git clone https://github.com/TheMinimalOwl/StreamDeckArduino.git
    ```

2. **Install the required libraries** from the Arduino Library Manager:
    - `Adafruit GFX Library`
    - `MCUFRIEND_kbv`
    - `RTClib` (for RTC Clock)
    - `SoftwareSerial` (for Bluetooth)
    - `Adafruit TouchScreen`

3. **Connect the hardware** according to the connection diagram provided in the documentation.

4. **Upload the code** to your Arduino.

5. **Customize the buttons** and functions by editing the configuration files.

## Usage

- **User Interface**: Touch the buttons on the touchscreen to execute the assigned functions.
- **Menu Navigation**: Use the buttons to switch between different function screens.
- **Configuration**: Edit the configuration file to change the functions assigned to each button.

For the detailed use of each of the functions see: [Documentation](https://github.com/)

## Contributing

Contributions are welcome! If you have ideas for new features or improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the **MIT License**. See the `LICENSE` file for more details.

## Credits

- Inspired by the Elgato Stream Deck.
- Developed and documented by [Samuel Gil](https://github.com/TheMinimalOwl).

---

We hope you enjoy creating and using your own Arduino Stream Deck! If you have any questions or need help, feel free to open an issue or contact us.
