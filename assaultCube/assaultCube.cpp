// assaultCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main()
{
	std::cout << "--- Assault Cube cheat by Kuzenet ---\n\n\n" << std::endl;
	// get proc id of the target proces
	DWORD procId = GetProcId(L"ac_client.exe");
	std::cout << "Process ID: 0x" << std::hex << procId << std::endl;
	// get module base address
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");
	// get handle to process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	// resolve base address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10F4F4;
	std::cout << "dynamicPtrBaseAddr: " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;
	// resolve our ammo pointer chain
	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
	std::cout << "ammoAddr: " << "0x" << std::hex << ammoAddr << std::endl;
	// read ammo value
	int ammoValue = 0;
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "Current ammo = " << std::dec << ammoValue << std::endl;
	// write ammo value
	int newAmmo = 1337;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
	// read out again
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

	getchar();
	return  0;
}
