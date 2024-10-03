# 基板の仕様
ロボコンにおいて３人の選手が連携してロボットの非常停止を操作するための基板。
## 構成
- 遠隔非常停止基板
- 駆動系電源遮断基板
## 遠隔非常停止基板
### 部品
|用途|部品名|URL|
|:-:|:-:|:-:|
|BLE通信|XIAO ESP32C3|https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/|
### 入力
|用途|データ量|部品|
|:-:|:-:|:-:|
|チャンネル選択|2bit|DIPスイッチ|
|非常停止ボタン|1bit|XH2pin|
### 出力
|用途|データ量|部品|
|:-:|:-:|:-:|
|通信状況|1bit|青色LED|
|非常停止作動|1bit|[圧電ブザー](https://akizukidenshi.com/catalog/g/g109704/) & 黄色LED|
|バッテリー交換|1bit|赤色LED|