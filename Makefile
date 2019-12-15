CC := g++
SRCDIR := src
BUILDDIR := build

build: $(SRCDIR)/render.cpp
	mkdir $(BUILDDIR)
	$(CC) -o $(BUILDDIR)/render $(SRCDIR)/render.cpp `pkg-config --cflags --libs gl glfw3 glu`
	$(BUILDDIR)/render

clean:
	$(RM) -r $(BUILDDIR)
