# R3-SoftwareTask1-AnuramThirumoli
Arduino Uno program written for R3 Software Task 1. Displays a number between 0 and 99 to two 7-segment displays based on a potentiometers output/position. Uses multiplexing instead of using two CD4511 7-segment decoders.

![image](https://user-images.githubusercontent.com/59899086/136715278-7a5f7000-f508-4d3c-bbc4-877420445891.png)

**1. How is the project powered?** \
The project is powered through the Arduino Uno's built-in 5V output and its ground. There are wires (red for 5V and black for ground) connecting all the breadboards in the project to a common power and ground. It is important to have a common ground so that the project references the same point for voltage measurements.

**2. How is the potentiometer output measured by the Arduino Uno?** \
The potentiometer is connected to 5V and ground through its Terminal 1 and Terminal 2 pins. To measure the voltage of the potentiometer, the wiper pin is connected to the analog input port A0 on the Arduino Uno (using the green wire). We are using the A0 (analog) port instead of the digital ports because instead of the 0V and 5V the digital ports output, we want to know the voltage in the range from 0V to 5V. \
In order to convert the potentiometers output to a range from 0 to 99, we use Arduino's analogRead() and map() functions. In order to do this correctly, we must keep in mind that the analogRead() function returns a integer from 0 to 1023, with 0 being 0V and 1023 being 5V respectively. Therefore, we have to map the analogRead() function using the values 0 to 1023, to the values 0 to 99. The code to do this is given below:
```
int pot_range = map(analogRead(A0), 0, 1023, 0, 99);
```

**3. How is the rest of the project built?** \
Since I am using multiplexing to run the 7-segment displays, I only need to use one CD4511 decoder. This decoder uses Binary Coded Decimal to represent the numbers 0 to 9 using its binary equivalent (ex. the number 9 is the binary pattern 1001). Therefore, I need to use 4 digital pins and output HIGH and LOW using the binary pattern of the number I want to display to the CD4511 decoder. I do this by connecting the digital pins 8, 9, 10, and 11 from the Arduino Uno to the pin inputs 1, 2, 3, and 4 respectively.
