# Workshop Sessions

This repository will hold slides and resources for workshops organized
by Zilogic.

## Workshops

  * Git Basics Workshop. For details see http://www.zilogic.com/git-training.html
  * Dive Into Yocto, Workshop. For details see http://www.zilogic.com/yocto-poky-training.html
  * ARM Bare Metal Programming, Workshop. For details see
    http://www.zilogic.com/arm-linker-script-training.html
  * Kernel Porting Workshop. For details see http://www.zilogic.com/linux-kernel-porting-training.html

## Git Basics Workshop: Sessions

  * [Git Basics](git-basics)
  * [Git Object Model](git-internals)
  * [Git Remotes](git-remotes)
  * Advanced Git Features

## To build the slides

 * Install asciidoc 
 * Install build-essential

After installation you can navigate to each session and then build the slides

#### Example to build slides

```
$ git clone https://github.com/zilogic-systems/workshop-sessions.git
$ cd workshop-sessions
$ cd kernel-boot
$ make
$ firefox slides.html

```
## Dive Into Yocto, Workshop: Sessions

  * [Autotools](autotools)
  * [Manual Rootfs](manual-rootfs)
  * [BitBake Intro](bitbake-intro)
  * [BitBake Rootfs](bitbake-rootfs)
  * [BitBake Layers](bitbake-layers)
  * [Debian Packaging](debian-packaging)
  * [BitBake Data Model](bitbake-data-model)
  * [BitBake Packaging](bitbake-packages)
  * [Yocto Introduction](yocto-intro)
  * [Yocto Getting Started](yocto-getting-started)
  * [Yocto Customization](yocto-customization)
  * [Yocto Internals](yocto-internals)

## ARM Bare Metal Programming, Workshop: Sessions

  * [ARM Architecture](arm-intro)
  * [ARM Instruction Set](arm-iset)
  * [ARM Assembler](arm-asm)
  * [Role of Linker](arm-linker)
  * [Linker Scripts](arm-lds)
  * [C Startup Code](arm-cstartup)
  * [Using C Library](arm-libc)

## Kernel Porting, Workshop: Sessions

  * [The Linux Kernel](kernel-build)
  * [Device Interfacing](devices-intro)
  * [Introduction to Drivers](kernel-driver)
  * [Bus Model](kernel-bus-model)
  * [Device Tree Syntax](kernel-dt-syntax)
  * [SoC Architecture](kernel-soc)
  * [Device Tree by Example](kernel-dt-by-example)
  * [Flash in DTS](kernel-flash)
  * [Ethernet in DTS](kernel-ethernet)
  * [I2C in DTS](kernel-i2c)
  * [LCD Display in DTS](kernel-display)
  * [GPIOs in DTS](kernel-gpio)
  * [Pin Control in DTS](kernel-pinctrl)
  * [Drivers for Device Tree](kernel-dt-drivers)
  * [Device Tree at Boot](kernel-boot)
  * [Debugging Device Tree Issue](dt-debugging)