-include $(ANALYZERPATH)/Makefile.common

.PHONY: lib dict all

lib: libVBFTagger.so
dict: libVBFTaggerClassDictionaries.so
all: lib

libVBFTagger.so: libVBFTaggerClassDictionaries.so $(OBJECTS)
	@echo "--> Creating custom shared library."
	@$(CC) $(CFLAGSDICT) -shared $(OBJECTS) $(LFLAGS) -o $(ANALYZERPATH)/$(LIBDIR)/$@ $(ROOTLIBS) -lVBFTaggerClassDictionaries

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "--> Creating object $@"
	@$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(LIBSMAIN)


libVBFTaggerClassDictionaries.so: $(LIBDIR)/ClassDictionaries.cxx
	@echo "--> Creating shared library with custom class dictionaries."
	@$(CC) $(CFLAGSDICT) -shared -o $(ANALYZERPATH)/$(LIBDIR)/$@ $(ROOTLIBS) $^
	@echo "--> Copying library with class dictionary to local CMSSW library folder: $(LIBDIR_CMSSW)"
	@cp $(ANALYZERPATH)/$(LIBDIR)/$@ $(LIBDIR_CMSSW)/

$(LIBDIR)/ClassDictionaries.cxx: $(INCLUDES) include/Linkdef.hpp
	@echo "--> Creating custom class dictionaries."
	@rootcling -f $@ -c -p -I${LEAFPATH} $^

clean:
	@echo "--> cleaning folders $(OBJDIR)/, $(LIBDIR)/"
	@rm -f $(wildcard $(OBJDIR)/*.o) $(LIBOBJS)
