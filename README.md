# GN10RemoteEmergencyStop
Gento Aibaが作成する遠隔非常停止と電源遮断ユニットです。

## 遠隔非常停止

遠隔非常停止ボタン用の通信ユニットで、RNBD451によるBLE通信を用いる。
MCUにはSTM32F303K8T6を用い、RNBD451との間にはUARTのインターフェイスを用いる。
チャンネルは4つあり、2pinのDIPスイッチによって選択できる。

## 電源遮断ユニット

2系統の電源遮断を行うユニットで、それぞれ10Aと30Aの最大電流に対応している。
遮断と同時に抵抗で放電を行う。そのため、非常停止作動後コンデンサの電荷によってロボットが動作してしまうことを防止できる。
外部スイッチの入力は2つ、RNBD451によるBLEの通信を介した遠隔非常停止が有効である。

- [KiCAD](power_cutoff_unit)
- [使用部品](docs/power_cuttoff_unit_parts.md)
- [STM32F303K8T6で実装した場合のファームウェア](power_cutoff_unit/firmware/F303)
- [STM32G431K8T6で実装した場合のファームウェア](power_cutoff_unit/firmware/G431)

### 電源

|電源種類|基板上の名称|電圧範囲|最大電流|
|:-:|:-:|:-:|:-:|
|制御系電源|LogicPower|4~35V|2A|
|CAN通信電源|CAN(5V)|4.5~5.5V|0.1A|
|駆動系電源１|INPUT(30A) or OUTPUT(30A)|0~35V|30A|
|駆動系電源２|INPUT(10A) or OUTPUT(10A)|0~35V|10A|

### インジケーター

|部品|色|個数|内容|説明|
|:-:|:-:|:-:|:-:|:-:|
|LED|白|1|LogicPower|電源直結|
|LED|白|1|CAN(5V)|電源直結|
|LED|白|1|INPUT(30A)|入力側電源直結|
|LED|白|1|INPUT(10A)|入力側電源直結|
|LED|赤|1|OUTPUT(30A)|出力側電源直結|
|LED|赤|1|OUTPUT(10A)|出力側電源直結|
|LED|青|4|Connection|通信時点灯,遠隔非常停止有効時点滅,非通信時消灯|
|LED|青|1|BluetoothStatus|BLE通信状況|
|Buzzer|-|1|RemoteStop|遠隔非常停止有効時|

### インターフェイス

|種類|コネクタ数|用途|説明|
|:-:|:-:|:-:|:-:|
|CAN|2|遠隔非常停止の状態を他基板に送信|非常停止基板の動作状況を送信する。|
|STM32-UART|1|プログラムのデバッグ用||
|RNBD451-UART|1|BLEモジュールのデバッグ用||
|USB-type-c|1|マイコンのデバッグ用||
|XH2pin|2|非常停止ボタン接続用|ロボット搭載の非常停止スイッチを接続する。|
|ジャンパー|1|遠隔非常停止無効化用|遠隔非常停止が押されても駆動系を止めない。|
|DIPx4|1|BLE通信時のチャンネル切り替え|2bit分はチャンネル。残りは予備。|