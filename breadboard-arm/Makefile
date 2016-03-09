TOPDIR = ../
EXPORT_WIDTH = 1600
blocks = battery-block.png ftdi-block.png usb-block.png lpc1114-block.png ftdi-simple-block.png regulator-block.png
diagrams = v1.png v2.png v3.png v4.png v5.png ftdi-simple-block.png spectrum.png

all: slides.html

slides.html: $(diagrams)

v1.png: battery-block.png lpc1114-block.png

v2.png: battery-block.png lpc1114-block.png

v3.png: usb-block.png lpc1114-block.png regulator-block.png

v4.png: ftdi-block.png lpc1114-block.png

v5.png: ftdi-block.png lpc1114-block.png

spectrum.png: spectrum.svg
	inkscape -d 200 -z -e spectrum.png spectrum.svg

ftdi-simple-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=ftdi-simple-block -e ftdi-simple-block.png blocks.svg

battery-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=battery-block -e battery-block.png blocks.svg

regulator-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=regulator-block -e regulator-block.png blocks.svg 

ftdi-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=ftdi-block -e ftdi-block.png blocks.svg

usb-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=usb-block -e usb-block.png blocks.svg 

lpc1114-block.png: blocks.svg
	inkscape -d 1200 -z --export-id=lpc1114-block -e lpc1114-block.png blocks.svg 

clean:
	rm -f $(blocks)
	rm -f $(diagrams)
	rm -f *.html

include $(TOPDIR)/stylesheets/Makefile.rules
