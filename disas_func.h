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

void PrintToFile(char *instruction_ascii){
	FILE *WrFile;
	WrFile = fopen("as_output.txt", "a");
	if(WrFile ==NULL){
		perror("cannot open file for write\n");
		exit(1);
	}

	fprintf(WrFile, instruction_ascii);
	fprintf(WrFile, "\n");
	fclose(WrFile);
}


void CheckFileExists(){
	if (fopen("as_output.txt", "r") != NULL){
		printf("Removing Old File First\n");
		remove("as_output.txt");
	}
}