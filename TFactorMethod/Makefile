IDIR       = .
ODIR       = obj
SDIR       = ../../SusyAnaTools/Tools

#CXX       = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++
CXX        = g++

#CXXFLAGS  += -Iinc -std=c++0x -I${CMSSW_BASE}/src/
#CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include
#CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/../../../external/fastjet/3.1.0-odfocd/include -I$(CMSSW_RELEASE_BASE)/src
CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/src -I$(shell scram tool info fastjet | grep '^INCLUDE' | sed 's/INCLUDE=//')
## Optimization flag
CXXFLAGS += -g #-O3
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD       = g++
LDFLAGS  =

LIBS     = $(shell root-config --glibs)
MT2LIB     = -L$(CMSSW_BASE)/lib/${SCRAM_ARCH}/ -lrecipeAUXOxbridgeMT2
LHAPDFLIB  = -L$(LHAPDF_DATA_PATH)/../../lib -lLHAPDF

PROGRAMS = tupleTest QCD ClosurePlots BasicCheckPlots SysUncs

all: mkobj sampPyWrap $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python
sampPyWrap: $(ODIR)/samplesModule.so

$(ODIR)/samplesModule.so: $(ODIR)/samplesPyWrap.o $(ODIR)/samplesModulePyWrap.o
	$(CXX) -shared -o $@ $^

$(ODIR)/samplesPyWrap.o: $(SDIR)/samples.cc	$(SDIR)/samples.h
	$(CXX) --std=c++11 -c -fPIC -o $@ $<

$(ODIR)/samplesModulePyWrap.o: $(SDIR)/samplesModule.cc
	$(CXX) --std=c++11 -c -fPIC -o $@ $<

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

tupleTest: $(ODIR)/NTupleReader.o $(ODIR)/PDFUncertainty.o $(ODIR)/tupleReadTest.o
	$(LD) $^ $(LIBS) $(MT2LIB) $(LHAPDFLIB) -o $@

QCD: $(ODIR)/QCD.o $(ODIR)/NTupleReader.o $(ODIR)/searchBins.o $(ODIR)/QCDReWeighting.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

ClosurePlots: $(ODIR)/ClosurePlots.o $(ODIR)/searchBins.o
	$(LD) $^ $(LIBS)  -o $@

BasicCheckPlots: $(ODIR)/BasicCheckPlots.o
	$(LD) $^ $(LIBS)  -o $@

SysUncs: $(ODIR)/SysUncs.o $(ODIR)/searchBins.o
	$(LD) $^ $(LIBS)  -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 

-include $(ODIR)/*.d
