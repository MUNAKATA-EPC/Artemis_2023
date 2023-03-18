#変更点
# 新基盤

import sensor, image, time, math#ライブラリーの読み込み
from pyb import UART, LED, Pin, Timer, DAC#ライブラリーの読み込み
from ulab import numpy as np


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 1000)

"""
red_led   = LED(1)                  #下２１行目までLEDのセットアップ
green_led = LED(2)
blue_led  = LED(3)
ir_led    = LED(4)

def led_control(x):
    if   (x&1)==0: red_led.off()
    elif (x&1)==1: red_led.on()
    if   (x&2)==0: green_led.off()
    elif (x&2)==2: green_led.on()
    if   (x&4)==0: blue_led.off()
    elif (x&4)==4: blue_led.on()
    if   (x&8)==0: ir_led.off()
    elif (x&8)==8: ir_led.on()
"""
threshold_index = 0 # 0 for red, 1 for green, 2 for blue

#########################################################################################################################
yoko_line = 124
tate_line = 120
#yoko_line2 = 100
#tate_line2 = 190

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
"""大会用
thresholds1 = [(0, 100, -12, 127, 36, 127)]#ボール
thresholds2 = [(42, 100, -128, -54, 37, 127)]#コート（緑色）
thresholds3 = [(31, 41, -33, -8, -128, 1)]#ゴール（青色）
thresholds4 = [(31, 100, -34, 4, 33, 127)]#ゴール（黄色）
"""
thresholds1 = [(28, 100, 26, 127, 8, 127)]#ボール
thresholds2 = [(31, 100, -128, -37, -128, 127)]#コート（緑色）
thresholds3 = [(0, 24, -128, 127, -128, -12)]#ゴール（青色）
thresholds4 = [(0, 100, -127, 23, 33, 127)]#ゴール（黄色）
uart = UART(3,115200, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
sensor.set_contrast(-3)#コントラスト
sensor.set_brightness(-3)#明るさ
sensor.set_saturation(0)#彩3~-3
sensor.skip_frames(time = 250)#描写速度
sensor.set_auto_exposure(False)
sensor.set_auto_whitebal(False,(-4,-4,0)) # must be turned off for color tracking,(-5.874588, -6.02073, -1.887871)
clock = time.clock()

tim1 = Timer(4, freq=1000)
ch1 = tim1.channel(1, Timer.PWM, pin=Pin("P7"))
ch2 = tim1.channel(2, Timer.PWM, pin=Pin("P8"))
ch3 = tim1.channel(3, Timer.PWM, pin=Pin("P9"))

while(True):
    h = 0
    i = 0
    j = 0
    k = 0
    blue_number = 0
    yellow_number = 0
    green_number = 0
    ball_number = 0
    count1 = 0
    count2 = 0
    count3 = 0
    count4 = 0
#########################################################################################################################
    MaxBall = 0
    MaxGreen = 0
    MaxBlue = 0
    MaxYellow = 0
#########################################################################################################################
    areaA    = np.array([0,0,0,0,0,0,0,0,0,0])#取得したブロックの面積を配列にして1つの関数に保存
    areaB    = np.array([0,0,0,0,0,0,0,0,0,0])
    areaC    = np.array([0,0,0,0,0,0,0,0,0,0])
    areaD    = np.array([0,0,0,0,0,0,0,0,0,0])
#########################################################################################################################
    rectA    = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標、Y座標、ブロックの横幅、縦幅の値を配列にして1つの関数に保存
    rectB    = [0,0,0,0,0,0,0,0,0,0]
    rectC    = [0,0,0,0,0,0,0,0,0,0]
    rectD    = [0,0,0,0,0,0,0,0,0,0]
#########################################################################################################################
    cxA      = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のX座標のみを配列にして1つの関数に保存
    cxB      = [0,0,0,0,0,0,0,0,0,0]
    cxC      = [0,0,0,0,0,0,0,0,0,0]
    cxD      = [0,0,0,0,0,0,0,0,0,0]
#########################################################################################################################
    cyA      = [0,0,0,0,0,0,0,0,0,0]#取得したブロック（ボール）の中心のY座標のみを配列にして1つの関数に保存
    cyB      = [0,0,0,0,0,0,0,0,0,0]
    cyC      = [0,0,0,0,0,0,0,0,0,0]
    cyD      = [0,0,0,0,0,0,0,0,0,0]
#########################################################################################################################
    rA2 = [0,0,0,0,0,0,0,0,0,0]
    rB2 = [0,0,0,0,0,0,0,0,0,0]
    rC2 = [0,0,0,0,0,0,0,0,0,0]
    rD2 = [0,0,0,0,0,0,0,0,0,0]
    radsA  = [0,0,0,0,0,0,0,0,0,0]#ｒによって出た角度を絶対値に
    radsAT  = [0,0,0,0,0,0,0,0,0,0]
    radsAB  = [0,0,0,0,0,0,0,0,0,0]
    radsB  = [0,0,0,0,0,0,0,0,0,0]
    radsBT  = [0,0,0,0,0,0,0,0,0,0]
    radsBB  = [0,0,0,0,0,0,0,0,0,0]
    radsC  = [0,0,0,0,0,0,0,0,0,0]
    radsCT  = [0,0,0,0,0,0,0,0,0,0]
    radsCB  = [0,0,0,0,0,0,0,0,0,0]
    radsD  = [0,0,0,0,0,0,0,0,0,0]
    radsDT  = [0,0,0,0,0,0,0,0,0,0]
    radsDB  = [0,0,0,0,0,0,0,0,0,0]
#########################################################################################################################
    distanceA = [0,0,0,0,0,0,0,0,0,0]
    distanceAT = [0,0,0,0,0,0,0,0,0,0]
    distanceAB = [0,0,0,0,0,0,0,0,0,0]
    distanceB = [0,0,0,0,0,0,0,0,0,0]
    distanceBT = [0,0,0,0,0,0,0,0,0,0]
    distanceBB = [0,0,0,0,0,0,0,0,0,0]
    distanceC = [0,0,0,0,0,0,0,0,0,0]
    distanceCT = [0,0,0,0,0,0,0,0,0,0]
    distanceCB = [0,0,0,0,0,0,0,0,0,0]
    distanceD = [0,0,0,0,0,0,0,0,0,0]
    distanceDT = [0,0,0,0,0,0,0,0,0,0]
    distanceDB = [0,0,0,0,0,0,0,0,0,0]
#########################################################################################################################
    valAx = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    valAy = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    valBx = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    valBy = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    valCx = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    valCy = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    valDx = [0,0,0,0,0,0,0,0,0,0]#画面中心のX座標
    valDy = [0,0,0,0,0,0,0,0,0,0]#画面中心のY座標
    absnum = [0,0,0,0,0,0,0,0,0,0]
    absnum2 = [0,0,0,0,0,0,0,0,0,0]
    touchColor = [0,0,0]
    touchIND = 0
#########################################################################################################################

    clock.tick()
    sensor.set_hmirror(True)
    img = sensor.snapshot()
#########################################################################################################################
#ボール色取り
    for blob in img.find_blobs([thresholds1[threshold_index]], pixels_threshold=2, area_threshold=1, merge=False,margin=25):#ボール色取り
        if h > 8:
            break
        else:
            h += 1
            cxA[h] = blob.cx()
            cyA[h] = blob.cy()
            rectA[h] = blob.rect()
            valAx[h] = blob.cx()-tate_line
            valAy[h] = blob.cy()-yoko_line
            rA2[h] = int(math.atan2(-valAy[h],-valAx[h])*1600)
            radsA[h] = rA2[h] +5024
            radsAT[h] = int(radsA[h]/100)
            radsAB[h] = int(radsA[h] - (radsAT[h]*100))
            distanceA[h] = int((math.sqrt((math.pow(valAx[h],2))+(math.pow(valAy[h],2))))*95)#２点間の距離の公式
            distanceAT[h] = int(distanceA[h]/100)
            distanceAB[h] = int(distanceA[h]-(distanceAT[h]*100))
            areaA[h] = blob.area()

    MaxBall = np.argmax(areaA)
    if areaA[MaxBall] != 0:
        img.draw_rectangle(rectA[MaxBall], color = [255,0,0])
        img.draw_cross(cxA[MaxBall], cyA[MaxBall], thickness = 1)
    else:
        radsAT[MaxBall] = 200
        radsAB[MaxBall] = 00
        distanceAT[MaxBall] = 200
        distanceAB[MaxBall] = 00
#########################################################################################################################
#緑色取り
    for blob in img.find_blobs([thresholds2[threshold_index]], pixels_threshold=30, area_threshold=1, merge=True,margin=5):
        if i > 8:
            break
        else:
            i += 1
            cxB[i] = blob.cx()
            cyB[i] = blob.cy()
            rectB[i] = blob.rect()
            valBx[i] = blob.cx()-tate_line
            valBy[i] = blob.cy()-yoko_line
            rB2[i] = int(math.atan2(-valBy[i],-valBx[i])*1600)
            radsB[i] = rA2[i] + 5024
            radsBT[h] = int(radsB[i]/100)
            radsBB[h] = int(radsB[i] - (radsBT[i]*100))
            distanceB[i] = int((math.sqrt((math.pow(valBx[i],2))+(math.pow(valBy[i],2))))*95)#２点間の距離の公式
            distanceBT[i] = int(distanceB[i]/100)
            distanceBB[i] = int(distanceB[i]-(distanceBT[i]*100))
            areaB[i] = blob.area()

    MaxGreen = np.argmax(areaB)
    if areaB[MaxGreen] != 0:
        img.draw_rectangle(rectB[MaxGreen], color = [0,255,0])
        img.draw_cross(cxB[MaxGreen], cyB[MaxGreen], thickness = 1)
    else:
        radsBT[MaxGreen] = 200
        radsBB[MaxGreen] = 00
        distanceBT[MaxGreen] = 200
        distanceBB[MaxGreen] = 00
#########################################################################################################################
#青色ゴール取り
    for blob in img.find_blobs([thresholds3[threshold_index]], pixels_threshold=5, area_threshold=1, merge=True,margin=3):
        if j > 8:
            break
        else:
            j += 1
            cxC[j] = blob.cx()
            cyC[j] = blob.cy()
            rectC[j] = blob.rect()
            valCx[j] = blob.cx()-tate_line
            valCy[j] = blob.cy()-yoko_line
            rC2[j] = int(math.atan2(-valCy[j],-valCx[j])*1600)
            radsC[j] = rC2[j] + 5024
            radsCT[j] = int(radsC[j]/100)
            radsCB[j] = int(radsC[j] - (radsCT[j]*100))
            distanceC[j] = int(math.sqrt((math.pow(valCx[j],2))+(math.pow(valCy[j],2)))*95)#２点間の距離の公式
            distanceCT[j] = int(distanceC[j]/100)
            distanceCB[j] = int(distanceC[j] - (distanceCT[j]*100))
            areaC[j] = blob.area()

    MaxBlue = np.argmax(areaC)
    if areaC[MaxBlue] != 0:
        img.draw_rectangle(rectC[MaxBlue], color = [0,0,255])
        img.draw_cross(cxC[MaxBlue], cyC[MaxBlue], thickness = 1)
    else:
        radsCT[MaxBlue] = 200
        radsCB[MaaxBlue] = 00
        distanceCT[MaxBlue] = 200
        distanceCB[MaxBlue] = 00
#########################################################################################################################
#黄色ゴール取り
    for blob in img.find_blobs([thresholds4[threshold_index]], pixels_threshold=10, area_threshold=1, merge=True,margin=5):
        if k > 8:
            break
        else:
            k += 1
            cxD[k] = blob.cx()
            cyD[k] = blob.cy()
            rectD[k] = blob.rect()
            valDx[k] = blob.cx()-tate_line
            valDy[k] = blob.cy()-yoko_line
            rD2[k] = int(math.atan2(-valDy[k],-valDx[k])*1600)
            radsD[k] = rD2[k] + 5024
            radsDT[k] = int(radsD[k]/100)
            radsDB[k] = int(radsD[k] - (radsDT[k]*100))
            distanceD[k] = int(math.sqrt((math.pow(valDx[k],2))+(math.pow(valDy[k],2)))*95)#２点間の距離の公式
            distanceDT[k] = int(distanceD[k]/100)
            distanceDB[k] = int(distanceD[k] - (distanceDT[k]*100))
            areaD[k] = blob.area()

    MaxYellow = np.argmax(areaD)
    if areaD[MaxYellow] != 0:
        img.draw_rectangle(rectD[MaxYellow], color = [255,255,0])
        img.draw_cross(cxD[MaxYellow], cyD[MaxYellow], thickness = 1)
    else:
        radsDT[MaxYellow] = 200
        radsDB[MaxYellow] = 00
        distanceDT[MaxYellow] = 200
        distanceDB[MaxYellow] = 00
#########################################################################################################################

    touchColor = img.get_pixel(100,125)
    touchColor = image.rgb_to_lab(touchColor)

    if (thresholds1[0][0] <= touchColor[0] <= thresholds1[0][1]) and (thresholds1[0][2] <= touchColor[1] <= thresholds1[0][3]) and (thresholds1[0][4] <= touchColor[2] <= thresholds1[0][5]) :
        touchIND = 1
    else:
        touchIND = 0

    uart.write(str(radsAT[MaxBall]))
    uart.write("a")
    uart.write(str(radsAB[MaxBall]))
    uart.write("b")
    uart.write(str(distanceAT[MaxBall]))
    uart.write("c")
    uart.write(str(distanceAB[MaxBall]))
    uart.write("d")
    uart.write(str(radsBT[MaxGreen]))
    uart.write("e")
    uart.write(str(radsBB[MaxGreen]))
    uart.write("f")
    uart.write(str(distanceBT[MaxGreen]))
    uart.write("g")
    uart.write(str(distanceBB[MaxGreen]))
    uart.write("h")
    uart.write(str(radsCT[MaxBlue]))
    uart.write("i")
    uart.write(str(radsCB[MaxBlue]))
    uart.write("j")
    uart.write(str(distanceCT[MaxBlue]))
    uart.write("k")
    uart.write(str(distanceCB[MaxBlue]))
    uart.write("l")
    uart.write(str(radsDT[MaxYellow]))
    uart.write("m")
    uart.write(str(radsDB[MaxYellow]))
    uart.write("n")
    uart.write(str(distanceDT[MaxYellow]))
    uart.write("o")
    uart.write(str(distanceDB[MaxYellow]))
    uart.write("p")
    uart.write(str(touchIND))
    uart.write("q")

#########################################################################################################################
    print(touchIND)
    #img.draw_line(0,yoko_line2,320,yoko_line2,[0,0,0])#横線
    #img.draw_line(tate_line2,0,tate_line2,240,[0,0,0])#縦線
    #img.draw_line(0,yoko_line,320,yoko_line)#横線
    #img.draw_line(tate_line,0,tate_line,240)#縦線

