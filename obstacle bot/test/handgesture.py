from cvzone.HandTrackingModule import HandDetector
import cv2
from handgesture import arduino_bluetooth

ard_blue_obj = arduino_bluetooth()

cam = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.7, maxHands=1)

while True:
    _, img = cam.read()

    hands, img = detector.findHands(img)
    if hands:
        fingers1 = detector.fingersUp(hands[0])
        add = sum(fingers1)
        print(fingers1)

    cv2.imshow('img', img)
    # cv2.imshow('hands',hands)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break
