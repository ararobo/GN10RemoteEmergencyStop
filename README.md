# GN10RemoteEmergencyStop
Gento Aibaが作成する遠隔非常停止と電源遮断ユニットです。

## 遠隔非常停止

## 電源遮断ユニット
- [KiCAD](power_cutoff_unit)
- [使用部品](docs/power_cuttoff_unit_parts.md)
- [STM32F303K8T6で実装した場合のファームウェア](power_cutoff_unit/firmware/F303)
- [STM32G431K8T6で実装した場合のファームウェア](power_cutoff_unit/firmware/G431)

基板の仕様
2系統の電源遮断を行うユニットで、それぞれ10Aと30Aの最大電流に対応している。
遮断と同時に50ohm抵抗で放電を行う。そのため、非常停止作動後コンデンサの電荷によってロボットが動作してしまうことを防止できる。
外部スイッチの入力は2つ、ESP32C3によるBLEの通信を介した遠隔非常停止が有効である。