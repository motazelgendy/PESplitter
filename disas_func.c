/*
 *
 *  Copyright (C) 2014-2015 Motaz Reda <motazkhodair@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to motaz reda 
 *  motazkhodair@gmail.com
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "disas_func.h"
#include "pe_analyzer.h"


void PrintToFile(char *instruction_ascii)
{
	FILE *WrFile;
	WrFile = fopen("as_output.txt", "a");
	if(WrFile ==NULL) {
		perror("cannot open file for write\n");
		exit(1);
	}

	fprintf(WrFile, instruction_ascii);
	fprintf(WrFile, "\n");
	fclose(WrFile);
}


void CheckFileExists()
{
	if (fopen("as_output.txt", "r") != NULL) {
		printf("Removing Old File First\n");
		remove("as_output.txt");
	}
}


int RealFileOffset(unsigned char *buffer, int address)
{
	IMAGE_DOS_HEADER *dos;
	IMAGE_NT_HEADERS *ntheader;
	IMAGE_IMPORT_DESCRIPTOR *import_desc;
	PIMAGE_THUNK_DATA *names;

	int n, section_size = 0;
	int data_dir;
	char *data_dir_desc;

	int import_count = 0; 
	int offset = 0;
	int length = 0;

	dos = (IMAGE_DOS_HEADER *)buffer;

	unsigned char *PE_HEADER = (unsigned char *)malloc(sizeof(buffer[dos->e_lfanew]) * sizeof(unsigned char *) + 1); //allocate
	PE_HEADER = &buffer[dos->e_lfanew];
	ntheader = (IMAGE_NT_HEADERS *)PE_HEADER;

	int g=0;
	int realoffset=0;
	int fileoffset = 0;
	// here we check if the address has imagebase included with it
	if(address & ntheader->op_header.ImageBase) {
		address = address - ntheader->op_header.ImageBase;
		// printf("the address withgout image base is %x\n", ntheader->op_header.ImageBase);
	}
	for(n=1;n<=ntheader->file_header.NumberOfSections;n++) {
		IMAGE_SECTION_HEADER *secheader = (IMAGE_SECTION_HEADER *)(PE_HEADER + sizeof(IMAGE_NT_HEADERS) + section_size);
		section_size += sizeof(IMAGE_SECTION_HEADER);
		// here we check for the address are its in a section or not 
		if(address <= (secheader->VirtualAddress + secheader->VirtualSize) && 
			address >= secheader->VirtualAddress) {
			fileoffset = (secheader->VirtualAddress - secheader->PointerToRawData); //this the pointer to row data to get the real offset
			// printf("\treal offset in disk is: %x for section %c%c%c%c%c%c%c%c\n", fileoffset, secheader->Name[0], secheader->Name[1], secheader->Name[2], secheader->Name[3], secheader->Name[4], secheader->Name[5], secheader->Name[6], secheader->Name[7]);
			offset = (address - fileoffset);
			// printf("the offset is %x\n", offset);
		}
		// we are comment this three line just for a while 
		// else{
			// offset = address;
		// }
	}
	// here we return the real offset of the address choosed
	return offset;
}

unsigned char *GetApi(int insns, unsigned char *buf)
{
	int addr = RealFileOffset(buf, insns);

	unsigned char oneaddr, twoaddr;
	unsigned char *straddr;
	int realintaddr, intaddr;

	oneaddr = buf[addr];
	twoaddr = buf[addr+1];

	sprintf(straddr, "%x%x", twoaddr, oneaddr);
	intaddr = strtoul(straddr, NULL, 16);

	realintaddr = RealFileOffset(buf, intaddr);
	unsigned char *ApiName = &buf[realintaddr+2];

	return ApiName;
}