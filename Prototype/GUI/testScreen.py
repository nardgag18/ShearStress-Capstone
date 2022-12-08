from tkinter import *
from tkinter import messagebox
import serial
import time
import threading
import sys

serial1 = serial.Serial('/dev/cu.usbserial-01D17AE0', 9600)



default_screen_dimensions = '750x500'

startScreen = Tk()
startScreen.geometry(default_screen_dimensions)
startScreen.title('Start Screen')

motor_Rotations = IntVar()
motor_Rotations.set(0)

Temp = StringVar()
Temp.set('00')

Hum = StringVar()
Hum.set('00')

pumpOn = 0

win = Toplevel(startScreen) # creating the main window
win.geometry(default_screen_dimensions) # set the screen's dimensions
win.title('Running') # title of the screen

def controlPump() :
    global pumpOn
    if pumpOn == 0 :
        serial1.write(b'2')

        pumpOn = 1
    else :
        serial1.write(b'1')
        pumpOn = 0

def moveMotor() :
    global motor_Rotations
    
    sendCommand = ''
    if motor_Rotations.get() < 0 :
        # ccw
        val = str(motor_Rotations.get())
        val = val.replace('-', '')
        sendCommand = '4,' + val
    else :
        #cw
        sendCommand = '3,' + str(motor_Rotations.get())

    sendCommand = sendCommand.encode()
    serial1.write(sendCommand)
    time.sleep(1)
    motor_Rotations.set(0)

def compareMessage(buffer):
    compare = [
        ['>', ' ', 'W', 'a', 'i', 't', 'i', 'n', 'g', '.', '.', '.'],
        ['>', ' ', 'S', 'e', 'n', 's', 'o', 'r', ' ', 's', 'e', 't', 'u', 'p', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 't', 'e'],
        ['>', ' ', 'G', 'o', '!'],
        []
    ]
    index = 0
    for comp in compare :
        if comp == buffer :
            if index == 0 :
                print("WAITING")
                return 0
            if index == 1 :
                print("SETUP COMPLETE")
                return 1
            if index == 2 :
                print("GO!")
                return 2
            if index == 3 :
                print("SPACE")
                return 3        
        index += 1

    return 5 
#def sendCommand(data) :
    #if data == 5 :
        
def parseSensor(buffer) :
    size = 0
    string_Buffer = ''.join(buffer)
    x = string_Buffer.split("   ")
    
    sens_Hum = x[0]
    sens_Temp = x[1]

    humMessage = sens_Hum.split("=")
    tempMessage = sens_Temp.split("=")

    y = humMessage[1]
    z = tempMessage[1]

    yTemp = y.split("%")
    zTemp = z.split("d")

    hum_Val = yTemp[0]
    temp_Val = zTemp[0]
    
    hum_Val = int(hum_Val.strip())
    temp_Val = int(temp_Val.strip())

    Temp.set(temp_Val)
    Hum.set(hum_Val)

def getSerialMessage() :
    wait = True
    buffer = []
    index = 0
    threading.Timer(2.5, getSerialMessage).start()
    while wait :
        try:
            byteMessage = serial1.read()
            strMessage = byteMessage.decode()

            if (strMessage != '\n') and (strMessage != '\r') :
                buffer.append(strMessage)
                index+=1
            else :
                #print(buffer)
                data = compareMessage(buffer)
                
                if data == 5 :
                    # parse sensor reading from arduino
                    #print("parsing")
                    parseSensor(buffer)
                #else :
                    #sendCommand(data)
                #return data
                buffer.clear()
                wait = False
        except Exception as e :
            pass

def runOperation():
    #win = Toplevel(startScreen) # creating the main window
    #win.geometry(default_screen_dimensions) # set the screen's dimensions
    #win.title('Running') # title of the screen
    #global win
    win.lift()

    TempLabel = Label(win, text='Temperature:', font=('Arial', 30, ""))
    HumLabel = Label(win, text='Humidity:', font=('Arial', 30, ""))
    rotationsLabel = Label(win, text='rotations', font=('Arial', 30, ""))
    TempLabelLabel = Label(win, text=" degrees C.", font=('Arial', 30, ""))
    HumLabelLabel = Label(win, text="%", font=('Arial', 30, ""))

    TempEntry = Entry(win,width=3, font=('Arial', 30, ""), textvariable=Temp)
    HumEntry = Entry(win,width=3, font=('Arial', 30, ""), textvariable=Hum)

    motorRotationEntry = Entry(win, width=3, font=('Arial', 30, ""), textvariable=motor_Rotations)
    
    PumpButton = Button(win, text="Pump", font=('Arial', 30, ""), height=3, width=15, command=controlPump)
    MotorButton = Button(win, text="Move Motor", font=('Arial', 30, ""), height=3, width=15, command=moveMotor)

    TempLabel.place(x=50,y=60)
    HumLabel.place(x=50,y=100)
    rotationsLabel.place(x=120,y=300)
    TempEntry.place(x=235,y=58)
    HumEntry.place(x=178,y=100)
    TempLabelLabel.place(x=290, y=60)
    HumLabelLabel.place(x=240,y=100)
    motorRotationEntry.place(x=50,y=300)
    PumpButton.place(x=400,y=150)
    MotorButton.place(x=400,y=300)

    #time.sleep(5)
    win.update()

    serial1.write(b'1')
    time.sleep(1)

    getSerialMessage()


wait = True
buffer = []
index = 0
data = 0

while wait :
    byteMessage = serial1.read()
    strMessage = byteMessage.decode()

    if (strMessage != '\n') and (strMessage != '\r') :
        buffer.append(strMessage)
        index += 1
    else :
        print(buffer)
        data = compareMessage(buffer)
        buffer.clear()
        if data == 0 :
            wait = False
            startButton = Button(startScreen, text='Start', font=('Arial', 30, ""), height=3, width=15, command=runOperation)
            startButton.place(x=220,y=180)


startScreen.mainloop()