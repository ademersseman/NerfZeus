# NerfZeus
Included in this repository are my files for a [Nerf blaster](https://www.amazon.com/Nerf-Rival-Zeus-MXV-1200-Blaster/dp/B00VX9F5G6?th=1) I have wired up to an [Arduino](https://store-usa.arduino.cc/products/arduino-nano/) to increase functionality.
## Demonstration
## Features
* [CNC cut](https://www.youtube.com/shorts/z72jtO_NJdo) slits for [LCD](https://www.youtube.com/watch?v=qvk_KqMDpkA), LED strip, and the lightning bolt LED
* Sanded, [primed](https://www.amazon.com/gp/product/B0876DM8L8/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), [hydrodipped](https://www.youtube.com/watch?v=PM9zkxGlZ6o), then [clear-coated](https://www.amazon.com/gp/product/B006ZLQKQG/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
* [Mosfets](https://www.amazon.com/High-Power-Transistor-Adjustment-Electronic-Brightness/dp/B0952LQRTZ/ref=sr_1_8?crid=1AJKS5UCQZRH9&keywords=arduino+mosfet&qid=1654103866&s=electronics&sprefix=arduino+mosfet%2Celectronics%2C65&sr=1-8) control the [solenoid](https://www.amazon.com/0530-Frame-Solenoid-Electromagnet-Stroke/dp/B07K35L4TH/ref=asc_df_B07K35L4TH/?tag=hyprod-20&linkCode=df0&hvadid=343955653419&hvpos=&hvnetw=g&hvrand=13716584401319201639&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1018095&hvtargid=pla-733922966132&psc=1&tag=&ref=&adgrpid=70729713273&hvpone=&hvptwo=&hvadid=343955653419&hvpos=&hvnetw=g&hvrand=13716584401319201639&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1018095&hvtargid=pla-733922966132) and motor.
* An [infrared led](https://www.digikey.com/en/products/detail/qt-brightek-qtb/QBLP653-IR3/5299229?s=N4IgTCBcDaII4CMA2AHAbAVgMwFoCSASliALoC%2BQA) and [sensor](https://www.digikey.com/en/products/detail/vishay-semiconductor-opto-division/TSOP18456/8556536?utm_adgroup=Temperature%20Sensors%20-%20NTC%20Thermistors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Sensors%2C%20Transducers_NEW&utm_term=&utm_content=Temperature%20Sensors%20-%20NTC%20Thermistors&gclid=Cj0KCQjwnNyUBhCZARIsAI9AYlEBhRqWYb9Gbd37PVzR86RHP54eGQX1h0B9IgQUE2Ub4C6oELgv0usaAl-KEALw_wcB) are places on opposite sides of the barrel to detect passing balls.
* The LCD screen displays the number of remaining ammo and the voltage of the battery.
* An [LED strip]([https://a.co/d/eVlWRH4](https://www.amazon.com/dp/B08ZHCQS8P/ref=cm_sw_r_api_i_QF52V4BFF7XM3XWEKZ2G?_encoding=UTF8&psc=1)) of sixteen leds displays the remaining ammo at a quick glance.
## The circuit diagram
![NerfZeus](https://user-images.githubusercontent.com/38081126/170147878-2ea72245-42ce-4946-8af7-eb5291e770c8.jpg)
Created with [Scheme-it](https://www.digikey.com/schemeit/project/)
## The future
Also included are the [files](https://github.com/ademersseman/NerfZeus/tree/main/NerfZeusOOP) for an object oriented approach to this problem. Unfortunately, the object oriented approach is unfinished and will be revisited at a later date as the LCD screen looks like this under the current implementation. This may look like it is caused by electric noise but alas a functional implementation of LCD control as it appears in this repository functions flawlessly. This is a software issue I will crack once I am more familiar with C++.![IMG_1272](https://user-images.githubusercontent.com/38081126/169588125-8101f675-aefb-4f70-af85-870e87a8a555.jpg)
