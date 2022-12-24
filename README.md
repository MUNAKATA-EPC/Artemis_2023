# 宗中アルテミス
宗中アルテミスのプログラムやファイル等を共有するためのリポジトリです。

## 目標とか
### 来季の全国大会へ向けたロボットの制作。
* これに関しては下記。

### チーム全体の技術力向上
* ハードウェア、ソフトウェアの両方ともをチーム全体が把握し、誰もが修正・加筆できるようにする。
* [Fusion 360](https://www.autodesk.co.jp/products/fusion-360/overview) や [KiCad](https://www.kicad.org/) などの部内に設置されている機械を使いこなし、後輩に繋いでいくのが最終目標。

## ロボットの概要
### 1号機(Artemis)
* メインマイコン：Arduino Mega 2560
* サブマイコン：Seeeduino Xiao(ジャイロ制御用)
* モータードライバ：4chモータードライバ
* モーター：ジョンミンモーター x4
* IRセンサー：12個(円形)
* ラインセンサー：円形、並列
* ジャイロセンサー：MPU6050
* カメラ：OpenMV H7
* 電源：Lipo 2cell(7.4V, 2200mAh)

### 2号機(Aporon)
* メインマイコン：TJ3B Loader 2620
* サブマイコン：Seeeduino Xiao(ジャイロ制御用)
* モータードライバ：4chモータードライバ
* モーター：ジョンミンモーター x4
* IRセンサー：12個(円形)
* ラインセンサー：円形、並列
* ジャイロセンサー：MPU6050
* カメラ：OpenMV H7 or Pixy
* 電源：Lipo 2cell(7.4V, 2200mAh)

## 進捗状況
- [ ] 設計
- [ ] ロボット本体制作
- [ ] メイン基板制作
- [ ] IR Ring 制作
- [ ] Line Ring 制作
- [ ] ジャイロセンサー制作
- [ ] 4chモータードライバの駆動
- [ ] メインプログラム作成 (←一番大変)
- [ ] 電源統合基盤

## 使用ライブラリ
> DSR1202.cpp / anbara
