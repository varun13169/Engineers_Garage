#Surveillance Car Controlled via DTMF

##Requirements:
* DTMF decoder module
* 3.5mm audio cable (for connecting mobile to DTMF module)
* Arduino Uno
* Chassis
* Servo motor (7 kg/cm)
* Android Phone(In my case Galaxy Ace Duos)
* Laptop(can be desktop or any android device supporting multi windows)
* Geared DC motors with Wheels
* L298 motor driver module
* Android apps  [AirDroid], [DTMF Tone Generator], [VNC server]
* Applications on laptop [VNC client] and [Browser] 

##Summary:

I made this project in order to build a surveillance car which can be controlled over Internet or on any private network. My objective was to **easily and cost effectively** do something that can be used for security purposes.

My car uses uses DTMF module which takes it’s input from mobile phone attached to the car, that mobile is not only used to generate DTMF tones but also for the **surveillance by providing Live Footage from it’s camera**, over the network using [AirDroid].

Conventionally, any project using DTMF requires call from another cell phone to the one attached to the project, **which is not cost effective**, but in case of my project I used an android app [DTMF Tone Generator] which generates DTMF tone now for this to work I shared my phone’s screen over the network using [VNC server], **hence cost effective**.

To make this Idea more effective I mounted the phone on a servo motor. This gave my Camera one degree of freedom, i.e. I can move it left and right without moving the bot.
    
Generally, there is **one more security problem involved with DTMF** that I took care of was that anyone can control the bot by calling the mobile phone attached to the bot. A simple solution to this problem is to apply a PIN using DTMF tones. I demonstrated this concept in the video and for the inner working you can check the source code.

Advantages:
* Far much more cheaper than the bluetooth and Wifi modules, with almost Identical working.
* Can be controlled via Internet using VPN.

Utilities:
* one can efficiently keep track on activities in his/her house when there are no occupants.
* It can be used for surveillance purposes in Dangerous areas where there is any kind of threat to human life.



##Project's Video
[https://www.youtube.com/watch?v=ecWZbtY6rOI]


##Circuit Diagram:
![alt text][circuit diagram]

##Description:
###Explanation of circuit and hardware components:
I used DTMF decoder module using MT8870DE and connected it to arduino as shown in circuit diagram. I pulled up pin13 permanently so as to provide +5v to the module. As can be seen D1-D4 are connected to pin12-pin9 respectively, here D1 represents least significant bit and D4 represents most significant bit. Pin8 of arduino is connected to STD pin of DTMF module, it becomes high whenever a new signal(valid tone) is given to module.
Tones were generated via mobile phone and were fed as input to DTMF decoder module using 3.5mm audio jack.

For motor driver I used L298D module here M11, M12 and M21, M22 are connection for LEFT and RIGHT motor respectively, when car is seen from back to front, when M11=M21=HIGH and M12=M22=LOW car will move forward. With this information you can easily use my source code directly by changing your connection respectively.
PWM1 and PWM2 are the pins which can be used to control left and right motor's speed. I set both of them HIGH in order to attain maximum speed. EN1 and EN2 enables left and right motor when set high, so I shorted them with +5v supply from arduino.
    Vcc for DC motors was connected from a +12v supply.

Phone was mounted on servo motor. Data pin of servo was connected to pin5 and +5v was taken from +5v supply and not from arduino as the current drawn by servo motor that I used exceeded the maximum current that could have been drawn from arduino.


###Explanation and working of peripheral applications used:
First of all I connected my laptop and my mobile phone to the same network.

I used [DTMF Tone Generator] to generate DTMF tones. This application was running on my mobile phone.

Now in order share the display and gain control over my mobile phone from my laptop I created a VNC server by running [VNC server] application on my phone in background and using [VNC client] on my laptop, now I was able to view my mobile phone's screen and simulated touches from my laptop.
At this point I was able to generate DTMF tones from my mobile phone using my laptop, therefore I was able to control my car using my laptop.
    
To get the live feed from my phone's camera I used [AirDroid] application, which was running in background alongside [VNC server] and using any browser(preferably Chrome) on my laptop I was able to use the camera of my phone.
          
Source code is well documented therefore all the required explanation is given as comments.



##Possible Modifications:
* Instead of being on the same network one can control it via internet from any part of the world using VPN.
* One can use any tablet or phone which supports multi window instead of laptop, as the only required application on my laptop were VNC client and a web browser both of them are available for android, ios, windows and Linux.
* One can control the speed of vehicle by connecting PWM1 and PWM2 to pwm pins of arduino and by making necessary changes in source code.
* If only maximum speed is required L293D can be used instead of L298, which might in turn save some bucks


##An extension of this project:
I tethered wifi from the phone mounted on the vehicle, thereby creating a local network. Now I was able to control my vehicle without the need of an external router or internet. Although I wasn’t able to get the live feed as Airdroid need internet connection to initialize.

Video: [https://www.youtube.com/watch?v=QwP7BD6L834]



[AirDroid]: https://play.google.com/store/apps/details?id=com.sand.airdroid&hl=en-GB
[DTMF Tone Generator]: https://play.google.com/store/apps/details?id=com.amknott.ToneGen&hl=en-GB
[VNC server]: https://play.google.com/store/apps/details?id=com.schumi.vncs&hl=en-GB
[VNC client]: https://www.realvnc.com/
[Browser]: http://www.google.com/chrome/
[circuit diagram]: https://github.com/varun13169/Engineers_Garage/blob/master/Surveillance%20Car%20Controlled%20via%20DTMF/circuit%20diagram.jpg "circuit diagram"
[https://www.youtube.com/watch?v=ecWZbtY6rOI]: https://www.youtube.com/watch?v=ecWZbtY6rOI
[https://www.youtube.com/watch?v=QwP7BD6L834]: https://www.youtube.com/watch?v=QwP7BD6L834
