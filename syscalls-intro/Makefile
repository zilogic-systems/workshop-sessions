TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

#datauris = code/led.py.datauri         \
	   code/led-blink.py.datauri   \
	   code/led-chcolor.py.datauri \
	   code/gpio.py.datauri        \
	   code/key.py.datauri         \
           code/key-debounce.py.datauri\
           code/key-status.py.datauri

#dl-files = figures/pir.jpg 		\
	   figures/reed-switch.jpg	\
	   figures/smoke-sensor.jpg 	\
	   figures/solenoid-valve.jpg 	\
	   figures/relay.jpg

code/%.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: download slides.html

download: $(dl-files)

figures/pir.jpg:
	wget -c -O figures/pir.jpg "https://github.com/SeeedDocument/Grove_PIR_Motion_Sensor/raw/master/images/Grove_-_PIR_Motion_Sensor.jpg"

figures/reed-switch.jpg:
	wget -c -O figures/reed-switch.jpg "https://upload.wikimedia.org/wikipedia/commons/thumb/b/bd/Reed_switch_%28aka%29.jpg/800px-Reed_switch_%28aka%29.jpg"

figures/smoke-sensor.jpg:
	wget -c -O figures/smoke-sensor.jpg "http://img.dxcdn.com/productimages/sku_429922_2.jpg"

figures/solenoid-valve.jpg:
	wget -c -O figures/solenoid-valve.jpg "https://cdn1.bigcommerce.com/server2300/tntau7/images/stencil/500x659/products/123/623/Latching_Valve_2__52042.1382796365.jpg?c=2"

figures/relay.jpg:
	wget -c -O figures/relay.jpg "https://www.waveshare.com/media/catalog/product/cache/1/image/800x800/9df78eab33525d08d6e5fb8d27136e95/r/p/rpi-relay-board-1.jpg"

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png) $(datauris) $(dl-files)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
