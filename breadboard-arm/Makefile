blocks = battery-block.png ftdi-block.png usb-block.png lpc1114-block.png

all: $(blocks) v1.png v2.png v3.png v4.png

battery-block.png:
	inkscape -d 1200 -z --export-id=battery-block -e battery-block.png blocks.svg 

ftdi-block.png:
	inkscape -d 1200 -z --export-id=ftdi-block -e ftdi-block.png blocks.svg

usb-block.png:
	inkscape -d 1200 -z --export-id=usb-block -e usb-block.png blocks.svg 

lpc1114-block.png:
	inkscape -d 1200 -z --export-id=lpc1114-block -e lpc1114-block.png blocks.svg 

clean:
	rm -f $(blocks)
	rm -f *.html
