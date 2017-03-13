IDIR       = .
ODIR       = obj
SDIR       = $(CMSSW_BASE)/src/SusyAnaTools/Tools

CXX        = g++

#CXXFLAGS  += -Iinc -std=c++0x -I${CMSSW_BASE}/src/
CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include
#CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/src -I$(shell scram tool info fastjet | grep '^INCLUDE' | sed 's/INCLUDE=//')
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

PROGRAMS = QCD ClosurePlots BasicCheckPlots SysUncs LLHadTau AllHadTTJetsWJetsSTPlots

all: mkobj $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python
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

QCD: $(ODIR)/QCD.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/searchBins.o $(ODIR)/TriggerEff.o $(ODIR)/QCDFactors.o $(ODIR)/QCDReWeighting.o $(ODIR)/QCDBinFunction.o $(ODIR)/CalHistgram.o $(ODIR)/ClosureHistgram.o $(ODIR)/ClosureUncAUX.o $(ODIR)/BasicCheckHistgram.o $(ODIR)/SBCheckHistgram.o
	$(LD) $^ $(LIBS) -o $@

#SFCheck: $(ODIR)/SFCheck.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/BTagCorrector.o $(ODIR)/BTagCalibrationStandalone.o $(ODIR)/QCDReWeighting.o $(ODIR)/SFCheckHistgram.o
#	$(LD) $^ $(LIBS) -o $@

ClosurePlots: $(ODIR)/ClosurePlots.o $(ODIR)/searchBins.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) -o $@

BasicCheckPlots: $(ODIR)/BasicCheckPlots.o
	$(LD) $^ $(LIBS) -o $@

#SFCheckPlots: $(ODIR)/SFCheckPlots.o
#	$(LD) $^ $(LIBS) -o $@

SysUncs: $(ODIR)/SysUncs.o $(ODIR)/searchBins.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) -o $@

LLHadTau: $(ODIR)/LLHadTau.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/searchBins.o $(ODIR)/TriggerEff.o $(ODIR)/LLHadTauFactors.o $(ODIR)/QCDReWeighting.o $(ODIR)/AllHadTTJetsWJetsSTHistgram.o
	$(LD) $^ $(LIBS) -o $@

AllHadTTJetsWJetsSTPlots: $(ODIR)/AllHadTTJetsWJetsSTPlots.o $(ODIR)/searchBins.o $(ODIR)/SATException.o
	$(LD) $^ $(LIBS) -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 

-include $(ODIR)/*.d
