# R3-SoftwareTask1-AnuramThirumoli
Arduino Uno program written for R3 Software Task 1. Displays a number between 0 and 99 to two 7-segment displays based on a potentiometers output/position. Uses multiplexing instead of using two CD4511 7-segment decoders.

![image](https://user-images.githubusercontent.com/59899086/136715278-7a5f7000-f508-4d3c-bbc4-877420445891.png)

**1. How is the project powered?** \
The project is powered through the Arduino Uno's built-in 5V output and its ground. There are wires (red for 5V and black for ground) connecting all the breadboards in the project to a common power and ground. It is important to have a common ground so that the project references the same point for voltage measurements.

**2. How is the potentiometer output measured by the Arduino Uno?** \
The potentiometer is connected to 5V and ground through its Terminal 1 and Terminal 2 pins. To measure the voltage of the potentiometer, the wiper pin is connected to the analog input port A0 on the Arduino Uno (using the green wire). We are using the A0 (analog) port instead of the digital ports because instead of the 0V and 5V the digital ports output, we want to know the voltage in the range from 0V to 5V. \
In order to convert the potentiometers output to a range from 0 to 99, we use Arduino's analogRead() and map() functions. To do this correctly, we must keep in mind that the analogRead() function returns a integer from 0 to 1023, with 0 being 0V and 1023 being 5V respectively. Therefore, we have to map the analogRead() function from the values 0 to 1023, to the values 0 to 99. The code to do this is given below:
```
int pot_range = map(analogRead(A0), 0, 1023, 0, 99);
```

**3. How is the CD4511 decoder connected?** \
Since I am using multiplexing to run the 7-segment displays, I only need to use one CD4511 decoder. This decoder uses Binary Coded Decimal to represent the numbers 0 to 9 using its binary equivalent (ex. the number 9 is the binary pattern 1001). Therefore, I need to use 4 digital pins and output HIGH and LOW using the binary pattern of the number I want to display to the CD4511 decoder. I do this by connecting the digital pins 8, 9, 10, and 11 from the Arduino Uno to the pin inputs 1, 2, 3, and 4 respectively (brown wires).

Here are the other pins in the 7-segment display and what I have done with them (other than the 7-segment output pins):
- *Power:* I have connected this to 5V power rail.
- *Lamp Test:* When you connect this to LOW (ground) all the segments in the display turn on. This is used to test if the 7-segment display is working. Since we want to change which segments are off, we connect this is HIGH (the 5V power rail).
- *Blanking:* When you connect this to LOW (ground) all the segments in the display turn off. Since we want to be able to turn the segments on, we connect this to HIGH (the 5V power rail).
- *Latch Enable:* When you connect this to LOW, it will allow the decoder to read the 4 inputs and output to the 7-segment display. Therefore, we connect this to LOW (ground).
- *Ground:* I have connected this to ground.

![image](https://user-images.githubusercontent.com/59899086/136716180-854a657f-7aea-40b6-9f32-a850eab69cac.png)

**4. How is multiplexing used to control two 7-segment displays?** \
Multiplexing is used to be able to control multiple devices using the same I/O lines instead of using seperate I/O lines. Even though this method is slightly more complex, it allows us to use less I/O lines. For example, instead of using 8 I/O lines by having two seperate CD4511 decoders, we are able to use only one decoder and consequently only need 4 I/O lines.

For this project, I am using a common cathode 7-segment display. This means that the LEDs in the 7-segment display have a common cathode (ground), and each segment's LEDs must be connected to 5V for the segment to light up. Knowing this, if we ensure that the common cathode pin is not connected to ground, the 7-segment display will not light up. Therefore, we can use the same 7 lines from the single CD4511 decoder to display numbers on both 7-segment displays. We just have to ensure that when one 7-segment display is connected to ground, the other is not. Since we are doing this very quickly, it is impossible for our eyes to register that the 7-segment displays are turning on and off. 

**5. How are the two 7-segment displays connected?** \
From the CD4511 decoder, we have 7 pins ranging from A to G. Each pin corresponds to a certain segment on the 7-segment display. As we can see in the image below, we first need to wire each pin to a current limiting resistor of 330ohms before connecting it to the corresponding input pins of the 7-segment display. We must make sure that the A pin from the decoder is connected to the A pin of the 7-segment display. As you can also see, because we want to multiplex the two 7-segment displays, we connect both input pins of the 7-segment display together. For example, we would connect the A input of the left display to the A input of the right display. There is an 8th display pin called DP which stands for decimal point, and turns on the decimal point LED on the display. Since we are not using it, we do not need to wire it up.

Finally, we want to connect the common cathode pin of each 7-segment display to a seperate NMOS transistor each. The NMOS transistor works by closing the circuit between the source pin and the drain pin when the gate pin is HIGH (at 5V). Since we have connected the source to ground and the drain to the common cathode pin of the 7-segment display, when we make the gate pin HIGH in our Arduino code, we will display a number on the 7-segment display. We have implemented these two NMOS transistors so that we can keep both LOW unless we want to display a number, where we can selectively turn a 7-segment display on.

![image](https://user-images.githubusercontent.com/59899086/136716378-516e92b3-1fb5-4952-8dbe-001006cc6694.png)

**6. So, how is this README relevant to my project?** \
Well, this README will allow you to understand the methodology used to build the projects circuitry and understand the code to run the project. The code has comments that will allow you to be able to come back to this README and refresh your memory on how and why the code is written and structured.

**THANK YOU FOR READING!** You can find my Arduino project on TinkerCAD at this link: \
https://www.tinkercad.com/things/idn425qP1kW
