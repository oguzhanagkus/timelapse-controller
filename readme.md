This is my hobby project that enables capturing timelapses with DSLR cameras.

Informations about each function are given above the function.

Briefly, it is a intervalometer to make timelapses.
Also it has bulb mode. You can make exposures longer than 30 seconds.
It is developed on ARDUKIT that is Arduino Mega 2560 based development kit.
I did not deal with cable clutter thanks to ARDUKIT.
But you do not use to ARDUKIT. You can combine all compenent you need.

Compenent list: 1 Ardunio Uno / Mega
                1 2x16 LCD screen
                1 potentiometer (does not matter its value)
                1 relay (maybe a transistor can be used instead of it)
                2 push button
                1 330 ohm resistor
                1 diode (I used 1N4007)
                1 2,5mm male jack connect to Canon DSLR (if you wish use with socket)
                Some jumpers and a release cable to connect DSLR

Note: I used it on Canon 650D. Its shutter release connect with 2,5mm jack.
      So if you have another brand's machine check their pinouts.
      Then modify the related part. Probably, it will work, too.

If you want, you can use shields. So you can make a case for your intervalometer easily.

How it works?
Briefly, it controls the shutter release automatically according to settings you did.
For example, you want to shot every 5 seconds. You set it and start. It do it automatically.
It press the shutter instead of you. The relay is on means shutter is pressed.

After you start the program, you will see opening message and instructions.
Then you will see the menu. It has two mode. Move the potentiometer and press enter button to select.

Timelapse Mode
This mode help you to shot images for timelapses.
After select this mode, you will make two settings.
Set the interval using the potentiometer. Then press enter.
Interval is bounded 1-300 seconds. If you want, change borders. I think its ideal.
Do not forget to calculate writing time to card. Keep in mind your exposure time you set in your machine.
After set the interval, you should set the shot count between 1-500.
If your battery is very well, you can capture more than 500 but its ideal border, I think.
Then press enter to show capture information. It also shows you estimated time.
To start, press enter. To cancel and return to menu, press down button.
After you press enter, it will be in 3 seconds. The backlight will be turned off beacuse of power.
Capturing will take long time. We should save our power supply.
During the capturing left shot count will shown in the screen.
If you wish stop the capturing, you should press to reset button of Arduino.
When it finished, backlight will be turned on and it will tell you that capture finished.
Press any button to go menu.

Bulb Mode
This mode help you make very long exposures, especially more than 30 seconds.
After select this mode, press enter button to start. If you want return press down button.
When you press enter capture starts immediately. It will last until you press enter button to stop.
Then it shows the time that capture last. Now you can press any button to go menu.