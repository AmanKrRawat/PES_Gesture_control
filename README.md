# PES_Vis_Pow_Algo

Flash the boards with the project:

First connect the boards with the sensor and the OLED screen.

MPU6050 side:
•	In the terminal first go to the FOLDER in the project repo.
•	Run the west environment variables script in the terminal.
•	Type "west build -p auto -b nrf52840dk_nrf52840” and press enter. This will create the build folder in the project.
•	Now type “west flash” and press enter. This will start the flashing process. Wait for the flash to get over.
•	Open Putty and select the “serial” option and set the baudrate to 115200 and start the session. A black screen will open where you can see the logs of Bluetooth and check the sensed commands.

OLED side:
•	In the terminal first go to the FOLDER in the project repo.
•	Run the west environment variables script in the terminal.
•	Type "west build -p auto -b nrf52840dk_nrf52840” and press enter. This will create the build folder in the project.
•	Now type “west flash” and press enter. This will start the flashing process. Wait for the flash to get over.
•	Open Putty and select the “serial” option and set the baudrate to 115200 and start the session. A black screen will open where you can see the logs of Bluetooth.

Once both the boards are flashed you can press reset and see the project working.


To train the Machine learning model:
1.	Flash the sensor side board with this  code.
2.	Open the UART terminal and connect to COM port.
3.	Draw the shapes continuously for 20sec.
4.	Save the log in CSV file.
5.	In the python file change the file names to the ones which you saved.
6.	Run the script.
7.	Copy the window.h and classifier.h file generated in script folder to MPU6050_Embedded_project/src folder.
8.	Build the MPU6050_Embedded_project project again and flash it on sensor side.
