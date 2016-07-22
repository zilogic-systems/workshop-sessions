TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = sokoban.zip.datauri             \
	   code/test_sokoban_v3.py.datauri \
	   code/test_sokoban_v4.py.datauri \
           code/test_sokoban_v5.py.datauri

all: slides.html

sokoban.zip:
	zip -r $@ sokoban

sokoban.zip.datauri: MIMETYPE = "binary/octet-stream"

code/test_sokoban_v3.py.datauri: MIMETYPE = "text/python"
code/test_sokoban_v4.py.datauri: MIMETYPE = "text/python"
code/test_sokoban_v5.py.datauri: MIMETYPE = "text/python"

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f sokoban.zip
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
