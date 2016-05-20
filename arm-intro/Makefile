TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

figures/terms.png: figures/chip.jpg figures/core.jpg figures/potato-chips.jpg

figures/chip.jpg:
	wget -O $@ -c "https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/KL_Motorola_68HC11.jpg/640px-KL_Motorola_68HC11.jpg"

figures/core.jpg:
	wget -O $@ -c "https://upload.wikimedia.org/wikipedia/commons/4/4e/Diopsis.jpg"

figures/potato-chips.jpg:
	wget -O $@ -c "https://upload.wikimedia.org/wikipedia/commons/1/15/Pizza_potato.JPG"

slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/simple

include $(TOPDIR)/stylesheets/Makefile.rules
