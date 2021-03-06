
#include "types.h"

#include "math/math.h"
#include "memory/memory.h"
#include "string/string.h"

#include "user/death.h"

#include "common/print.h"
#include "vga/text.h"
#include "graphics/colour.h"

#include "specs/video.h"
#include "specs/version.h"
#include "specs/help.h"

#include "drivers/power/acpi.h"
#include "drivers/power/shutdown.h"
#include "drivers/power/reboot.h"

#include "drivers/pc_speaker.h"
#include "drivers/cmos.h"
#include "drivers/keyboard_old.h"

#include "drivers/serial.h"
#include "drivers/lpt.h"

#include "drivers/ata/ata.h"

#include "cpu/cpuid.h"
#include "cpu/rdtsc.h"
#include "cpu/speed.h"

#include "pci/pci.h"

#include "bios/bios.h"
#include "bios/smbios.h"

#include "bios/video_colour_type.h" // BDA stuff
#include "bios/generic_bda.h"

#include "key_maps/key_map.h"
#include "grub/parse_mboot.h"

#include "drivers/irq/pit.h"
#include "drivers/irq/mouse.h"
#include "drivers/irq/keyboard.h"

#include "int/irq.h"
#include "int/isr.h"
#include "int/misc.h"

#include "descr_tables/idt.h"
#include "descr_tables/gdt.h"

