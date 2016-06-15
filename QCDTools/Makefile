IDIR       = .
ODIR       = obj
SDIR       = ../../SusyAnaTools/Tools

#CXX       = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++
CXX        = g++

#CXXFLAGS  += -Iinc -std=c++0x -I${CMSSW_BASE}/src/
CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include

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

PROGRAMS = tupleTest DeepTrim QCDTFTrimAndSlim_LLHadTau QCDTFTrimAndSlim_Zinv QCDTFTrimAndSlim_QCD QCDTFTrimAndSlim_TTZ QCDTFTrimAndSlim_Data

all: mkobj sampPyWrap $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python
sampPyWrap: $(ODIR)/samplesModule.so

$(ODIR)/samplesModule.so: $(ODIR)/samplesPyWrap.o $(ODIR)/samplesModulePyWrap.o
	$(CXX) -shared -o $@ $^

$(ODIR)/samplesPyWrap.o: $(SDIR)/samples.cc $(SDIR)/samples.h
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

DeepTrim: $(ODIR)/DeepTrim.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_LLHadTau: $(ODIR)/QCDTFTrimAndSlim_LLHadTau.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_Zinv: $(ODIR)/QCDTFTrimAndSlim_Zinv.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_QCD: $(ODIR)/QCDTFTrimAndSlim_QCD.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_TTZ: $(ODIR)/QCDTFTrimAndSlim_TTZ.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_Data: $(ODIR)/QCDTFTrimAndSlim_Data.o $(ODIR)/NTupleReader.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 

-include $(ODIR)/*.d
