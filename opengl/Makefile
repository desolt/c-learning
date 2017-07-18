# Settings
PROJECT = gllearning
BUILDDIR = build
INCDIR = include
SRCDIR = src
OBJDIR = $(BUILDDIR)/obj

# Flags
CFLAGS += -I$(INCDIR) -std=c11 -Wall
LDFLAGS += -lglfw -lGL
NDEBUG ?= 0

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(BUILDDIR)/$(PROJECT)

.PHONY: clean

$(BUILDDIR)/$(PROJECT): $(OBJS) $(BUILDDIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $< $(CFLAGS) -c -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf build
