# Retail Store Station Box (Embedded Software Design project)

The ESD station box is an embedded check-out system for a retail store running Linux on a `ZYBO Z7 Zynq-7010` board. The desired system consists of one or more check-out stations, potentially with variations. The station box can accees an item database (for items sold in the store) which is kept on a server available over gigabit Ethernet in the store. The system is comprised of a barcode scanner, numpad, card reader, receipt printer, cashier display and customer display.

![station-box][img-station-box]

The central server can be accessed from a terminal in order to update item information (price, stock, sales, customer relations etc.). The central box also offers a secure connection to a credit card payment service, which is accesible using the ZeroMQ protocol - the full requirements specifications are [available here][req-specs].

## Overview

This repository structure is based on the [Modern CMake][modern-cmake] design principles. The project is developed using `C++14` and is cross-compiled using the `plnx-2017.4-arm-6.2.1` toolchain to run on the Zybo. However, the code can also be compiled using a regular compiler by using the `-DUSE_SYSTEM_COMPILER=ON` option when compiling.

The system is designed using a Task-based architecture using a generic Event structure.

## Installing

After cloning the project, it can be configured by running `cmake . -Bbuild` (using cross-compiler for Zybo) or `cmake . -Bbuild -DUSE_SYSTEM_COMPILER=ON` (using system compiler). Then compiled by running `cmake --build build`. The executable binaries are available in `/build/app`.

## Acknowledgements

- [Catalin Ntemkas][ref-catalin] - project and course supervisor
- [imabot2/serialib][ref-serialib] - serial communication library

<!-- LINKS -->

[modern-cmake]: https://cliutils.gitlab.io/modern-cmake/
[img-station-box]: /assets/img/esd-stationbox-system-diagram.png
[req-specs]: /assets/docs/requirements-specification.pdf
[ref-catalin]: https://portal.findresearcher.sdu.dk/da/persons/can
[ref-serialib]: https://github.com/imabot2/serialib
