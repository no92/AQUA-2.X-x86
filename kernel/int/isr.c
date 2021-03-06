#include "isr.h"

void isr_install(void) {
	set_idt_gate(0, (uint32_t) isr0);
	set_idt_gate(1, (uint32_t) isr1);
	set_idt_gate(2, (uint32_t) isr2);
	set_idt_gate(3, (uint32_t) isr3);
	set_idt_gate(4, (uint32_t) isr4);
	set_idt_gate(5, (uint32_t) isr5);
	set_idt_gate(6, (uint32_t) isr6);
	set_idt_gate(7, (uint32_t) isr7);
	set_idt_gate(8, (uint32_t) isr8);
	set_idt_gate(9, (uint32_t) isr9);
	set_idt_gate(10, (uint32_t) isr10);
	set_idt_gate(11, (uint32_t) isr11);
	set_idt_gate(12, (uint32_t) isr12);
	set_idt_gate(13, (uint32_t) isr13);
	set_idt_gate(14, (uint32_t) isr14);
	set_idt_gate(15, (uint32_t) isr15);
	set_idt_gate(16, (uint32_t) isr16);
	set_idt_gate(17, (uint32_t) isr17);
	set_idt_gate(18, (uint32_t) isr18);
	set_idt_gate(19, (uint32_t) isr19);
	set_idt_gate(20, (uint32_t) isr20);
	set_idt_gate(21, (uint32_t) isr21);
	set_idt_gate(22, (uint32_t) isr22);
	set_idt_gate(23, (uint32_t) isr23);
	set_idt_gate(24, (uint32_t) isr24);
	set_idt_gate(25, (uint32_t) isr25);
	set_idt_gate(26, (uint32_t) isr26);
	set_idt_gate(27, (uint32_t) isr27);
	set_idt_gate(28, (uint32_t) isr28);
	set_idt_gate(29, (uint32_t) isr29);
	set_idt_gate(30, (uint32_t) isr30);
	set_idt_gate(31, (uint32_t) isr31);
	
	register_idt();
	
}

void isr0(void) {
	printf("%s\n", exception_messages[0]);
	asm("hlt");
	
		
}

void isr1(void) {
	printf("%s\n", exception_messages[1]);
	asm("hlt");
	
}

void isr2(void) {
	printf("%s\n", exception_messages[2]);
	asm("hlt");
	
}

void isr3(void) {
	printf("%s\n", exception_messages[3]);
	asm("hlt");
	
}

void isr4(void) {
	printf("%s\n", exception_messages[4]);
	asm("hlt");
	
}

void isr5(void) {
	printf("%s\n", exception_messages[5]);
	asm("hlt");
	
}

void isr6(void) {
	printf("%s\n", exception_messages[6]);
	asm("hlt");
	
}

void isr7(void) {
	printf("%s\n", exception_messages[7]);
	asm("hlt");
	
}

void isr8(void) {
	printf("%s\n", exception_messages[8]);
	asm("hlt");
	
}

void isr9(void) {
	printf("%s\n", exception_messages[9]);
	asm("hlt");
	
}

void isr10(void) {
	printf("%s\n", exception_messages[10]);
	asm("hlt");
	
}

void isr11(void) {
	printf("%s\n", exception_messages[11]);
	asm("hlt");
	
}

void isr12(void) {
	printf("%s\n", exception_messages[12]);
	asm("hlt");
	
}

void isr13(void) {
	printf("%s\n", exception_messages[13]);
	asm("hlt");
	
}

void isr14(void) {
	printf("%s\n", exception_messages[14]);
	asm("hlt");
	
}

void isr15(void) {
	printf("%s\n", exception_messages[15]);
	asm("hlt");
	
}

void isr16(void) {
	printf("%s\n", exception_messages[16]);
	asm("hlt");
	
}

void isr17(void) {
	printf("%s\n", exception_messages[17]);
	asm("hlt");
	
}

void isr18(void) {
	printf("%s\n", exception_messages[18]);
	asm("hlt");
	
}

void isr19(void) {
	printf("%s\n", exception_messages[19]);
	asm("hlt");
	
}

void isr20(void) {
	printf("%s\n", exception_messages[20]);
	asm("hlt");
	
}

void isr21(void) {
	printf("%s\n", exception_messages[21]);
	asm("hlt");
	
}

void isr22(void) {
	printf("%s\n", exception_messages[22]);
	asm("hlt");
	
}

void isr23(void) {
	printf("%s\n", exception_messages[23]);
	asm("hlt");
	
}

void isr24(void) {
	printf("%s\n", exception_messages[24]);
	asm("hlt");
	
}

void isr25(void) {
	printf("%s\n", exception_messages[25]);
	asm("hlt");
	
}

void isr26(void) {
	printf("%s\n", exception_messages[26]);
	asm("hlt");
	
}

void isr27(void) {
	printf("%s\n", exception_messages[27]);
	asm("hlt");
	
}

void isr28(void) {
	printf("%s\n", exception_messages[28]);
	asm("hlt");
	
}

void isr29(void) {
	printf("%s\n", exception_messages[29]);
	asm("hlt");
	
}

void isr30(void) {
	printf("%s\n", exception_messages[30]);
	asm("hlt");
	
}

void isr31(void) {
	printf("%s\n", exception_messages[31]);
	asm("hlt");
	
}

char* exception_messages[32] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	
};

