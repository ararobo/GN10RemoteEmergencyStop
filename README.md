# GN10RemoteEmergencyStop
Gento Aibaが作成する遠隔非常停止と電源遮断ユニットです。

## 遠隔非常停止

遠隔非常停止ボタン用の通信ユニットで、ESP32C3によるBLE通信を用いる。
MCUにはSTM32F303K8T6を用い、ESP32C3との間にはUARTのインターフェイスを用いる。
チャンネルは4つあり、2pinのDIPスイッチによって選択できる。

## 電源遮断ユニット

2系統の電源遮断を行うユニットで、それぞれ10Aと30Aの最大電流に対応している。
遮断と同時に抵抗で放電を行う。そのため、非常停止作動後コンデンサの電荷によってロボットが動作してしまうことを防止できる。
外部スイッチの入力は2つ、ESP32C3によるBLEの通信を介した遠隔非常停止が有効である。

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

|部品|色|内容|説明|
|:-:|:-:|:-:|:-:|
|LED|白|LogicPower|電源直結|
|LED|白|CAN(5V)|電源直結|
|LED|白|INPUT(30A)|入力側電源直結|
|LED|白|INPUT(10A)|入力側電源直結|
|LED|青|OUTPUT(30A)|出力側電源直結|
|LED|青|OUTPUT(10A)|出力側電源直結|
|LED|青|Connection|通信時点滅|
|LED|赤|RemoteStop|遠隔非常停止|
|7seg|赤|DeviceCount|接続済みデバイス数|
|Buzzer|-|RemoteStop|遠隔非常停止|

### インターフェイス

|種類|コネクタ数|用途|説明|
|:-:|:-:|:-:|:-:|
|CAN|2|遠隔非常停止の状態を他基板に送信||
|STM32-UART|1|プログラムのデバッグ用||
|ESP32C3-UART|1|BLEモジュールのデバッグ用||
|XH2pin|2|非常停止ボタン接続用||
|ジャンパー|1|遠隔非常停止無効化用||