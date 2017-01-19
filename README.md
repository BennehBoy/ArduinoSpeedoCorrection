# ArduinoSpeedoCorrection
Arduino based speedo correction for ABS vehicles, with optional 2nd channel final drive correction  

Based upon the 1986 944 Turbo Speedometer Calibrator written by Tom M'Guinness  

http://members.rennlist.com/tom86951/Speedometer%20Calibrator%20Page1.html

Code kindly used here with consent from Tom.

# Goal
This project aims to provide a cheap means to transform PWM speedo signals (VSS) from Land Rover TD5 SLABS units so that:  
1) Vehicles with larger than standard tyres can have a corrected speedo which does not under report  
2) Vehicles which have significantly altered drivetrain ratios can still utilise cruise control.  (The factory ECU prevents cruise control from working if a calculated vehicle speed, based upon crank, speed differs from the VSS by ~ > 10%.  

# Status
In development, research of VSS waveform underway.

# License

The source code of this project are released under "THE BEER-WARE" license.

I would, however, consider it a great courtesy if you could email me and tell me about your project and how this code was used, just for my own continued personal gratification :)

# Contribution

Contributions in all forms (including documentation) are welcomed. If you would like to contribute to this project, then just fork it in github and send a pull request.




