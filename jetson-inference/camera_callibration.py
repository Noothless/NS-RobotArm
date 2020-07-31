#!C:/Python27/python.exe
import cv2
import numpy as np
import scipy as sp
import scipy.interpolate
import enum

cap = cv2.VideoCapture("rtsp://192.168.1.171")
#cv2.VideoCapture.set(CV_CAP_PROP_FRAME_WIDTH , double width)
#cv2.VideoCapture.set(CV_CAP_PROP_FRAME_HEIGHT , double height)

v=np.array([273,327,378,445,490,555,602,700,800,900,1000,1100,1200,1300,1350])
t=np.array([702,584,505,430,389,344,316,274,241,213,192 ,172, 158, 145, 140])
c_points = np.array
i_points = np.array([[0, 0, 0], [0, 130, 0], [130, 0, 0], [130, 130, 0]])

def dist_to_camera(dist):
    tnew=np.arange(start=702,stop=140,step=-1)
    fvcubic=sp.interpolate.interp1d(t,v,kind='cubic')
    vcubic=fvcubic(tnew)
    return int(vcubic[int(702-dist)])

while True:
    _, frame = cap.read()
    blur_frame = cv2.GaussianBlur(frame, (5,5), 1)
    hsv_frame = cv2.cvtColor(blur_frame, cv2.COLOR_BGR2HSV)

    # Red color
    low_red = np.array([90,90,0])
    high_red = np.array([115, 255, 255])
    red_mask = cv2.inRange(hsv_frame, low_red, high_red)

    red_mask = cv2.bitwise_not(red_mask)

    kernal = np.ones((10,10), np.uint8)
    red_mask = cv2.dilate(red_mask, kernal)

    params = cv2.SimpleBlobDetector_Params()

    params.filterByArea = True
    params.minArea = 50
    params.maxArea = 10000

    params.filterByCircularity = True
    params.minCircularity = 0.1

    params.filterByConvexity = True
    params.minConvexity = 0.2

    params.filterByInertia = True
    params.minInertiaRatio = 0.1

    detector = cv2.SimpleBlobDetector_create(params)

    keypoints = detector.detect(red_mask)

    if len(keypoints) == 4:
        x = [keypoints[0].pt[0], keypoints[1].pt[0], keypoints[2].pt[0], keypoints[3].pt[0]]
        x.sort()
        for i in range(4):
            for f in range(4):
                if x[i] == keypoints[f].pt[0]:
                    xa = np.array([[keypoints[f].pt[0], keypoints[f].pt[1]]])
                    if(i == 0):
                        c_points = xa
                    else:
                        c_points = np.append(c_points, xa, axis = 0)
                    #print(str(c_points[f]))
                    break
        #print("original:")
        #print(c_points)
         
        if c_points[0,1] > c_points[1,1]:
            c_points[[0,1],:] = c_points[[1,0],:]

        if c_points[2,1] > c_points[3,1]:
               c_points[[2,3],:] = c_points[[3,2],:]

        #print("sorted:")
        #print(c_points)

        for i in range(4):
            st = ['1', '2', '3', '4']
            x = int(c_points[i,0])
            y = int(c_points[i,1])
            font = cv2.FONT_HERSHEY_SIMPLEX
            cv2.putText(red_mask,st[i],(x,y), font, 4,(10,10,10),2,cv2.LINE_AA)
        


    imgKeyPoints = cv2.drawKeypoints(red_mask, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    #imgKeyPoints = cv2.drawKeypoints(blur_frame, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
 
    #font = cv2.FONT_HERSHEY_SIMPLEX
    #cv2.putText(red_mask,'1',(int(c_points[0,0]),int(c_points[0,1])), font, 4,(50,50,50),2,cv2.LINE_AA)

    cv2.imshow("Frame", blur_frame)

    #cv2.imshow("Red", red)

    cv2.imshow("Keypoints", imgKeyPoints)

    key = cv2.waitKey(1)
    if key == 27:
        print("---------------------")
        #print(values)
        break
    elif key == 13:
        print(c_points)
        