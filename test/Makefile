.PHONY: all clean

SRCDIR=src
MATDIR=mat
BUILDDIR=build
DUMPDIR=dump
HEXDIR=hex

ELF2HEX=./elf2hex

RISCVCC32=riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -static -nostdlib -nostartfiles -mcmodel=medany
RISCVOBJD=riscv64-unknown-elf-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data

SOURCES_C=$(notdir $(wildcard $(SRCDIR)/*.c))
SOURCES_S=$(notdir $(wildcard $(SRCDIR)/*.S))
SOURCES_M=$(notdir $(wildcard $(MATDIR)/*.S))
SOURCES  =$(sort $(SOURCES_C) $(SOURCES_S) $(SOURCES_M))
ELF=$(addprefix build/rv32-,$(basename $(SOURCES)))

all: $(ELF)

$(ELF2HEX)/elf2hex:
	$(MAKE) -C $(ELF2HEX)

rv32-init.o: init.S
	$(RISCVCC32) -c init.S -o rv32-init.o

rv32-mmio.o: mmio.c
	$(RISCVCC32) -c mmio.c -o rv32-mmio.o

rv32-mxmhost.o: mxmhost.c
	$(RISCVCC32) -c mxmhost.c -o rv32-mxmhost.o

$(BUILDDIR)/rv32-%: $(ELF2HEX)/elf2hex $(SRCDIR)/%.c rv32-init.o rv32-mmio.o mmio.ld
	mkdir -p $(BUILDDIR)
	mkdir -p $(DUMPDIR)
	mkdir -p $(HEXDIR)
	$(RISCVCC32) -c $(SRCDIR)/$*.c -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-$* -Tmmio.ld rv32-intermeidate.o rv32-init.o rv32-mmio.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-$* > $(DUMPDIR)/rv32-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-$* 0 16G $(HEXDIR)/rv32-$*.hex
	rm rv32-intermeidate.o

$(BUILDDIR)/rv32-%: $(ELF2HEX)/elf2hex $(SRCDIR)/%.S rv32-init.o rv32-mmio.o mmio.ld
	mkdir -p $(BUILDDIR)
	mkdir -p $(DUMPDIR)
	mkdir -p $(HEXDIR)
	$(RISCVCC32) -c $(SRCDIR)/$*.S -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-$* -Tmmio.ld rv32-intermeidate.o rv32-init.o rv32-mmio.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-$* > $(DUMPDIR)/rv32-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-$* 0 16G $(HEXDIR)/rv32-$*.hex
	rm rv32-intermeidate.o

$(BUILDDIR)/rv32-mxm-%: $(ELF2HEX)/elf2hex rv32-init.o rv32-mmio.o mmio.ld rv32-mxmhost.o mat/mxm-%.S
	$(RISCVCC32) -c $(MATDIR)/mxm-$*.S -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-mxm-$* -Tmmio.ld rv32-intermeidate.o rv32-init.o rv32-mmio.o rv32-mxmhost.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-mxm-$* > $(DUMPDIR)/rv32-mxm-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-mxm-$* 0 16G $(HEXDIR)/rv32-mxm-$*.hex
	rm rv32-intermeidate.o

clean:
	rm -f rv32-intermeidate.o rv32-init.o rv32-mmio.o rv32-mxmhost.o
	rm -rf build
	rm -rf dump
	rm -rf hex
