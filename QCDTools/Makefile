IDIR       = .
ODIR       = obj
SDIR       = ../../SusyAnaTools/Tools

CXX        = g++

CXXFLAGS += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/src
CXXFLAGS += -I$(shell scram tool info fastjet | grep '^INCLUDE' | sed 's/INCLUDE=//')
CXXFLAGS += -I$(shell scram tool info boost | grep '^INCLUDE' | sed 's/INCLUDE=//')
## Optimization flag
CXXFLAGS += -g -fPIC
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD         = g++
LDFLAGS    =

OPENCV_DIRECTORY=$(CMSSW_BASE)/src/opencv
LIBS       = $(shell root-config --glibs)
LIBS      += -Lobj -lSusyAnaTools
LIBS      += -L$(CMSSW_BASE)/src/TopTagger/TopTagger/test -lTopTagger
LIBS      += -L$(OPENCV_DIRECTORY)/lib/ -lopencv_ml -lopencv_core
MT2LIB     = -L$(CMSSW_BASE)/lib/${SCRAM_ARCH}/ -lrecipeAUXOxbridgeMT2 -L$(CMSSW_RELEASE_BASE)/lib/${SCRAM_ARCH}/ -lPhysicsToolsHeppy
LHAPDFLIB  = -L$(LHAPDF_DATA_PATH)/../../lib -lLHAPDF
FILES = $(wildcard $(SDIR)/*.cc)
OBJS  := $(FILES:$(SDIR)/%.cc=$(ODIR)/%.o)
PROGRAMS = DeepTrim SFCheckTrim QCDTFTrimAndSlim_LLHadTau QCDTFTrimAndSlim_Zinv QCDTFTrimAndSlim_QCD QCDTFTrimAndSlim_TTZ QCDTFTrimAndSlim_Data

all: mkobj $(OBJS) SusyAnaTools $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python
SusyAnaTools : $(OBJS)
	ar rcs lib$@.a $^
	gcc -shared -o $(ODIR)/lib$@.so $^

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

DeepTrim: $(ODIR)/DeepTrim.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

SFCheckTrim: $(ODIR)/SFCheckTrim.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_LLHadTau: $(ODIR)/QCDTFTrimAndSlim_LLHadTau.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_Zinv: $(ODIR)/QCDTFTrimAndSlim_Zinv.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_QCD: $(ODIR)/QCDTFTrimAndSlim_QCD.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_TTZ: $(ODIR)/QCDTFTrimAndSlim_TTZ.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

QCDTFTrimAndSlim_Data: $(ODIR)/QCDTFTrimAndSlim_Data.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) $(MT2LIB) -o $@

clean:
	rm -f $(IDIR)/*.a $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 

-include $(ODIR)/*.d
