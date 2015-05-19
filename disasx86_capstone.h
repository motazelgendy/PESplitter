int DisassembleCap(unsigned char *buffer, char opt, unsigned char *filename, int file_len){
	printf("file name is : %s\n", filename);
	printf("buffer is %s\n", buffer);
	printf("option is %c\n", opt);
	char *buf = (char *)malloc(file_len);
	int i=0;
	int buf_len = 0;
	for(i=0;i!=file_len;i++){
		buf[i] = buffer[34230+i];
		buf_len++;
		// printf("%c\n", buf[i]);
	}

	csh handle;
	cs_insn *insn;
	size_t count;
	printf("buffer size is %d\n", file_len);
	printf("buf len is %d\n", buf_len);
	if(cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK)
		return -1;
	// cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
	// cs_option(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_INTEL);
	cs_option(handle, CS_OPT_SKIPDATA, CS_OPT_ON);
	count = cs_disasm(handle, buf, buf_len, 0, 0, &insn);
	if(count > 0){
		size_t j;
		for(j=0;j<count;j++){
			printf("\t%s\t\t%s\n", insn[j].mnemonic, insn[j].op_str);
		}
		cs_free(insn, count);
	}else{
		printf("failed disassemble\n");

	}

	cs_close(&handle);
	return 0;
}