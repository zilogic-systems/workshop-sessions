images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

figures/branch-1.png: EXPORT_WIDTH=400
figures/branch-2.png: EXPORT_WIDTH=450
figures/merged.png: EXPORT_WIDTH=450

all: index.html $(images_png)

index.html: slides.asciidoc
	asciidoc slides.asciidoc

clean:
	rm -f $(images_png)
	rm -f slides.html

include ../Makefile.rules
