arm-barcode-scanner
===================

qr barcode scanner  for ARM

project works for the controller STM32F407VG.

This code is based on the ZXing library. See https://code.google.com/p/zxing/ for
more information.

Hardware requirements
=====================
The main board is the STM32F4 discovery kit.
See http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/PF252419 for more information.

Running in IAR Embedded Workbench
=================================
1. Open the project: arm-barcode-scanner\Project\OV9655_Camera\EWARM\Project.eww
2. Recompile the project: Project -> Rebuild all
3. Run the debugging: Project -> Download and debug (CTRL + D)
4. Run the program: Debug -> Go (F5)

video work
https://vimeo.com/120055682
