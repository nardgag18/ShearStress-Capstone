import time
from tkinter import *
from tkinter import messagebox

default_screen_dimensions = '750x500'

win = Tk() # creating the main window
win.geometry(default_screen_dimensions) # set the screen's dimensions
win.title('Home') # title of the screen

User_LowFlowRate_set = StringVar() # low flow rate variable to store user input
User_LowFlowRate_set.set('00') # display '00' in text field

User_HighFlowRate_set = StringVar() # high flow rate variable to store user input
User_HighFlowRate_set.set('00') # display '00' in text field

# timer variables
hour = StringVar()
minute = StringVar()
second = StringVar()

# set the variable's text boxes with '00'
hour.set('00')
minute.set('00')
second.set('00')

# Display "Time: " to the GUI home screen
timeLabel = Label(win, text='Time:', font=('Arial', 30, ""))
timeLabel.place(x=50, y=60) # place the time label on the GUI on location (50, 60)

# set the input boxes on the GUI
hourEntry = Entry(win, width=2, font=('Arial', 30, ""), textvariable=hour) # save entry in hour variable
hourEntry.place(x=135,y=60) # set the location of the button

hourLabel = Label(win, text='hours', font=('Arial', 30, ""))
hourLabel.place(x=180, y=60)

minuteEntry = Entry(win, width=2, font=('Arial', 30, ""), textvariable=minute) # save entry in minute variable
minuteEntry.place(x=260,y=60) # set the location of the button

minuteLabel = Label(win, text='minutes', font=('Arial', 30, ""))
minuteLabel.place(x=305,y=60)

secondEntry = Entry(win, width=2, font=('Arial', 30, ""), textvariable=second) # save entry in second variable
secondEntry.place(x=415,y=60) # set the location of the button

secondLabel = Label(win, text='seconds', font=('Arial', 30, ""))
secondLabel.place(x=460, y=60)

paused = False

def pauseTest(value) :
    global paused
    paused = value

def submit() :
    global paused
    resumed = False

    runningWindow = Toplevel(win)
    runningWindow.title('Operation running')
    runningWindow.geometry(default_screen_dimensions)

    # Display "Time: " to the GUI home screen
    timeLabel = Label(runningWindow, text='Time:', font=('Arial', 30, ""))
    timeLabel.place(x=50, y=60) # place the time label on the GUI on location (50, 60)

    # set the input boxes on the GUI
    hourEntry = Entry(runningWindow, width=2, font=('Arial', 30, ""), textvariable=hour) # save entry in hour variable
    hourEntry.place(x=135,y=60) # set the location of the button

    hourLabel = Label(runningWindow, text='hours', font=('Arial', 30, ""))
    hourLabel.place(x=180, y=60)

    minuteEntry = Entry(runningWindow, width=2, font=('Arial', 30, ""), textvariable=minute) # save entry in minute variable
    minuteEntry.place(x=260,y=60) # set the location of the button

    minuteLabel = Label(runningWindow, text='minutes', font=('Arial', 30, ""))
    minuteLabel.place(x=305,y=60)

    secondEntry = Entry(runningWindow, width=2, font=('Arial', 30, ""), textvariable=second) # save entry in second variable
    secondEntry.place(x=415,y=60) # set the location of the button

    secondLabel = Label(runningWindow, text='seconds', font=('Arial', 30, ""))
    secondLabel.place(x=460, y=60)

    # function to start the timer function on home screen
    try:
        # check if the input are numbers and create a variable to count down
        temp = int(hour.get()) * 3600 + int(minute.get()) * 60 + int(second.get())
    except:
        # if try didn't work, the input was wrong. Ask for user to put in the correct fields
        print("Please input the right value (Numbers only)")
    while (temp >- 1):
        global paused
        while not paused :
            print("counting")
            
            if resumed :
                print("destroying ")
                resumeBtn.destroy()
                resumed = False

            pauseBtn = Button(runningWindow, text='Pause', font=('Arial', 30, ""), command=lambda : pauseTest(True))
            pauseBtn.place(x=310, y=200)
            # while the timer is greater than 0
            mins, secs = divmod(temp, 60) # update the minutes and seconds on the GUI
            hours = 0
            if mins > 60: # update the hours on the GUI
                hours, mins = divmod(mins, 60)

            # format the numbers to be printed on the GUI
            hour.set("{0:2d}".format(hours))
            minute.set("{0:2d}".format(mins))
            second.set("{0:2d}".format(secs))

            # update the GUI
            runningWindow.update()

            # wait
            time.sleep(1)

            if(temp == 0):
                messagebox.showinfo("Time counting down ...", "Test Complete!")
            temp -= 1

        if paused :
            print('Paused')
            pauseBtn.destroy()
            resumeBtn = Button(runningWindow, text='Resume', font=('Arial', 30, ""), command=lambda : pauseTest(False))
            resumeBtn.place(x=300, y=200)
            runningWindow.update()
            time.sleep(1)
            resumed = True
            
def lowFlowRate() :
    # new window to get low flow rate input from user
    newWindow = Toplevel(win) # create new window variable that is a layer above the home window
    newWindow.title('Low Flow Rate') # name the window
    newWindow.geometry(default_screen_dimensions) # set the dimensions of the window
    
    # add a label to display "Low Flow Rate:" to the GUI
    LowFlowRateLabel = Label(newWindow, text='Low Flow Rate:', font=('Arial', 18, "")) 
    LowFlowRateLabel.place(x=20, y=80)
    
    # add a entry box to get the user's input and save in User_LowFlowRate_set
    LowFlowRateEntry = Entry(newWindow, width=3, font=('Arial', 18, ""), textvariable=User_LowFlowRate_set)
    LowFlowRateEntry.place(x=150,y=79)

def highFlowRate() :
    # new window to get high flow rate input from user
    newWindow = Toplevel(win) # create new window variable that is a layer above the home screen
    newWindow.title('High Flow Rate') # name the window
    newWindow.geometry(default_screen_dimensions) # set the dimensions of the window
    
    # add a lable to display "High Flow Rate:" to the GUI
    LowFlowRateLabel = Label(newWindow, text='High Flow Rate:', font=('Arial', 18, ""))
    LowFlowRateLabel.place(x=20, y=80)
    
    # add a entry box to get the user's input and save in User_HighFlowRate_set variable
    LowFlowRateEntry = Entry(newWindow, width=3, font=('Arial', 18, ""), textvariable=User_HighFlowRate_set)
    LowFlowRateEntry.place(x=150,y=79)    

# set a low flow rate button on the home screen
lowFR = Button(win, text="Low Flow Rate", font=('Arial', 30, ""), height=3, width=15, command=lowFlowRate)
lowFR.place(x=60,y=180) # place the button on the GUI

# set a high flow rate button on the home screen
highFR = Button(win, text="High Flow Rate", font=('Arial', 30, ""), height=3, width=15, command=highFlowRate)
highFR.place(x=400, y=180) # place the button on the GUI

# set a start button on the home screen
startBtn = Button(win, text="Start" , font=('Arial', 30, ""), height=3, width=10, command=submit)
startBtn.place(x=270, y = 350) # place the button on the GUI

win.mainloop() # start the screen