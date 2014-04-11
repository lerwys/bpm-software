==============================================================================

Repository containing the Beam Position Monitor Software

==============================================================================

Prerequisites:

	-> Make sure you have the following libraries installed: 

	* zeromq-4.0.4 (http://zeromq.org/area:download)
	* czmq-2.1.0 (http://czmq.zeromq.org/page:get-the-software)

	-> Cloning this repository

1 - git clone --recursive https://github.com/lerwys/bpm-software.git

==============================================================================

PCIe Installation Instructions:

1 - sudo apt-get install linux-headers-generic

	-> Install the GIT package

2 - sudo apt-get install binutils gcc

	-> Change folder to the pcie driver location

4 - cd kernel

	-> Compile the PCIe driver and its tests

5 - make

	-> Install the PCIe drivers and libraries

6 - sudo make install

	-> Load the Driver module

7 - sudo insmod /lib/modules/$(uname -r)/extra/PciDriver.ko

	-> After this the kernel should have found the FPGA board and
	initialized it. Run the following command and check its output

8 - dmesg | tail

	-> You should see something like the excerpt below:

	"
		[267002.495109] pciDriver - pcidriver_init : 
			Major 250 allocated to nodename 'fpga'
		[267002.495130] pciDriver - pcidriver_probe : 
			Found ML605 board at 0000:01:00.0
		[267002.495224] pciDriver - pcidriver_probe : 
			Device /dev/fpga0 added
		[267002.495434] pciDriver - pcidriver_probe_irq : 
			Registered Interrupt Handler at pin 1, line 11, IRQ 16
		[267002.495450] pciDriver - pcidriver_init : 
			Module loaded
	"
==============================================================================

Running the PCIe self-test:

	-> After the installation of the PCIe driver (see above) it is possible to run
        a self test to check if everything is setup properly. For this run the following:

	-> Change to the "compiled tests folder"

1 - cd tests/pcie/bin

	-> Run the test entitled "testPciDriverMod"

2 - sudo ./testPciDriverMod

	-> You should get an output like the following, if everythig is ok:

	"
        Testing OPEN DEVICE... PASSED!
         Testing PCIDRIVER_IOC_MMAP_MODE... PASSED!
         Testing PCIDRIVER_IOC_MMAP_AREA... PASSED!
         Testing PCIDRIVER_IOC_PCI_INFO...  PASSED!
         Testing PCI CONFIG... 
           Reading PCI config area in byte mode ... PASSED!
           Reading PCI config area in word mode ... PASSED!
           Reading PCI config area in double-word mode ... PASSED!
         Testing PCI mmap... 
           Reading PCI info... PASSED!
           Setting mmap mode... PASSED!
           Setting mmap area... PASSED!
           MMAP'ing BAR0... PASSED!
           Setting mmap area... PASSED!
           MMAP'ing BAR2... PASSED!
           Setting mmap area... PASSED!
           MMAP'ing BAR4... PASSED!
         Testing PCIDRIVER_IOC_KMEM_ALLOC...
           alloc size    1024 :  PASSED!
           alloc size    2048 :  PASSED!
           alloc size    4096 :  PASSED!
           alloc size    8192 :  PASSED!
           alloc size   16384 :  PASSED!
           alloc size   32768 :  PASSED!
           alloc size   65536 :  PASSED!
           alloc size  131072 :  PASSED!
           alloc size  262144 :  PASSED!
           alloc size  524288 :  PASSED!
           alloc size 1048576 :  PASSED!
           alloc size 2097152 :  PASSED!
           alloc size 4194304 :  PASSED!
           alloc size 8388608 :  FAILED (maybe size is just too big)!
         Testing PCIDRIVER_IOC_KMEM_SYNC...
           Setting KMEM SYNC to write mode... PASSED!
           Setting KMEM SYNC to read mode... PASSED!
           Setting KMEM SYNC to read/write mode... PASSED!
         Testing PCIDRIVER_IOC_KMEM_FREE... PASSED!
         Testing Kernel Buffer mmap... 
           Setting MMAP mode to KMEM... PASSED!
             Allocing size    1024 : PASSED!
             MMAPing size     1024 : PASSED!
             Allocing size    2048 : PASSED!
             MMAPing size     2048 : PASSED!
             Allocing size    4096 : PASSED!
             MMAPing size     4096 : PASSED!
             Allocing size    8192 : PASSED!
             MMAPing size     8192 : PASSED!
             Allocing size   16384 : PASSED!
             MMAPing size    16384 : PASSED!
             Allocing size   32768 : PASSED!
             MMAPing size    32768 : PASSED!
             Allocing size   65536 : PASSED!
             MMAPing size    65536 : PASSED!
             Allocing size  131072 : PASSED!
             MMAPing size   131072 : PASSED!
             Allocing size  262144 : PASSED!
             MMAPing size   262144 : PASSED!
             Allocing size  524288 : PASSED!
             MMAPing size   524288 : PASSED!
             Allocing size 1048576 : PASSED!
             MMAPing size  1048576 : PASSED!
             Allocing size 2097152 : PASSED!
             MMAPing size  2097152 : PASSED!
             Allocing size 4194304 : PASSED!
             MMAPing size  4194304 : PASSED!
             Allocing size 8388608 : FAILED (maybe size is just too big)!
           Freeing Kernel buffers...
              Buffer index 0... PASSED!
              Buffer index 1... PASSED!
              Buffer index 2... PASSED!
              Buffer index 3... PASSED!
              Buffer index 4... PASSED!
              Buffer index 5... PASSED!
              Buffer index 6... PASSED!
              Buffer index 7... PASSED!
              Buffer index 8... PASSED!
              Buffer index 9... PASSED!
              Buffer index 10... PASSED!
              Buffer index 11... PASSED!
              Buffer index 12... PASSED!
         Testing PCIDRIVER_IOC_UMEM_SGMAP ... PASSED!
         Testing PCIDRIVER_IOC_UMEM_SGGET ... PASSED!
         Testing PCIDRIVER_IOC_UMEM_SYNC ...
           Setting UMEM SYNC to write mode... PASSED!
           Setting UMEM SYNC to read mode... PASSED!
           Setting UMEM SYNC to read/write mode... PASSED!
         Testing PCIDRIVER_IOC_UMEM_SGUNMAP ... PASSED!

		-------------------------------------
		|        All tests PASSED!          |
		-------------------------------------
	
	"

    -> Notice that some tests that try to evaluate the limits of a current
        Linux Kernel may fail in some cases. In the example above,
        two tests , due to an attempt to allocate a large buffer in kernel
        space.

    -> This is not actually an error or a failure, it is just trying to
        allocate more memory than the kernel has available.

==============================================================================

Installation Instructions:

	-> Comple everything

1 - make

	-> Compile the examples

2 - make examples

	-> Run the server components with a helper script

3 - ./init.sh

	-> Now we should be good to start making transactions.
	-> Change to the example applications folder

4 - cd examples

	-> Run the Example application

5 - ./client -v

	-> Leds should be blinking in the FMC ADC board