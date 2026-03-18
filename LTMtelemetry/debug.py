import serial
import time

# Config baudrate
ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)

# Waiting time
time.sleep(2)

# First plot
frames = ['$TSAAAAAA1', '$TSAAAAAA1']
for frame in frames:
    ser.write((plot + '\r\n').encode('ascii'))
    print(f"Send: {frame}")
    time.sleep(0.02)

time.sleep(2)

# Second frame sent 5 times
#frame2 = '$TGFFFFFFFFFFFFF'
frame2 = ['$TSAAAAAA1', '$TGFFFFFFFFFFFFF']
for i in range(80):
    for framein in frame2:
        ser.write((framein + '\r\n').encode('ascii'))
        print(f"Send: {framein}")
        time.sleep(0.02)
    # Close port
ser.close()
