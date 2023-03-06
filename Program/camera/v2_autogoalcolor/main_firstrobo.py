import sensor, image, time, math

from pyb import LED, Pin, Timer

# メモ
# pixels = 色取りをした範囲上にある色の面積
# area   = 色取りをした範囲の面積
# 必然的にpixelsのほうが値は小さくなる…はず。

threshold_for_court = (22, 57, -37, -5, 18, 42)# コートの色取り用変数
threshold_for_goal_yellow = (64, 78, 14, 46, 57, 86)# ゴールの色取り用変数(黄色)
threshold_for_goal_blue = (35, 51, -39, -18, -16, 10) # ゴールの色取り用変数(青色)
threshold_for_goal = threshold_for_goal_blue #ゴールの最終色取り変数
screen_center = [134, 120]                  # 画面の中央座標
red_led = LED(1);
green_led = LED(2);
blue_led = LED(3);

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
timer = Timer(4, freq=1000)
sensor.set_contrast(0)#コントラスト
sensor.set_brightness(-2)#明るさ
sensor.set_saturation(2)#彩3~-3
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_exposure(False)
sensor.set_auto_whitebal(False,(-5.874588, -6.02073, -3.887871)) # must be turned off for color tracking,(-5.874588, -6.02073, -1.887871)


clock = time.clock()

port1 = timer.channel(1, Timer.PWM, pin=Pin("P7"))
port2 = timer.channel(2, Timer.PWM, pin=Pin("P8"))
port3 = timer.channel(3, Timer.PWM, pin=Pin("P9"))

decide_court_color = 0
waittimer = 0

read_areaofblue = 0
read_areaofyellow = 0

