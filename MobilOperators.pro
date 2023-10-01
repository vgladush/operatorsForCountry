QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbWorker.cpp \
    main.cpp \
    mainwindow.cpp \
    opersItemDelegate.cpp \
    opersModel.cpp \
    opersPopupDialog.cpp

HEADERS += \
    dbWorker.h \
    mainwindow.h \
    opersItemDelegate.h \
    opersModel.h \
    opersPopupDialog.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/Countries/AD.png \
    images/Countries/AE.png \
    images/Countries/AF.png \
    images/Countries/AG.png \
    images/Countries/AI.png \
    images/Countries/AL.png \
    images/Countries/AM.png \
    images/Countries/AN.png \
    images/Countries/AO.png \
    images/Countries/AR.png \
    images/Countries/AS.png \
    images/Countries/AT.png \
    images/Countries/AU.png \
    images/Countries/AW.png \
    images/Countries/AZ.png \
    images/Countries/BA.png \
    images/Countries/BB.png \
    images/Countries/BD.png \
    images/Countries/BE.png \
    images/Countries/BF.png \
    images/Countries/BG.png \
    images/Countries/BH.png \
    images/Countries/BI.png \
    images/Countries/BJ.png \
    images/Countries/BM.png \
    images/Countries/BN.png \
    images/Countries/BO.png \
    images/Countries/BR.png \
    images/Countries/BS.png \
    images/Countries/BT.png \
    images/Countries/BW.png \
    images/Countries/BY.png \
    images/Countries/BZ.png \
    images/Countries/CA.png \
    images/Countries/CD.png \
    images/Countries/CF.png \
    images/Countries/CG.png \
    images/Countries/CH.png \
    images/Countries/CI.png \
    images/Countries/CK.png \
    images/Countries/CL.png \
    images/Countries/CM.png \
    images/Countries/CN.png \
    images/Countries/CO.png \
    images/Countries/CR.png \
    images/Countries/CU.png \
    images/Countries/CV.png \
    images/Countries/CY.png \
    images/Countries/CZ.png \
    images/Countries/DE.png \
    images/Countries/DJ.png \
    images/Countries/DK.png \
    images/Countries/DM.png \
    images/Countries/DO.png \
    images/Countries/DZ.png \
    images/Countries/EC.png \
    images/Countries/EE.png \
    images/Countries/EG.png \
    images/Countries/ER.png \
    images/Countries/ES.png \
    images/Countries/ET.png \
    images/Countries/FI.png \
    images/Countries/FJ.png \
    images/Countries/FK.png \
    images/Countries/FM.png \
    images/Countries/FO.png \
    images/Countries/FR.png \
    images/Countries/GA.png \
    images/Countries/GB.png \
    images/Countries/GD.png \
    images/Countries/GE-AB.png \
    images/Countries/GE.png \
    images/Countries/GF.png \
    images/Countries/GG.png \
    images/Countries/GH.png \
    images/Countries/GI.png \
    images/Countries/GL.png \
    images/Countries/GM.png \
    images/Countries/GN.png \
    images/Countries/GP.png \
    images/Countries/GQ.png \
    images/Countries/GR.png \
    images/Countries/GT.png \
    images/Countries/GU.png \
    images/Countries/GW.png \
    images/Countries/GY.png \
    images/Countries/HK.png \
    images/Countries/HN.png \
    images/Countries/HR.png \
    images/Countries/HT.png \
    images/Countries/HU.png \
    images/Countries/ID.png \
    images/Countries/IE.png \
    images/Countries/IL.png \
    images/Countries/IM.png \
    images/Countries/IN.png \
    images/Countries/IQ.png \
    images/Countries/IR.png \
    images/Countries/IS.png \
    images/Countries/IT.png \
    images/Countries/JE.png \
    images/Countries/JM.png \
    images/Countries/JO.png \
    images/Countries/JP.png \
    images/Countries/KE.png \
    images/Countries/KG.png \
    images/Countries/KH.png \
    images/Countries/KI.png \
    images/Countries/KM.png \
    images/Countries/KN.png \
    images/Countries/KP.png \
    images/Countries/KR.png \
    images/Countries/KW.png \
    images/Countries/KY.png \
    images/Countries/KZ.png \
    images/Countries/LA.png \
    images/Countries/LB.png \
    images/Countries/LC.png \
    images/Countries/LI.png \
    images/Countries/LK.png \
    images/Countries/LR.png \
    images/Countries/LS.png \
    images/Countries/LT.png \
    images/Countries/LU.png \
    images/Countries/LV.png \
    images/Countries/LY.png \
    images/Countries/MA.png \
    images/Countries/MC.png \
    images/Countries/MD.png \
    images/Countries/ME.png \
    images/Countries/MG.png \
    images/Countries/MH.png \
    images/Countries/MK.png \
    images/Countries/ML.png \
    images/Countries/MM.png \
    images/Countries/MN.png \
    images/Countries/MO.png \
    images/Countries/MP.png \
    images/Countries/MQ.png \
    images/Countries/MR.png \
    images/Countries/MS.png \
    images/Countries/MT.png \
    images/Countries/MU.png \
    images/Countries/MV.png \
    images/Countries/MW.png \
    images/Countries/MX.png \
    images/Countries/MY.png \
    images/Countries/MZ.png \
    images/Countries/NA.png \
    images/Countries/NC.png \
    images/Countries/NE.png \
    images/Countries/NG.png \
    images/Countries/NI.png \
    images/Countries/NL.png \
    images/Countries/NO.png \
    images/Countries/NP.png \
    images/Countries/NR.png \
    images/Countries/NU.png \
    images/Countries/NZ.png \
    images/Countries/OM.png \
    images/Countries/PA.png \
    images/Countries/PE.png \
    images/Countries/PF.png \
    images/Countries/PG.png \
    images/Countries/PH.png \
    images/Countries/PK.png \
    images/Countries/PL.png \
    images/Countries/PM.png \
    images/Countries/PR.png \
    images/Countries/PS.png \
    images/Countries/PT.png \
    images/Countries/PW.png \
    images/Countries/PY.png \
    images/Countries/QA.png \
    images/Countries/RE.png \
    images/Countries/RO.png \
    images/Countries/RS.png \
    images/Countries/RU.png \
    images/Countries/RW.png \
    images/Countries/SA.png \
    images/Countries/SB.png \
    images/Countries/SC.png \
    images/Countries/SD.png \
    images/Countries/SE.png \
    images/Countries/SG.png \
    images/Countries/SI.png \
    images/Countries/SK.png \
    images/Countries/SL.png \
    images/Countries/SM.png \
    images/Countries/SN.png \
    images/Countries/SO.png \
    images/Countries/SR.png \
    images/Countries/SS.png \
    images/Countries/ST.png \
    images/Countries/SV.png \
    images/Countries/SY.png \
    images/Countries/SZ.png \
    images/Countries/TC.png \
    images/Countries/TD.png \
    images/Countries/TG.png \
    images/Countries/TH.png \
    images/Countries/TJ.png \
    images/Countries/TL.png \
    images/Countries/TM.png \
    images/Countries/TN.png \
    images/Countries/TO.png \
    images/Countries/TR.png \
    images/Countries/TT.png \
    images/Countries/TV.png \
    images/Countries/TW.png \
    images/Countries/TZ.png \
    images/Countries/UA.png \
    images/Countries/UG.png \
    images/Countries/US.png \
    images/Countries/UY.png \
    images/Countries/UZ.png \
    images/Countries/VA.png \
    images/Countries/VC.png \
    images/Countries/VE.png \
    images/Countries/VG.png \
    images/Countries/VI.png \
    images/Countries/VN.png \
    images/Countries/VU.png \
    images/Countries/WF.png \
    images/Countries/WS.png \
    images/Countries/XK.png \
    images/Countries/YE.png \
    images/Countries/ZA.png \
    images/Countries/ZM.png \
    images/Countries/ZW.png
