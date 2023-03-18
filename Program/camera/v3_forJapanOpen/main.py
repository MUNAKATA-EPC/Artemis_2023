import sensor, image, time, math
from pyb import UART, LED, Pin, Timer

threshold_for_court = (27, 57, -36, 0, -7, 24)# コートの色取り用変数
threshold_for_goal_yellow = ((70, 90, -15, 13, 52, 82))# ゴールの色取り用変数(黄色)
threshold_for_goal_blue = (35, 51, -39, -18, -16, 10) # ゴールの色取り用変数(青色)
screen_center = [160, 120]                  # 画面の中央座標

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#カラースケール
sensor.set_framesize(sensor.QVGA)#解像度
timer = Timer(4, freq=1000)
sensor.set_contrast(0)#コントラスト
sensor.set_brightness(-2)#明るさ
sensor.set_saturation(2)#彩3~-3
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_exposure(False)
sensor.set_auto_whitebal(False,(-5.874588, -6.02073, -1.887871)) # must be turned off for color tracking,(-5.874588, -6.02073, -1.887871)

uart = UART(3, 112500, timeout_char=1000)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_cross(screen_center[0], screen_center[1])    # クロスヘアの表示

    #=======================変数定義ライン=======================

    read_count_court            =   0                               # コートの色を何度取ったかを代入する変数
    read_count_goal_yellow      =   0                               # 黄ゴールの色を何度取ったかを代入する変数
    read_count_goal_blue        =   0                               # 青ゴールの色を何度取ったかを代入する変数

    maximum_cx_court            =   0                               # コートの最大色取りサイズの中心x座標
    maximum_cy_court            =   0                               # コートの最大色取りサイズの中心y座標
    maximum_area_court          =   0                               # コートの最大色取りサイズのエリアサイズ

    maximum_cx_goal_yellow      =   0                               # 黄ゴールの最大色取りサイズの中心x座標
    maximum_cy_goal_yellow      =   0                               # 黄ゴールの最大色取りサイズの中心y座標
    maximum_area_goal_yellow    =   0                               # 黄ゴールの最大色取りサイズのエリアサイズ

    maximum_cx_goal_blue        =   0                               # 青ゴールの最大色取りサイズの中心x座標
    maximum_cy_goal_blue        =   0                               # 青ゴールの最大色取りサイズの中心y座標
    maximum_area_goal_blue      =   0                               # 青ゴールの最大色取りサイズのエリアサイズ

    court_deg                   =   0                               # 画面中央からのコートの角度
    court_distance              =   0                               # 画面中央からのコートの距離
    goal_yellow_deg             =   0                               # 画面中央からの黄ゴールの角度
    goal_yellow_distance        =   0                               # 画面中央からの黄ゴールの距離
    goal_blue_deg               =   0                               # 画面中央からの青ゴールの角度
    goal_blue_distance          =   0                               # 画面中央からの青ゴールの距離

    #=======================配列定義ライン=======================

    cx_court                    =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心x座標保存用配列
    cy_court                    =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの中心y座標保存用配列
    area_court                  =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # コートの色取りエリア保存用配列

    cx_goal_yellow              =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 黄ゴールの中心x座標保存用配列
    cy_goal_yellow              =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 黄ゴールの中心y座標保存用配列
    area_goal_yellow            =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 黄ゴールの色取りエリア保存用配列

    cx_goal_blue                =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 青ゴールの中心x座標保存用配列
    cy_goal_blue                =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 青ゴールの中心y座標保存用配列
    area_goal_blue              =   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]      # 青ゴールの色取りエリア保存用配列

    #=======================コート色取りライン=======================

    for blob in img.find_blobs([threshold_for_court], pixels_threshold=200, area_threshold=200, merge=True):
        if read_count_court >= 3:              # コートの色を10回以上取った場合、それ以上コートの色取りをしない。
            break
        else:                                   # まだコートの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_court += 1

        cx_court[read_count_court] = blob.cx()
        cy_court[read_count_court] = blob.cy()
        area_court[read_count_court] = blob.area()

    #=======================黄ゴール色取りライン=======================

    for blob in img.find_blobs([threshold_for_goal_yellow], pixels_threshold=20, area_threshold=20, merge=True):
        if read_count_goal_yellow + 1 >= 10:              # コートの色を10回以上取った場合、それ以上コートの色取りをしない。
            break
        else:                                   # まだコートの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_goal_yellow += 1

        cx_goal_yellow[read_count_goal_yellow] = blob.cx()
        cy_goal_yellow[read_count_goal_yellow] = blob.cy()
        area_goal_yellow[read_count_goal_yellow] = blob.area()

    #=======================青ゴール色取りライン=======================

    for blob in img.find_blobs([threshold_for_goal_blue], pixels_threshold=20, area_threshold=20, merge=True):
        if read_count_goal_blue + 1 >= 10:              # コートの色を10回以上取った場合、それ以上コートの色取りをしない。
            break
        else:                                   # まだコートの色取りが10回行われていない場合、読み取り回数を増やす。
            read_count_goal_blue += 1

        cx_goal_blue[read_count_goal_blue] = blob.cx()
        cy_goal_blue[read_count_goal_blue] = blob.cy()
        area_goal_blue[read_count_goal_blue] = blob.area()

    #==============================================

    maximum_cx_court = (max(cx_court[:]))
    maximum_cy_court = (max(cy_court[:]))
    maximum_area_court = (max(area_court[:]))

    for i in range(0, 9):
        if area_court[i] == maximum_area_court:
            maximum_cx_court = cx_court[i]
            maximum_cy_court = cy_court[i]
            break

    img.draw_cross(maximum_cx_court, maximum_cy_court)    # コートの中心を交差線で描画
    img.draw_line(screen_center[0], screen_center[1], maximum_cx_court, maximum_cy_court, thickness=2)  # 画面中心からコート中心へのライン描画

    #==============================================

    maximum_cx_goal_yellow = (max(cx_goal_yellow[:]))
    maximum_cy_goal_yellow = (max(cy_goal_yellow[:]))
    maximum_area_goal_yellow = (max(area_goal_yellow[:]))

    for i in range(0, 9):
        if area_goal_yellow[i] == maximum_area_goal_yellow:
            maximum_cx_goal_yellow = cx_goal_yellow[i]
            maximum_cy_goal_yellow = cy_goal_yellow[i]
            break

    #==============================================

    maximum_cx_goal_blue = (max(cx_goal_blue[:]))
    maximum_cy_goal_blue = (max(cy_goal_blue[:]))
    maximum_area_goal_blue = (max(area_goal_blue[:]))

    for i in range(0, 9):
        if area_goal_blue[i] == maximum_area_goal_blue:
            maximum_cx_goal_blue = cx_goal_blue[i]
            maximum_cy_goal_blue = cy_goal_blue[i]
            break

    #======================計算フェーズ=======================

    #==============================================

    court_deg = math.atan2((maximum_cx_court - screen_center[0]), (maximum_cy_court - screen_center[1]))
    if court_deg < 0:
        court_deg = (2 * math.pi) - abs(court_deg)
    court_deg = (math.floor(court_deg / (2 * math.pi) * 100))

    court_distance = math.sqrt(math.pow((maximum_cx_court - screen_center[0]), 2) + math.pow((maximum_cy_court - screen_center[1]), 2))

    #==============================================

    goal_deg_yellow = math.atan2((maximum_cx_goal_yellow - screen_center[0]), (maximum_cy_goal_yellow - screen_center[1]))
    if goal_deg_yellow < 0:
        goal_deg_yellow = (2 * math.pi) - abs(goal_deg_yellow)
    goal_deg_yellow = (math.floor(goal_deg_yellow / (2 * math.pi) * 90))

    if maximum_area_goal_yellow == 0:
        goal_deg_yellow = 100

    goal_distance_yellow = math.sqrt(math.pow((maximum_cx_goal_yellow - screen_center[0]), 2) + math.pow((maximum_cy_goal_yellow - screen_center[1]), 2)) - 50;

    #==============================================

    goal_deg_blue = math.atan2((maximum_cx_goal_blue - screen_center[0]), (maximum_cy_goal_blue - screen_center[1]))
    if goal_deg_blue < 0:
        goal_deg_blue = (2 * math.pi) - abs(goal_deg_blue)
    goal_deg_blue = (math.floor(goal_deg_blue / (2 * math.pi) * 90))

    if maximum_area_goal_blue == 0:
        goal_deg_blue = 100

    goal_distance_blue = math.sqrt(math.pow((maximum_cx_goal_blue - screen_center[0]), 2) + math.pow((maximum_cy_goal_blue - screen_center[1]), 2)) - 50;

    #==============================================

    #======================出力フェーズ=======================

    #uart.write(str(court_deg))
    #uart.write("a")
    #uart.write(str(court_distance))
    #uart.write("b")
    #uart.write(str(goal_deg_yellow))
    #uart.write("c")
    #uart.write(str(goal_distance_yellow))
    #uart.write("d")
    #uart.write(str(goal_deg_blue))
    #uart.write("e")
    #uart.write(str(goal_distance_blue))
    #uart.write("f")








