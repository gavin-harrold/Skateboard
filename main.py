import cv2
import sys
import argparse
import serial
import time

#creates parser for arguments because I can I guess
parser = argparse.ArgumentParser(description="Testing stuff")
parser.add_argument('--face_cascade', help="Path to face cascade.", default="Lib\site-packages\cv2\data\haarcascade_frontalface_alt.xml")
args = parser.parse_args()

lastSeen = (0, 0)

#file
face_cascade_name = args.face_cascade

#creates cascade classifer out of face_cascade, uses file provided by library to determine what is face
face_cascade = cv2.CascadeClassifier()
#error handling, if file can't be loaded. doesn't handle file not existing
if not face_cascade.load(cv2.samples.findFile(face_cascade_name)):
    print("--(!)Error loading face cascade")
    exit(0)
#cascPath = sys.argv[1]
#faceCascade = cv2.CascadeClassifier(cascPath)


video_capture = cv2.VideoCapture(0)

#serial stuff - currently having technical difficulties, still sometimes crashes
arduino = serial.Serial('COM3', 9600)
time.sleep(2)
print("Connected to arduino...")

count = 0

#loop that runs forever, ie. every frame
while True:
    ret, frame = video_capture.read()

#works better for some reason HAAR classifier
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.equalizeHist(gray)

#detects faces
    faces = face_cascade.detectMultiScale(gray)
#loops through faces and draws rectangle around it
    for(x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        lastSeen = (x+w/2, y+h/2)
        #send info to arduino, resets not found counter to 0
        arduino.write('f'.encode())
        count = 0

        #debug
        print("found")

#displays video with title "Video"
    cv2.imshow("Cool people only", frame)

    #debug
    print("no face found")
    #checks to see if no face has been found for two instants, 
    count += 1
    if count >= 2:
        if(lastSeen[0] >= (video_capture.get(cv2.CAP_PROP_FRAME_WIDTH))/2):
            arduino.write('l'.encode())
            print("l")
        elif(lastSeen[0] < (video_capture.get(cv2.CAP_PROP_FRAME_WIDTH))/2):
            arduino.write('r'.encode())
            print("r")
        #arduino.write('n'.encode())

#breaks program, normal x doesn't work
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

#die die die
video_capture.release()
cv2.destroyAllWindows()
arduino.write('n'.encode())