#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>


int __cdecl _tmain(int argc, TCHAR* argv[])
{
	HANDLE hFile;
	char DataBuffer[] = "";
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	printf("\n");
	if (argc != 2)
	{
		printf("Usage Error:\tIncorrect number of arguments\n\n");
		printf("touch <file_name>\n");
		return 1;
	}

	hFile = CreateFile(argv[1],                // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,             // create new file always 
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout<<"Terminal failure: Unable to open file "<< argv[1] <<"for write."<<std::endl;
		return 1;
	}

	//printf("Writing %d bytes to %s.\n", dwBytesToWrite, argv[1]);

	bErrorFlag = WriteFile(
		hFile,           // open file handle
		DataBuffer,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);            // no overlapped structure

	if (FALSE == bErrorFlag)
	{
		
		printf("Terminal failure: Unable to write to file.\n");
	}
	else
	{
		if (dwBytesWritten != dwBytesToWrite)
		{
			// This is an error because a synchronous write that results in
			// success (WriteFile returns TRUE) should write all data as
			// requested. This would not necessarily be the case for
			// asynchronous writes.
			printf("Error: dwBytesWritten != dwBytesToWrite\n");
		}
		else
		{
			//printf("Wrote %d bytes to %s successfully.\n", dwBytesWritten, argv[1]);
		}
	}

	CloseHandle(hFile);
	return 0;
}