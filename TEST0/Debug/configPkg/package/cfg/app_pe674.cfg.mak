# invoke SourceDir generated makefile for app.pe674
app.pe674: .libraries,app.pe674
.libraries,app.pe674: package/cfg/app_pe674.xdl
	$(MAKE) -f D:\workspace_v9\TEST0/src/makefile.libs

clean::
	$(MAKE) -f D:\workspace_v9\TEST0/src/makefile.libs clean

