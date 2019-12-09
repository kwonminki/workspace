# invoke SourceDir generated makefile for app.pe674
app.pe674: .libraries,app.pe674
.libraries,app.pe674: package/cfg/app_pe674.xdl
	$(MAKE) -f C:\Users\user\Desktop\LAB8H/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\user\Desktop\LAB8H/src/makefile.libs clean

