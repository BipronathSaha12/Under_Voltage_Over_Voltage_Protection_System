
# Arduino Based Under Voltage and Over Voltage Protection System 

Overvoltage happen when voltages surpass their rated values, resulting in insulation damage and short circuits. They might be temporary or permanent, resulting in power surges and other risks.
Similarly, Undervoltage happens when the average voltage of equipment falls below the rated voltage amount. Frequent Undervoltage can result in a degradation in equipment performance and reliability.
In this project, we will construct a Smart Arduino Based AC Voltage Protection & Monitoring System with Under & Over Voltage Protection features. We can use a ZMPT101B voltage sensor to measure the current Voltage status and display it on LCD Display.
Voltage irregularities are a major issue in industries that frequently damage sensitive electronic equipment. In most cases, MCBs are used as a protection system, but it would be better if we implemented our own system, which could be less expensive and more effective. These fluctuations are caused by heavy load interruptions, thunder and lightning, and switching impulses.
Many devices are available on the market that monitor AC voltage and include Under, Normal, and Over Voltage Protection functions. However, they are pricey and cannot accept user input. This project seeks to address all of these issues and offer cost-effective protection and monitoring for electrical equipment from over and under AC voltages utilizing Arduino as a controller. So, we can use the ZMPT101B voltage sensor and Arduino to measure AC voltage, and if under or over voltage is detected, the relay can turn off the entire system.
The typical AC supply voltage in Asia and the rest of the world ranges between 220-240V. Voltage fluctuations are tolerated to an extent of +2%. If the voltage exceeds the tolerance level, an overvoltage is recognized. In addition, we have set the under voltage to 190V in this circuit. We used a 220V Fan AC Dimmer to test for differences in under and overvoltage. Refer to our earlier page for instructions on making your own AC dimmer.

## Block diagram of Arduino Over & Under AC Voltage Monitoring

![blockdiagramUVov](https://github.com/user-attachments/assets/4f59214e-b79f-4191-915e-ddef1b3d05cd)


### Circuit Diagram 

![Messenger_creation_7140D6A9-C717-4512-8FB9-B4AF95813F99](https://github.com/user-attachments/assets/4cf5166b-d16d-44b3-a004-03638140beba)

#### Authors

[@Bipronath Saha](https://github.com/BipronathSaha12)
