# kernel_inline_hook
a base kernel inline hook lib (use LDE engine)


# how use :
```
ULONG NtOpenProcess_patch_size = 0;
PUCHAR NtOpenProcess_head_n_byte = NULL;
PVOID ori_NtOpenProcess = NULL;`
```
```
NTSTATUS NTAPI DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UnhookKernelApi(GetFunctionAddr(L"NtOpenProcess"), NtOpenProcess_head_n_byte, NtOpenProcess_patch_size);
	return STATUS_SUCCESS;
}
```
```
NTSTATUS NTAPI DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	//blabla...
	if (!lde_init())
		return STATUS_UNSUCCESSFUL;

	NtOpenProcess_head_n_byte = (PUCHAR)HookKernelApi(GetFunctionAddr(L"NtOpenProcess"), 
	(PVOID)Hooked_NtOpenProcess, 
	&ori_NtOpenProcess, 
	&NtOpenProcess_patch_size);

	return STATUS_SUCCESS;
}
```
