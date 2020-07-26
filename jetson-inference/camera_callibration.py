import cv2
import numpy as np

cap = cv2.VideoCapture("rtsp://192.168.1.171")

while True:
    _, frame = cap.read()
    blur_frame = cv2.GaussianBlur(frame, (5,5), 1)
    hsv_frame = cv2.cvtColor(blur_frame, cv2.COLOR_BGR2HSV)

    # Red color
    low_red = np.array([95,40,0])
    high_red = np.array([105, 255, 255])
    red_mask = cv2.inRange(hsv_frame, low_red, high_red)

    red_mask = cv2.bitwise_not(red_mask)

    kernal = np.ones((10,10), np.uint8)
    red_mask = cv2.dilate(red_mask, kernal)

    params = cv2.SimpleBlobDetector_Params()

    params.filterByArea = True
    params.minArea = 200
    params.maxArea = 1000

    params.filterByCircularity = True
    params.minCircularity = 0.1

    params.filterByConvexity = True
    params.minConvexity = 0.2

    params.filterByInertia = True
    params.minInertiaRatio = 0.1

    detector = cv2.SimpleBlobDetector_create(params)

    keypoints = detector.detect(red_mask)

    for keypoint in keypoints:
        x = keypoint.pt[0]
        y = keypoint.pt[1]
        print(str(x) + " -- " + str(y))

    imgKeyPoints = cv2.drawKeypoints(red_mask, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    cv2.imshow("Frame", blur_frame)

    #cv2.imshow("Red", red)

    cv2.imshow("Keypoints", imgKeyPoints)

    key = cv2.waitKey(1)
    if key == 27:
        break