POWER_RELEASE = orion_power_beta_mar2003
CC = g++

#OFLAGS = -O0 -g -w -Wall   -Wno-unused
#CFLAGS = -Wno-deprecated -O0 -g -static -DPOWER_TEST -I./$(POWER_RELEASE)/power -I./$(POWER_RELEASE)/library
CFLAGS = -g  -w -Wall -m32 -Wno-unused -DPOWER_TEST -I./$(POWER_RELEASE)/power -I./$(POWER_RELEASE)/library


LINKFLAGS = -L./$(POWER_RELEASE)/power -lm -lpower 
.SUFFIXES: .o .cc

HEADERS = mynode.h mytable.h index.h SString.h SStd.h SRGen.h Svector.h configuration.h mess_queue.h mess_event.h flit.h sim_foundation.h sim_router.h sim_vcarb.h sim_ps.h

TARGET = popnet
PTARGET = power_model

SIM_SRCS = mytable.cc mynode.cc SString.cc SStd.cc SRGen.cc configuration.cc flit.cc sim_router.cc sim_routing.cc sim_vcarb.cc sim_ps.cc mess_event.cc sim_foundation.cc mess_queue.cc mainPopnet.cc

SIM_OBJS = $(SIM_SRCS:.cc=.o)

$(TARGET):$(SIM_OBJS) $(PTARGET) 

$(PTARGET):
	cd ./$(POWER_RELEASE)/power; $(MAKE)

configuration.o: configuration.cc configuration.h SStd.h SRGen.h index.h \
  SString.h mynode.h mytable.h
flit.o: flit.cc flit.h index.h SStd.h mynode.h mytable.h
mainPopnet.o: mainPopnet.cc index.h SStd.h SRGen.h configuration.h sim_foundation.h \
  sim_router.h sim_ps.h flit.h mess_event.h mess_queue.h mynode.h mytable.h
mess_event.o: mess_event.cc mess_event.h index.h flit.h SStd.h mynode.h mytable.h
mess_queue.o: mess_queue.cc mess_queue.h SStd.h index.h configuration.h \
  SRGen.h sim_foundation.h sim_router.h sim_ps.h flit.h mess_event.h mynode.h mytable.h
sim_foundation.o: sim_foundation.cc sim_foundation.h sim_router.h sim_ps.h flit.h \
  index.h SStd.h SRGen.h configuration.h mess_event.h mess_queue.h mynode.h mytable.h 
sim_router.o: sim_router.cc sim_router.h flit.h index.h SStd.h SRGen.h \
  configuration.h sim_foundation.h mess_event.h mess_queue.h mainPopnet.h mynode.h mytable.h
sim_ps.o: sim_ps.cc sim_ps.h flit.h index.h SStd.h SRGen.h \
  configuration.h sim_foundation.h mess_event.h mess_queue.h mainPopnet.h mynode.h mytable.h
sim_routing.o: sim_routing.cc sim_router.h flit.h index.h SStd.h SRGen.h \
  configuration.h sim_foundation.h mess_event.h mess_queue.h mynode.h mytable.h
sim_vcarb.o: sim_vcarb.cc sim_router.h flit.h index.h SStd.h SRGen.h \
  configuration.h sim_foundation.h mess_event.h mess_queue.h sim_vcarb.h mynode.h mytable.h
SRGen.o: SRGen.cc SRGen.h SStd.h
SStd.o: SStd.cc SStd.h
SString.o: SString.cc SString.h index.h SStd.h
RouterIDMap.o: RouterIDMap.h RouterIDMap.cc
VIP_Bypass.o: VIP_Bypass.h VIP_Bypass.cc

.cc.o:
	$(CC) -c $(CFLAGS) $<  

clean:
	rm -rf *.o popnet core
	cd ./$(POWER_RELEASE)/power; $(MAKE) clean
