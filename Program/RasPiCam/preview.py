from picamera import PiCamera
import time
with PiCamera(sensor_mode=4) as camera:
    camera.resolution = (1664, 1232)
    camera.start_preview()
    time.sleep(100)
    camera.stop_preview()
