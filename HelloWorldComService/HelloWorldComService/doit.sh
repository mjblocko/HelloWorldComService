x86_64-w64-mingw32-windres  \
   -i HelloWorldComServer.rc \
   -o build/obj/windows/HelloWorldComServer.o \

	 # -O res

x86_64-w64-mingw32-g++ -shared -static-libgcc -static-libstdc++ \
		build/obj/windows/./HelloWorldComServer.o \
		build/obj/windows/./FpxCritSecLock.o \
		build/obj/windows/./Reg.o \
		build/obj/windows/./ClassFactory.o \
		build/obj/windows/./Utils.o \
		build/obj/windows/./DllMain.o \
		build/obj/windows/./SimpleObject.o \
		build/obj/windows/./FpxCritSect.o -luuid -lole32 -loleaut32 \
		-o build/dist/windows/cominterface.dll \

		# build/obj/windows/./dbug_msvc.o \
