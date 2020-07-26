#!/usr/bin/python3
import jetson.inference
import jetson.utils

net = jetson.inference.detectNet("coco-bottle", threshold=0.5)
camera = jetson.utils.videoSource("rtsp://192.168.1.171", codec=h265)   
display = jetson.utils.videoOutput("rtp://192.168.1.144:5000") 

while display.IsStreaming():
	img = camera.Capture()
	detections = net.Detect(img)
	display.Render(img)

	for detection in detections:
		print(detection)

	display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))