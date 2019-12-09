# invoke SourceDir generated makefile for app.pe674
app.pe674: .libraries,app.pe674
.libraries,app.pe674: package/cfg/app_pe674.xdl
	$(MAKE) -f C:\Users\olleh\workspace_v9\LAB8_A/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\olleh\workspace_v9\LAB8_A/src/makefile.libs clean

