#pragma once


typedef INT(*LDE_DISASM)(PVOID address, INT bits);
extern LDE_DISASM lde_disasm;
bool lde_init();

PVOID GetFunctionAddr(PCWSTR FunctionName);
PVOID HookKernelApi(IN PVOID ApiAddress, IN PVOID Proxy_ApiAddress, OUT PVOID* Original_ApiAddress, OUT ULONG* PatchSize);
VOID UnhookKernelApi(IN PVOID ApiAddress, IN PVOID OriCode, IN ULONG PatchSize);
