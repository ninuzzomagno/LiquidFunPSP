#one-line comment
TARGET = hello
OBJS = main.o ClassApp.o FrameRate.o ClassMouse.o
 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
 
LIBS=  -losl -ljpeg -lpng -lz -lLiquidFunPSP\
         -lpsphprm -lpspsdk -lpspctrl -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio  -lpspaudiocodec\
         -lm -lstdc++

#EXTRA_TARGETS is the output file
#PSP_EBOOT_TITLE is the EBOOT's name
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = LiquidFun for PSP
#PSP_EBOOT_ICON= icon0.png
#PSP_EBOOT_PIC1= pic0.png
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak