TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = game.zip.datauri             \
	   code/test_model_v3.py.datauri \
	   code/test_model_v4.py.datauri \
           code/test_model_v5.py.datauri

all: test_model_v3-split test_model_v4-split test_model_v5-split test_controller_v1-split view-split test_view_v2-split test_view_v3-split slides.html

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

test_model_v5-split:
	python $(TOPDIR)/scripts/split.py code/test_model_v5.py

test_controller_v1-split:
	python $(TOPDIR)/scripts/split.py code/test_controller_v1.py

test_view_v2-split:
	python $(TOPDIR)/scripts/split.py code/test_view_v2.py

test_view_v3-split:
	python $(TOPDIR)/scripts/split.py code/test_view_v3.py

view-split:
	python $(TOPDIR)/scripts/split.py code/view.py

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f game.zip
	rm -f slides.html
	rm -fr code/test_model_v3
	rm -fr code/test_model_v4
	rm -fr code/test_model_v5
	rm -fr code/test_controller_v1
	rm -fr code/view
	rm -fr code/test_view_v2
	rm -fr code/test_view_v3

distclean: clean
	find . -name "*.pyc" -delete
	find . -name "*~" -delete
	find . -name "*.ttf" -delete

include $(TOPDIR)/stylesheets/Makefile.rules
