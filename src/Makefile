LIBS := BlankRecordDelivery DataStorage HistogramInterface \
	DefaultModule InteractiveDelivery ToolBox \
	CommandPattern DummyHistogram Interpreter Utility \
	DynamicLoader JobControl\
	DataDelivery Processor\
	DataHandler Signal Suez

BUILDDIR := $(USER_SRC)

TARGET = production
MAKEFILE = Makefile

default: production

production::
	$(MAKE) -f $(MAKEFILE) $(LIBS) \
                "TARGET=$@" "DEBUG=$(DEBUG)"
$(LIBS) ::
	-(cd $(BUILDDIR)/$@; pwd; \
        $(MAKE) $(TARGET) DEBUG=$(DEBUG) \
                )
# DO NOT DELETE
