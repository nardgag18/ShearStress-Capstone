import serial
import time

serial1 = serial.Serial('/dev/cu.usbserial-01D17AE0', 9600)

def compareMessage(message) :
    compare = [
        ['>', ' ', 'W', 'a', 'i', 't', 'i', 'n', 'g', '.', '.', '.'],
        ['>', ' ', 'G', 'o', '!']
    ]
    index = 0
    for comp in compare :
        if comp == message :
            if index == 0 :
                return 0
            if index == 1 :
                return 1
            
        index += 1

def getSerialMessage() :
    wait = True
    buffer = []
    index = 0

    while wait :
        byteMessage = serial1.read()
        strMessage = byteMessage.decode()

        if (strMessage != '\n') and (strMessage != '\r') :
            buffer.append(strMessage)
            index+=1
        else :
            print(buffer)
            data = compareMessage(buffer)
            buffer.clear()
            wait = False
            return data

def main() :
    completedSetup = False
    runningOp = False

    while True :
        data = getSerialMessage()
        if data == 0 :
            print("WAITING!!!!")
            serial1.write(b'1')
            time.sleep(1) 
            completedSetup = True
        if data == 1 :
            print("GO!!!")
            runningOp = True
            serial1.write(b'1')
            time.sleep(1)
            
    
main()