void c_main(uint32_t mb_magic, uint32_t mb_address) {
	vga_text_clear_screen();
	parse_mboot(mb_magic, mb_address);

	printf("GDT: Loading the gdt ...\n");
	load_gdt();

	printf("Interrupts: Installing isr ...\n");
	isr_install();

	printf("Memory: Initializing heap ...\n");
	init_heap();

	printf("Serial: Initializing serial ...\n");
	init_serial();

	printf("Interrupts: Initializing irqs ...\n");
	irq_init();

	printf_minor("\tInterrupts: Installing PIT on IRQ0 ...\n");
	pit_install();
	pit_phase(1000);

	printf_minor("\tInterrupts: Installing keyboard on IRQ1 ...\n");
	keyboard_install();

	printf_minor("\tInterrupts: Installing serial COM on IRQ3 and IRQ4 ...\n");
	serial_install();

	printf_minor("\tInterrutps: Installing parallel LPT on IRQ5 and IRQ7 ...\n");
	parallel_install();

	printf_minor("\tInterrupts: Installing PS/2 mouse on IRQ12 ...\n");
	mouse_install();

	printf("BDA: Parsing BDA ...\n");

	pit_uptime = (uint32_t) bda_pit_ticks_since_boot();
	printf_minor("\tBDA: %d PIT ticks have occured since boot.\n", pit_uptime);

	set_lpt_port(bda_get_lpt1_port());
	printf_minor("\tBDA: Setting LPT port to LPT1 (0x%x) ...\n", get_lpt_port());

	printf_minor("\tBDA: Detected %d LPT ports.\n", bda_get_lpt_count());
	printf_minor("\tBDA: Detected %d COM ports.\n", bda_get_com_count());

	printf_minor("\tBDA: The keyboard LED is %s.\n", bda_keyboard_led() ? "on" : "off");
	printf_minor("\tBDA: The keyboard buffer is %s.\n", bda_get_keyboard_buffer());
	printf_minor("\tBDA: There are %d coloumns in text mode.\n", bda_get_text_mode_columns());
	printf_minor("\tBDA: Screen is %s.\n", get_video_type() == VIDEO_TYPE_COLOUR ? "coloured" : "monochrome");

	printf("Interrupts: Storing interrupt flags ...\n");
	__asm__ __volatile__("sti");

	printf("Interrupts: Detecting if they are enabled ...\n");
	are_ints_enabled();
	printf_minor("\tInterrupts are %s.\n", !ints_enabled ? "enabled" : "disabled");

	printf("PC Speaker: Making sure it is set to mute ...\n");
	pc_speaker_mute();

	printf("CPU RDTSC: Timestamp is %d.\n", cpu_rdtsc());

	printf("CPUID: Detecting cpuid ...\n");
	uint8_t cpu = cpuid_detect_cpu();

	printf_minor("\tCPUID: CPU %s TSC.\n", cpuid_detect_tsc() ? "supports" : "does not support");
	printf_minor("\tCPUID: CPU %s SSE.\n", cpuid_detect_sse() ? "supports" : "does not support");

	printf("CPU: Benchmarking the CPU speed without interrupts (~ %d Hz).\n", cpu_detect_speed_noint());

	printf("SMBIOS: Detecting SMBIOS ...\n");
	char* smbios_entry_ptr = smbios_entry();

	if (&smbios_entry_ptr) {
		printf_minor("\tSMBIOS exists at %d.\n", (uint32_t) &smbios_entry_ptr);
		smbios_entry_point_t* smbios = smbios_get(smbios_entry_ptr);

		printf_minor("\tSMBIOS version %d.%d.\n", smbios->major_version, smbios->minor_version);

	} else {
		printf_warn("SMBIOS does not exist.\n");

	}

	printf("ATA: Setting up drives ...\n");
	printf_minor("\tBDA: Detected %d disk drives.\n", bda_get_drive_count());

	printf_minor("\tATA: Setting up primary master ...\n");
	_drive_primary_master = ata_setup(1, ATA_PRIMARY);
	printf_minor("\tATA: Setting up primary slave ...\n");
	_drive_primary_slave = ata_setup(0, ATA_PRIMARY);

	printf_minor("\tATA: Setting up secondary master ...\n");
	_drive_secondary_master = ata_setup(1, ATA_SECONDARY);
	printf_minor("\tATA: Setting up secondary slave ...\n");
	_drive_secondary_slave = ata_setup(0, ATA_SECONDARY);

	printf_minor("\tATA: Setting up tertiary master ...\n");
	_drive_tertiary_master = ata_setup(1, ATA_TERTIARY);
	printf_minor("\tATA: Setting up tertiary slave ...\n");
	_drive_tertiary_slave = ata_setup(0, ATA_TERTIARY);

	printf_minor("\tATA: Setting up quaternary master ...\n");
	_drive_quaternary_master = ata_setup(1, ATA_QUATERNARY);
	printf_minor("\tATA: Setting up quaternary slave ...\n");
	_drive_quaternary_slave = ata_setup(0, ATA_QUATERNARY);

	drive_primary_master = &_drive_primary_master;
	drive_primary_slave = &_drive_primary_slave;
	drive_secondary_master = &_drive_secondary_master;
	drive_secondary_slave = &_drive_secondary_slave;
	drive_tertiary_master = &_drive_tertiary_master;
	drive_tertiary_slave = &_drive_tertiary_slave;
	drive_quaternary_master = &_drive_quaternary_master;
	drive_quaternary_slave = &_drive_quaternary_slave;

	printf("ATA: Identifying drives ...\n");

	printf_minor("\tATA: Identifying primary master ...\n");
	ata_identify(drive_primary_master);
	printf_minor("\tATA: Identifying primary slave ...\n");
	ata_identify(drive_primary_slave);

	printf_minor("\tATA: Identifying secondary master ...\n");
	ata_identify(drive_secondary_master);
	printf_minor("\tATA: Identifying secondary slave ...\n");
	ata_identify(drive_secondary_slave);

	printf_minor("\tATA: Identifying tertiary master ...\n");
	ata_identify(drive_tertiary_master);
	printf_minor("\tATA: Identifying tertiary slave ...\n");
	ata_identify(drive_tertiary_slave);

	printf_minor("\tATA: Identifying quaternary master ...\n");
	ata_identify(drive_quaternary_master);
	printf_minor("\tATA: Identifying quaternary slave ...\n");
	ata_identify(drive_quaternary_slave);

	printf("ATA: The selected drive is %s %s.\n", ata_current_drive->name, ata_current_drive->master_name);

	printf("CMOS: Initializing ...\n");
	cmos_init();

	printf_minor("\tCMOS: Adding RTC update event to occur every minute ... \n");
	add_event(60000, cmos_read_rtc_event);

	printf("ACPI: Initializing ... \n");
	printf_minor("\tACPI: %d\n", acpi_init());

	printf("PCI: Scanning for devices ...\n");
	pci_debug();

	printf("PCI: Analysing devices ...\n");
	pci_analyse();

	//main();
	for(;;);
}
