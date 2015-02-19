arm-barcode-scanner
===================

qr barcode сканер для ARM

проект построен для работы на контроллере STM32F407VG.

Распознование реализовано на базе библиотеки ZXing. 
https://code.google.com/p/zxing/ 

аппаратная часть
================
аппаратная часть организована на отладочном наборе STM32F4 discovery.
http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/PF252419

Запуск в IAR Embedded Workbench
===============================
1. Открыть проект arm-barcode-scanner\Project\OV9655_Camera\EWARM\Project.eww
2. Перекомпилировать проект Project -> Rebuild all
3. Запускаем отладку Project -> Download and debug   (CTRL+D)
4. Запускаем программу Debug -> Go  (F5) 


демонстрация работы
https://vimeo.com/120055682

