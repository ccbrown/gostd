override CXXFLAGS += -nostdlib -fno-exceptions -std=c++1z -I./include
override LDFLAGS += -nostdlib -lSystem

SRCDIR = src
OBJDIR = obj

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

NODEPS := clean

all: cx libcx.a

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MD -MT '$@' -MF '$(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.d,$@)'

libcx.a: $(OBJS)
	ar rsc $@ $(OBJS)

cx: libcx.a
	$(CXX) libcx.a -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJDIR)
	rm -rf cx libcx.a
