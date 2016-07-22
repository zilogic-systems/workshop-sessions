TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = game.zip.datauri             \
	   code/test_model_v3.py.datauri \
	   code/test_model_v4.py.datauri \
           code/test_model_v5.py.datauri

all: test_model_v3-split test_model_v4-split slides.html

game.zip:
	zip -r $@ game

game.zip.datauri: MIMETYPE = "binary/octet-stream"

code/test_model_v3.py.datauri: MIMETYPE = "text/python"
code/test_model_v4.py.datauri: MIMETYPE = "text/python"
code/test_model_v5.py.datauri: MIMETYPE = "text/python"

test_model_v3-split:
	python $(TOPDIR)/scripts/split.py code/test_model_v3.py

test_model_v4-split:
	python $(TOPDIR)/scripts/split.py code/test_model_v4.py

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f sokoban.zip
	rm -f slides.html

distclean: clean
	find . -name "*.pyc" -delete
	find . -name "*~" -delete

include $(TOPDIR)/stylesheets/Makefile.rules
