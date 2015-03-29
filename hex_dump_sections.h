void DumpSecHex(unsigned char *buffer, char opt, unsigned char *sectionname){
	IMAGE_DOS_HEADER *dos;
	IMAGE_NT_HEADERS *ntheader;
	IMAGE_IMPORT_DESCRIPTOR *import_desc;
	PIMAGE_THUNK_DATA *names;

	int n, section_size = 0;
	int data_dir;
	char *data_dir_desc;
	unsigned char *section = (unsigned char *)malloc(8);
	int import_count = 0; //for count imports

	printf("\t########Dumping Section As Hex########\n");
	// Dos Header
	dos = (IMAGE_DOS_HEADER *)buffer;
	// End Dos Header
	// begin Pe Header
	unsigned char *PE_HEADER = (unsigned char *)malloc(sizeof(buffer[dos->e_lfanew])); //allocate
	PE_HEADER = &buffer[dos->e_lfanew];
	ntheader = (IMAGE_NT_HEADERS *)PE_HEADER;
	// printf("\t#####Section Header#####\n");
	int g=0;
	int counter = 0, counter2 = 0;
	int result_section;
	int realoffset[ntheader->file_header.NumberOfSections];
	for(n=1;n<=ntheader->file_header.NumberOfSections;n++) {
		IMAGE_SECTION_HEADER *secheader = (IMAGE_SECTION_HEADER *)(PE_HEADER + sizeof(IMAGE_NT_HEADERS) + section_size);
		section_size += sizeof(IMAGE_SECTION_HEADER);
		sprintf(section, "%c%c%c%c%c%c%c%c", secheader->Name[0], secheader->Name[1], secheader->Name[2], secheader->Name[3], secheader->Name[4], secheader->Name[5], secheader->Name[6], secheader->Name[7]);
		if(strcmp(sectionname, section) == 0) {
			printf("\tSection Name: %c%c%c%c%c%c%c%c\n", secheader->Name[0], secheader->Name[1], secheader->Name[2], secheader->Name[3], secheader->Name[4], secheader->Name[5], secheader->Name[6], secheader->Name[7]);
			printf("\tVirtualSize: %04x\n", secheader->VirtualSize);
			printf("\tVirtualAddress: %04x\n", secheader->VirtualAddress);
			printf("\tSizeOfRawData: %04x\n", secheader->SizeOfRawData);
			printf("\tRaw Data: %04x\n", secheader->PointerToRawData);
			printf("\tPointerToRelocations: %04x\n", secheader->PointerToRelocations);
			printf("\tPointerToLinenumbers: %04x\n", secheader->PointerToLinenumbers);
			printf("\tNumberOfRelocations: %02x\n", secheader->NumberOfRelocations);
			printf("\tNumberOfLinenumbers: %02x\n", secheader->NumberOfLinenumbers);
			printf("\tCharacteristics: %04x\n", secheader->Characteristics);
			printf("\t-------------------------\n");

			printf("\tPrinting Hex Dump For This Section\n");
			g=0;
			counter = 0;
			counter2 = 0;
			for(g = secheader->PointerToRawData ; g < (secheader->PointerToRawData + secheader->SizeOfRawData) ; g++) {
				if(counter2 == 0)
					printf("0x%04x\t\t", counter2);
				if(counter == 8){
					printf("  ");
				}else if(counter == 16){
					printf("\n");
					printf("0x%04x\t\t", counter2);
					counter = 0;
				}
				printf("%02x ", buffer[g]);
				counter++;
				counter2++;
			}
			printf("\n");
			realoffset[n] = secheader->VirtualAddress - secheader->PointerToRawData;
		}else if(strcmp(sectionname, section) != 0 && n < ntheader->file_header.NumberOfSections){
			continue;
		}

	}
}