while(True):
    clock.tick()
    img = sensor.snapshot()

    img.draw_cross(screen_center[0], screen_center[1])    # クロスヘアの表示

    waittimer = waittimer + 1

    #=======================変数定義ライン=======================

    read_count_court    =   0                               # コートの色を何度取ったかを代入する変数
    read_count_goal     =   0                               # ゴールの色を何度取ったかを代入する変数

    maxium_cx_court     =   0                               # コートの最大色取りサイズの中心x座標
    maxium_cy_court     =   0                               # コートの最大色取りサイズの中心y座標
    maxium_area_court   =   0                               # コートの最大色取りサイズのエリアサイズ

    maxium_cx_goal      =   0                               # ゴールの最大色取りサイズの中心x座標
    maxium_cy_goal      =   0                               # ゴールの最大色取りサイズの中心y座標
    maxium_area_goal    =   0                               # ゴールの最大色取りサイズのエリアサイズ

    court_deg           =   0                               # 画面中央からのコートの角度
    goal_deg            =   0                               # 画面中央からのゴールの角度
    goal_distance       =   0                               # 画面中央からのゴールの距離

    #=======================配列定義ライン=======================

    cx_court        =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心x座標保存用配列
    cy_court        =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心y座標保存用配列
    area_court      =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列

    cx_goal         =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # ゴールの中心x座標保存用配列
    cy_goal         =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # ゴールの中心y座標保存用配列
    area_goal       =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列
    area_goal_sub       =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列

    #=======================コート色取りライン=======================

    for blob in img.find_blobs([threshold_for_court], pixels_threshold=200, area_threshold=200, merge=True):
        if read_count_court >= 3:              # コートの色を10回以上取った場合、それ以上コートの色取りをしない。
            break
        else:                                   # まだコートの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_court += 1

        cx_court[read_count_court] = blob.cx()
        cy_court[read_count_court] = blob.cy()
        area_court[read_count_court] = blob.area()

        #img.draw_rectangle(blob.rect(), thickness=1)         # コートの色取り可能範囲の枠描画
        img.draw_cross(blob.cx(), blob.cy())    # コートの中心を交差線で描画
        img.draw_line(screen_center[0], screen_center[1], blob.cx(), blob.cy(), thickness=2)  # 画面中心からコート中心へのライン描画

    # コートの色取り値の内最大のものをコートとして扱う。
    maxium_area_court = (max(area_court[:]))

    for i in range(0, 9):
        if area_court[i] == maxium_area_court:
            maxium_cx_court = cx_court[i]
            maxium_cy_court = cy_court[i]
            break

    court_deg = math.atan2((maxium_cx_court - screen_center[0]), (maxium_cy_court - screen_center[1]))
    if court_deg < 0:
        court_deg = (2 * math.pi) - abs(court_deg)
    court_deg = (math.floor(court_deg / (2 * math.pi) * 100))

    #==========================================================

    #=======================ゴール色取りライン=======================

    for blob in img.find_blobs([threshold_for_goal], pixels_threshold=20, area_threshold=20, merge=True):
        if read_count_goal >= 5:              # ゴールの色を10回以上取った場合、それ以上ゴールの色取りをしない。
            break
        else:                                   # まだゴールの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_goal += 1

        cx_goal[read_count_goal] = blob.cx()
        cy_goal[read_count_goal] = blob.cy()
        area_goal[read_count_goal] = blob.area()

        img.draw_rectangle(blob.rect(), thickness=1)         # コートの色取り可能範囲の枠描画
        img.draw_cross(blob.cx(), blob.cy())    # コートの中心を交差線で描画
        img.draw_line(screen_center[0], screen_center[1], blob.cx(), blob.cy(), thickness=2)  # 画面中心からコート中心へのライン描画


    # コートの色取り値の内最大のものをコートとして扱う。
    maxium_cx_goal = (max(cx_goal[:]))
    maxium_cy_goal = (max(cy_goal[:]))
    maxium_area_goal = (max(area_goal[:]))

    for i in range(0, 9):
        if area_goal[i] == maxium_area_goal:
            maxium_cx_goal = cx_goal[i]
            maxium_cy_goal = cy_goal[i]
            break

    goal_deg = math.atan2((maxium_cx_goal - screen_center[0]), (maxium_cy_goal - screen_center[1]))
    if goal_deg < 0:
        goal_deg = (2 * math.pi) - abs(goal_deg)
    goal_deg = (math.floor(goal_deg / (2 * math.pi) * 90))

    if maxium_area_goal == 0:
        goal_deg = 100

    goal_distance = math.sqrt(math.pow((maxium_cx_goal - screen_center[0]), 2) + math.pow((maxium_cy_goal - screen_center[1]), 2)) - 50;


    if waittimer >= 50:
        if decide_court_color == 0:
            read_count_goal = 0
            for blob in img.find_blobs([threshold_for_goal_yellow], pixels_threshold=10, area_threshold=10, merge=True):
                if read_count_goal >= 9:              # ゴールの色を10回以上取った場合、それ以上ゴールの色取りをしない。
                    break
                else:                                   # まだゴールの色取りが10回行われていない場合、読み取り回数を増やす。
                    read_count_goal += 1

                area_goal[read_count_goal] = blob.area()

            read_areaofyellow = (max(area_goal[:]))

            print(read_areaofyellow)

            read_count_goal = 0
            for blob in img.find_blobs([threshold_for_goal_blue], pixels_threshold=20, area_threshold=20, merge=True):
                if read_count_goal >= 9:              # ゴールの色を10回以上取った場合、それ以上ゴールの色取りをしない。
                    break
                else:                                   # まだゴールの色取りが10回行われていない場合、読み取り回数を増やす。
                    read_count_goal += 1

                area_goal[read_count_goal] = blob.area()

            read_areaofblue = (max(area_goal[:]))

            print(read_areaofblue)

            if read_areaofblue >= read_areaofyellow:
                threshold_for_goal = threshold_for_goal_yellow
                decide_court_color = 100
                red_led.on()
                green_led.on()
                time.sleep_ms(500)
                red_led.off()
                green_led.off()

            if read_areaofyellow > read_areaofblue:
                threshold_for_goal = threshold_for_goal_blue
                decide_court_color = 100
                blue_led.on()
                time.sleep_ms(500)
                blue_led.off()



    #==========================================================

    #=======================ポート出力ライン========================

    port1.pulse_width_percent(court_deg)
    port2.pulse_width_percent(goal_deg)
    port3.pulse_width_percent(int(goal_distance))

    print(court_deg)

    #==========================================================
