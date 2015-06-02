##Arduino LED matrix UI control
##Ben Katz, June 15, 2011
##www.build-its.blogspot.com


import  time, serial, random
from Tkinter import *
from PIL import ImageTk
height = 600
width = 1000

enabled = [1, 1, 1, 1, 1, 1, 1, 1, 1]   #This list cointains the state of each button: 1 = disabled, -1 = enabled

buttons = []

directions = [W, '', E, SE, SW, E, SW, S, SE]

canvas = Canvas(highlightthickness=0, height=height, width=width)
canvas.master.title("Project Clean")
canvas.configure(background='white')
canvas.grid()
canvas_id = canvas.create_text(10, 10, anchor="nw")
image = ImageTk.PhotoImage(file = "C:/Python27/Photos/bubbles.jpg")
canvas.create_image(100,100, image = image)

class Arduino:
    connection = None
    def __init__(self, path):
        self.connection = serial.Serial(path, 9600)      
        pass
    def __del__(self):
        self.connection.close()
        pass
    def isOpen(self):
        return self.connection.isOpen()
    def writeLine(self, line):
        if self.isOpen():
            self.connection.write(line)
            time.sleep(0.1)


arduino = Arduino(6)       #This sets the arduino to serial port 2.  On PC's this will probably be COM3
                           # On macs this port will be something like  /dev/tty.usbmodem
arduino.writeLine('!')     #The arduino program resets all the led's when it recieves '!' over serial

def ledWrite(i):
   print(i)
   arduino.writeLine(str(i))                     
   if enabled[i] == 1:
      buttons[i].configure(bg = 'aquamarine')      #Tkinter can take hexidecimal color codes, so you can customize your UI
   else:
      buttons[i].configure(bg = 'lightcyan')
   buttons[i].update()
   enabled[i] = enabled[i] * -1

#for i in range(9): 
        #this creates all the buttons, so you don't need a line to create and grid each button
x = 0	
i = Button(height = 8, width = 20,  bg = 'lightcyan', relief = GROOVE, text = "Regular Cycle", font=("Segoe Print", 12, "bold"), command = lambda arg=x: ledWrite(arg))    #'arg = x' may seem repetitive, but if it is not included,
                                                                                                               #the buttons pass the final value of x to 'ledWrite' , which is 8
i.grid(column = 0, row = 0, columnspan = 3, rowspan = 3, sticky = directions[x])
i.number = x
buttons.append(i)

x = 1
i = Button(height = 8, width = 20,  bg = 'paleturquoise', relief = GROOVE, text = "Super Cycle", font=("Segoe Print", 12, "bold"), command = lambda arg=x: ledWrite(arg))    #'arg = x' may seem repetitive, but if it is not included,
                                                                                                               #the buttons pass the final value of x to 'ledWrite' , which is 8
i.grid(column = 0, row = 0, columnspan = 3, rowspan = 3, sticky = directions[x])
i.number = x
buttons.append(i)

x = 2
i = Button(height = 8, width = 20,  bg = 'skyblue', relief = GROOVE, text = "Economy Rinse", font=("Segoe Print", 12, "bold"), command = lambda arg=x: ledWrite(arg))    #'arg = x' may seem repetitive, but if it is not included,
                                                                                                               #the buttons pass the final value of x to 'ledWrite' , which is 8
i.grid(column = 0, row = 0, columnspan = 3, rowspan = 3, sticky = directions[x])
i.number = x
buttons.append(i)

x = 3
i = Button(height = 6, width = 15, bg = 'lightseagreen', relief = SUNKEN, text = "RESET", font=("Segoe Print", 8, "bold"), command = lambda arg=x: ledWrite(arg))    #'arg = x' may seem repetitive, but if it is not included,
                                                                                                               #the buttons pass the final value of x to 'ledWrite' , which is 8
i.grid(column = 0, row = 0, columnspan = 3, rowspan = 3, sticky = directions[x])
i.number = x
buttons.append(i)




print '1'
canvas.mainloop()

arduino.writeLine('!')      #when you exit the UI, all the LED's are reset to 'off'
print '!'
arduino.connection.close()    #The serial connection is also closed when you quit, so you can switch between programming in python and the arduino IDE without resetting your arduino

