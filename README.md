# Light Barrier Circuit w/ Barker Codes
This project was inspired by a project on [hackster.io](https://www.hackster.io/hague/over-engineered-dual-core-light-barrier-c523a9). 

## Circuit:
<img src="Media\thumbnail.JPEG" alt="Light Barrier Circuit" width="400"/>

## How it works:
Instead of using infrared light to form a detection barrier, this circuit implements visible light emitted by the red LED in the form of a barker code. Because the sensor (photoresister) measured the light emitted by the LED and the ambient light (namely the 60Hz light from my ceiling lightbulbs), the circuit must be able to dicern from the LED light and the ambient light.

[Barker codes](https://en.wikipedia.org/wiki/Barker_code) have special properties that allow for this processing through cross-correlation. The microcontroller attached to the red LED emits the Barker-7 code at 10ms intervals, while the microprocessor attached to the photoresistor measures the light and performs calculations to find the barker code in the noisy signal. If it is found, no sound is emitted by the buzzer, otherwise a 1kHz frecuency is emitted.

## Limitations
It is not necessary to use two microprocessors when the barker code is emitted at 10ms intervals as the LED can be controller in between the calculations on the photoresistor data, but smaller intervals may require seperate cores for processing. These microprocessors follow the Arduino Nano standard, which means they are only signle core processors. The black slideswitch connects the two microprocessors, turning them on/off but also syncing them to eachother for the 10ms intervals. This is adequete for a short testing period, but over time the microprocessors could fall out of sync, making the light barrier fail/buzz constantly.