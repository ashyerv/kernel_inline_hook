# kernel_inline_hook
a base kernel inline hook lib (use LDE engine)


# how use :
ULONG NtOpenProcess_patch_size = 0;	//patch size
PUCHAR NtOpenProcess_head_n_byte = NULL;	//patch size buffer
PVOID ori_NtOpenProcess = NULL;	//origin Ntopenprocess



void go_hook_()
{
	NtOpenProcess_head_n_byte = (PUCHAR)HookKernelApi(GetFunctionAddr(L"NtOpenProcess"), (PVOID)Hooked_NtOpenProcess, &ori_NtOpenProcess, &NtOpenProcess_patch_size);
}

void go_unhook_()
{
	UnhookKernelApi(GetFunctionAddr(L"NtOpenProcess"), NtOpenProcess_head_n_byte, NtOpenProcess_patch_size);
}

//==============================================

NTSTATUS NTAPI DriverEntry(__in PDRIVER_OBJECT DriverObject, __in PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)DriverUnload;

	PLDR_DATA_TABLE_ENTRY64 ldr = (PLDR_DATA_TABLE_ENTRY64)(DriverObject->DriverSection);
	ldr->Flags |= 0x20;

	if (!lde_init())
		return STATUS_UNSUCCESSFUL;

	go_hook_();

	mydbg("drv installed");
	return STATUS_SUCCESS;
}
