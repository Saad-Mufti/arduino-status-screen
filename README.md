# **Cool Status Screen**
A fun little project to show a couple of status items on an Arduino board (LilyGO) with an LCD soldered on to it.

## **Features**
- WPM Calculator: Run `crude_wpm_calc.py` and the device will show your WPM, which is basically calculated by counting how many non-consecutive spaces you type.
- WiFi Connectivity: Once the intended WiFi SSID and password are inputted into `status_screen.ino`, the device automatically connects. (Planned: Show local weather, stock tickers, and more).
- *In Progress*: Inspired from [this](https://www.reddit.com/r/MechanicalKeyboards/comments/h0a7kq/i_made_an_oled_animation_of_bongo_cat_that/), the faster you type, the faster the cat will tap. So far, only a static image is present
- *Planned*: Dark mode

## **Installation**
Before doing any of the below, be sure to clone this repository with `git clone <URL>`.

### Arduino Sketch
If you've never ran an Arduino sketch for an ESP-variant board, do the following:
1. Go to File > Preferences > Settings > "Additional Boards Manager URLs" and add the following link: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. Go to Tools > Board Manager, look for "esp32", and download it. It's quite a large download. 
3. Select the "ESP32 Dev Module" board for uploading, and ensure the following settings are selected:
   - PSRAM: "Disabled"
   - Flash Size: "4 MB (32 Mb)"
4. Install the `TTGO_eSPI` library (these instructions are also available [here](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)):
    1. Clone [the official repository](https://github.com/Xinyuan-LilyGO/TTGO-T-Display).
    2. Copy the `TFT_eSPI` folder into `<C:\Users\Your User Name\Documents\Arduino\libraries>`.
5. Everything should work properly! 

### Python Script (Windows only, for now)
The Python script is solely for the WPM functionality, so if you don't want that, this part isn't really necessary. Otherwise, there are two options:
1. Download the .exe file in the "Releases" page, OR
2. Run the script yourself (which requires a working Python environment). The only two 3rd party libraries used are `pynput` and `pyserial`, so be sure to install those.