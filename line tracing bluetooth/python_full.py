from cvzone.HandTrackingModule import HandDetector
import cv2
from bluetest import arduino_bluetooth
import time

ard_blue_obj = arduino_bluetooth()

cam = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.7,maxHands=1)

while True:
    _,img = cam.read()

    hands,img = detector.findHands(img)
    if hands:
        fingers1 = detector.fingersUp(hands[0])
        add = sum(fingers1)  # [0,0,0,0,0]
        if(add == 0):
            ard_blue_obj.sendMsg("STOP ")
            print("stop")
        elif(add == 1 and fingers1[1] == 1):
            ard_blue_obj.sendMsg("FRONT ")
            print("FRONT")
        elif(add == 2 and fingers1[1] == 1 and fingers1[2] == 1):
            ard_blue_obj.sendMsg("RIGHT ")
            print("RIGHT")
        elif(add == 3 and fingers1[1] == 1 and fingers1[2] == 1 and fingers1[3] == 1):
            ard_blue_obj.sendMsg("LEFT ")
            print("LEFT")
        elif(add == 4 and fingers1[1] == 1 and fingers1[2] == 1 and fingers1[3] == 1 and fingers1[4] == 1):
            ard_blue_obj.sendMsg("BACK ")
            print("BACK")
        else:
            ard_blue_obj.sendMsg("Nothing ")
            print("nothing")
    else:
        ard_blue_obj.sendMsg("Nothing ")
        print("nothing")



    cv2.imshow('img',img)
    # cv2.imshow('hands',hands)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break