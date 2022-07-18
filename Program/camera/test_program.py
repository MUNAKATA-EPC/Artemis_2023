import sensor, image, time, math
from pyb import LED, Pin, Timer

# メモ
# pixels = 色取りをした範囲上にある色の面積
# area   = 色取りをした範囲の面積
# 必然的にpixelsのほうが値は小さくなる…はず。

threshold_for_court = (23, 76, -34, 0, -13, 30)   # コートの色取り用変数
threshold_for_goal  = (0, 100, -42, 127, 30, 127) # ゴールの色取り用変数
screen_center = [160, 120]                  # 画面の中央座標

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking

clock = time.clock()

timer = Timer(4, freq=1000)
port1 = timer.channel(1, Timer.PWM, pin=Pin("P7"))

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_cross(screen_center[0], screen_center[1])    # クロスヘアの表示

    #=======================変数定義ライン=======================

    read_count_court    =   0                               # コートの色を何度取ったかを代入する変数
    read_count_goal     =   0                               # ゴールの色を何度取ったかを代入する変数

    maxium_cx_court     =   0                               # コートの最大色取りサイズの中心x座標
    maxium_cy_court     =   0                               # コートの最大色取りサイズの中心y座標
    maxium_area_court   =   0                               # コートの最大色取りサイズのエリアサイズ

    maxium_cx_goal     =   0                                # ゴールの最大色取りサイズの中心x座標
    maxium_cy_goal     =   0                                # ゴールの最大色取りサイズの中心y座標
    maxium_area_goal   =   0                                # ゴールの最大色取りサイズのエリアサイズ

    court_deg           =   0                               # 画面中央からのコートの角度

    #=======================配列定義ライン=======================

    cx_court        =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心x座標保存用配列
    cy_court        =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心y座標保存用配列
    area_court      =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列

    cx_goal         =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # ゴールの中心x座標保存用配列
    cy_goal         =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # ゴールの中心y座標保存用配列
    area_goal       =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列

    #=======================コート色取りライン=======================

    for blob in img.find_blobs([threshold_for_court], pixels_threshold=200, area_threshold=200, merge=True):
        if read_count_court >= 9:              # コートの色を10回以上取った場合、それ以上コートの色取りをしない。
            break
        else:                                   # まだコートの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_court += 1

        cx_court[read_count_court] = blob.cx()
        cy_court[read_count_court] = blob.cy()
        area_court[read_count_court] = blob.area()

        img.draw_rectangle(blob.rect(), thickness=1)         # コートの色取り可能範囲の枠描画
        img.draw_cross(blob.cx(), blob.cy())    # コートの中心を交差線で描画
        img.draw_line(screen_center[0], screen_center[1], blob.cx(), blob.cy(), thickness=2)  # 画面中心からコート中心へのライン描画

    # コートの色取り値の内最大のものをコートとして扱う。
    maxium_area_court = (max(area_court[:]))

    for i in range(0, 9):
        if area_court[i] == maxium_area_court:
            maxium_cx_court = cx_court[i]
            maxium_cy_court = cy_court[i]
            break

    court_deg = math.atan2((maxium_cx_court - screen_center[0]), -(maxium_cy_court - screen_center[1]))
    if court_deg < 0:
        court_deg = (2 * math.pi) - abs(court_deg)
    court_deg = (math.floor(court_deg / (2 * math.pi) * 100))

    #==========================================================

    #=======================ゴール色取りライン=======================

    for blob in img.find_blobs([threshold_for_goal], pixels_threshold=200, area_threshold=200, merge=True):
        if read_count_goal >= 9:              # ゴールの色を10回以上取った場合、それ以上ゴールの色取りをしない。
            break
        else:                                   # まだゴールの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_goal += 1

        cx_goal[read_count_goal] = blob.cx()
        cy_goal[read_count_goal] = blob.cy()
        area_goal[read_count_goal] = blob.area()

        img.draw_rectangle(blob.rect(), thickness=4)         # ゴールの色取り可能範囲の枠描画
        img.draw_cross(blob.cx(), blob.cy())    # ゴールの中心を交差線で描画
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

    #==========================================================

    #=======================ポート出力ライン========================

    port1.pulse_width_percent(court_deg)

    #==========================================================
