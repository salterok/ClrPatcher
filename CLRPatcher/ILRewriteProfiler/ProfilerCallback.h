// ==++==

//   Copyright (c) Microsoft Corporation.  All rights reserved.

// ==--==

#ifndef __PROFILER_CALLBACK_H__
#define __PROFILER_CALLBACK_H__

#include "bootstrap/basehdr.h"
#include "ProfilerDTOTypes.h"
#include "mscoree.h"
#include "stdafx.h"
#include <corprof.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

extern const GUID __declspec(selectany) CLSID_PROFILER = {
	0xf704f0e6, 0x82c4, 0x4bc4,{ 0x9e, 0xd7, 0xa9, 0xe1, 0x46, 0x70, 0xbd, 0xd8 }
};
#define THREADING_MODEL "Both"
#define PROGID_PREFIX "PatcherProfiler"
#define COCLASS_DESCRIPTION ".Net process patcher"
#define PROFILER_GUID "{F704F0E6-82C4-4BC4-9ED7-A9E14670BDD8}"

#define BUFSIZE 2048

extern std::wofstream g_wLogFile;

extern WCHAR g_wszCmdFilePath[];
extern WCHAR g_wszResponseFilePath[];
extern WCHAR g_wszLogFilePath[];
extern WCHAR g_wszResultFilePath[];


// Implementation of the ICorProfilerCallback5 profiler API
class ProfilerCallback : public ICorProfilerCallback5
{
public:
	// instantiate an instance of the callback interface
	static COM_METHOD(HRESULT) CreateObject(REFIID riid, void **ppInterface);

	ProfilerCallback();
	~ProfilerCallback();
	HRESULT Init();

	// IUnknown
	COM_METHOD(ULONG)   AddRef();
	COM_METHOD(ULONG)   Release();
	COM_METHOD(HRESULT) QueryInterface(REFIID riid, void **ppInterface);

	// STARTUP/SHUTDOWN EVENTS
	virtual COM_METHOD(HRESULT) Initialize(IUnknown *pICorProfilerInfoUnk);
	COM_METHOD(HRESULT) Shutdown();
	HRESULT DllDetachShutdown();

	// Attach / Embed Events
	void AddMemberRefs(
		IMetaDataAssemblyImport * pAssemblyImport,
		IMetaDataAssemblyEmit * pAssemblyEmit,
		IMetaDataEmit * pEmit,
		ModuleInfo * pModuleInfo);

	// APPLICATION DOMAIN EVENTS
	COM_METHOD(HRESULT) AppDomainCreationStarted(AppDomainID appDomainID);
	COM_METHOD(HRESULT) AppDomainCreationFinished(AppDomainID appDomainID, HRESULT hrStatus);
	COM_METHOD(HRESULT) AppDomainShutdownStarted(AppDomainID appDomainID);
	COM_METHOD(HRESULT) AppDomainShutdownFinished(AppDomainID appDomainID, HRESULT hrStatus);

	// ASSEMBLY EVENTS
	COM_METHOD(HRESULT) AssemblyLoadStarted(AssemblyID assemblyID);
	COM_METHOD(HRESULT) AssemblyLoadFinished(AssemblyID assemblyID, HRESULT hrStatus);
	COM_METHOD(HRESULT) AssemblyUnloadStarted(AssemblyID assemblyID);
	COM_METHOD(HRESULT) AssemblyUnloadFinished(AssemblyID assemblyID, HRESULT hrStatus);

	// MODULE EVENTS
	COM_METHOD(HRESULT) ModuleLoadStarted(ModuleID moduleID);
	COM_METHOD(HRESULT) ModuleLoadFinished(ModuleID moduleID, HRESULT hrStatus);
	COM_METHOD(HRESULT) ModuleUnloadStarted(ModuleID moduleID);
	COM_METHOD(HRESULT) ModuleUnloadFinished(ModuleID moduleID, HRESULT hrStatus);
	COM_METHOD(HRESULT) ModuleAttachedToAssembly(ModuleID moduleID, AssemblyID assemblyID);

	// CLASS EVENTS
	COM_METHOD(HRESULT) ClassLoadStarted(ClassID classID);
	COM_METHOD(HRESULT) ClassLoadFinished(ClassID classID, HRESULT hrStatus);
	COM_METHOD(HRESULT) ClassUnloadStarted(ClassID classID);
	COM_METHOD(HRESULT) ClassUnloadFinished(ClassID classID, HRESULT hrStatus);
	COM_METHOD(HRESULT) FunctionUnloadStarted(FunctionID functionID);

	// JIT EVENTS
	void                SetILFunctionBodyForManagedHelper(ModuleID moduleID, mdMethodDef methodDef);
	COM_METHOD(HRESULT) JITCompilationStarted(FunctionID functionID, BOOL fIsSafeToBlock);
	COM_METHOD(HRESULT) JITCompilationFinished(FunctionID functionID, HRESULT hrStatus, BOOL fIsSafeToBlock);
	COM_METHOD(HRESULT) JITCachedFunctionSearchStarted(FunctionID functionID, BOOL *pbUseCachedFunction);
	COM_METHOD(HRESULT) JITCachedFunctionSearchFinished(FunctionID functionID, COR_PRF_JIT_CACHE result);
	COM_METHOD(HRESULT) JITFunctionPitched(FunctionID functionID);
	COM_METHOD(HRESULT) JITInlining(FunctionID callerID, FunctionID calleeID, BOOL *pfShouldInline);

	// ReJIT EVENTS
	COM_METHOD(HRESULT) ReJITCompilationStarted(FunctionID functionID, ReJITID rejitID, BOOL fIsSafeToBlock);
	COM_METHOD(HRESULT) ReJITCompilationFinished(FunctionID functionId, ReJITID rejitId, HRESULT hrStatus, BOOL fIsSafeToBlock);
	COM_METHOD(HRESULT) ReJITError(ModuleID moduleId, mdMethodDef methodId, FunctionID functionId, HRESULT hrStatus);
	COM_METHOD(HRESULT) GetReJITParameters(ModuleID moduleId, mdMethodDef methodId, ICorProfilerFunctionControl *pFunctionControl);
	COM_METHOD(HRESULT) MovedReferences2(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], SIZE_T cObjectIDRangeLength[]);
	COM_METHOD(HRESULT) SurvivingReferences2(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], SIZE_T   cObjectIDRangeLength[]);
	COM_METHOD(HRESULT) ConditionalWeakTableElementReferences(ULONG cRootRefs, ObjectID keyRefIds[], ObjectID valueRefIds[], GCHandleID rootIds[]);

	// THREAD EVENTS
	COM_METHOD(HRESULT) ThreadCreated(ThreadID threadID);
	COM_METHOD(HRESULT) ThreadDestroyed(ThreadID threadID);
	COM_METHOD(HRESULT) ThreadAssignedToOSThread(ThreadID managedThreadID, DWORD osThreadID);

	// REMOTING EVENTS
	// > Client-side events
	COM_METHOD(HRESULT) RemotingClientInvocationStarted();
	COM_METHOD(HRESULT) RemotingClientSendingMessage(GUID *pCookie, BOOL fIsAsync);
	COM_METHOD(HRESULT) RemotingClientReceivingReply(GUID *pCookie, BOOL fIsAsync);
	COM_METHOD(HRESULT) RemotingClientInvocationFinished();
	// > Server-side events
	COM_METHOD(HRESULT) RemotingServerInvocationStarted();
	COM_METHOD(HRESULT) RemotingServerReceivingMessage(GUID *pCookie, BOOL fIsAsync);
	COM_METHOD(HRESULT) RemotingServerSendingReply(GUID *pCookie, BOOL fIsAsync);
	COM_METHOD(HRESULT) RemotingServerInvocationReturned();

	// CONTEXT EVENTS
	COM_METHOD(HRESULT) UnmanagedToManagedTransition(FunctionID functionID, COR_PRF_TRANSITION_REASON reason);
	COM_METHOD(HRESULT) ManagedToUnmanagedTransition(FunctionID functionID, COR_PRF_TRANSITION_REASON reason);

	// SUSPENSION EVENTS
	COM_METHOD(HRESULT) RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason);
	COM_METHOD(HRESULT) RuntimeSuspendFinished();
	COM_METHOD(HRESULT) RuntimeSuspendAborted();
	COM_METHOD(HRESULT) RuntimeResumeStarted();
	COM_METHOD(HRESULT) RuntimeResumeFinished();
	COM_METHOD(HRESULT) RuntimeThreadSuspended(ThreadID threadid);
	COM_METHOD(HRESULT) RuntimeThreadResumed(ThreadID threadid);

	// GC EVENTS
	COM_METHOD(HRESULT) MovedReferences(ULONG cmovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[]);
	COM_METHOD(HRESULT) SurvivingReferences(ULONG cmovedObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[]);
	COM_METHOD(HRESULT) ObjectAllocated(ObjectID objectID, ClassID classID);
	COM_METHOD(HRESULT) ObjectsAllocatedByClass(ULONG classCount, ClassID classIDs[], ULONG objects[]);
	COM_METHOD(HRESULT) ObjectReferences(ObjectID objectID, ClassID classID, ULONG cObjectRefs, ObjectID objectRefIDs[]);
	COM_METHOD(HRESULT) RootReferences(ULONG cRootRefs, ObjectID rootRefIDs[]);
	COM_METHOD(HRESULT) GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason);
	COM_METHOD(HRESULT) GarbageCollectionFinished();
	COM_METHOD(HRESULT) STDMETHODCALLTYPE FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID);
	COM_METHOD(HRESULT) STDMETHODCALLTYPE RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[]);
	COM_METHOD(HRESULT) STDMETHODCALLTYPE HandleCreated(UINT_PTR handleId, ObjectID initialObjectId);
	COM_METHOD(HRESULT) STDMETHODCALLTYPE HandleDestroyed(UINT_PTR handleId);

	// EXCEPTION EVENTS
	// > Exception creation
	COM_METHOD(HRESULT) ExceptionThrown(ObjectID thrownObjectID);
	// > Search phase
	COM_METHOD(HRESULT) ExceptionSearchFunctionEnter(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionSearchFunctionLeave();
	COM_METHOD(HRESULT) ExceptionSearchFilterEnter(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionSearchFilterLeave();
	COM_METHOD(HRESULT) ExceptionSearchCatcherFound(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionCLRCatcherFound();
	COM_METHOD(HRESULT) ExceptionCLRCatcherExecute();
	COM_METHOD(HRESULT) ExceptionOSHandlerEnter(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionOSHandlerLeave(FunctionID functionID);
	// > Unwind phase
	COM_METHOD(HRESULT) ExceptionUnwindFunctionEnter(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionUnwindFunctionLeave();
	COM_METHOD(HRESULT) ExceptionUnwindFinallyEnter(FunctionID functionID);
	COM_METHOD(HRESULT) ExceptionUnwindFinallyLeave();
	COM_METHOD(HRESULT) ExceptionCatcherEnter(FunctionID functionID, ObjectID objectID);
	COM_METHOD(HRESULT) ExceptionCatcherLeave();

	// COM CLASSIC WRAPPER
	COM_METHOD(HRESULT)  COMClassicVTableCreated(ClassID wrappedClassID, REFGUID implementedIID, void *pVTable, ULONG cSlots);
	COM_METHOD(HRESULT)  COMClassicVTableDestroyed(ClassID wrappedClassID, REFGUID implementedIID, void *pVTable);
	COM_METHOD(HRESULT) STDMETHODCALLTYPE ThreadNameChanged(ThreadID threadId, ULONG cchName, __in_ecount_opt(cchName) WCHAR name[]);

	// ATTACH EVENTS
	COM_METHOD(HRESULT) STDMETHODCALLTYPE InitializeForAttach(IUnknown *pICorProfilerInfoUnk, void *pvClientData, UINT cbClientData);
	COM_METHOD(HRESULT) ProfilerAttachComplete();
	COM_METHOD(HRESULT) ProfilerDetachSucceeded();

	// OUT-OF-THREAD REQUEST CALLS
	HRESULT CallRequestReJIT(UINT cFunctionsToRejit, ModuleID * rgModuleIDs, mdMethodDef * rgMethodIDs);
	HRESULT CallRequestRevert(UINT cFunctionsToRejit, ModuleID * rgModuleIDs, mdMethodDef * rgMethodIDs);

	// P-INVOKED FUNCTIONS
	void NtvEnteredFunction(ModuleID moduleIDCur, mdMethodDef mdCur, int nVersionCur);
	void NtvExitedFunction(ModuleID moduleIDCur, mdMethodDef mdCur, int nVersionCur);

private:
	HRESULT AddPInvoke(IMetaDataEmit * pEmit, mdTypeDef td, LPCWSTR wszName, mdModuleRef modrefTarget, mdMethodDef * pmdPInvoke);
	HRESULT GetSecuritySafeCriticalAttributeToken(IMetaDataImport * pImport, mdMethodDef * pmdSafeCritical);
	HRESULT AddManagedHelperMethod(IMetaDataEmit * pEmit, mdTypeDef td, LPCWSTR wszName, mdMethodDef mdTargetPInvoke, ULONG rvaDummy, mdMethodDef mdSafeCritical, mdMethodDef * pmdHelperMethod);
	void AddHelperMethodDefs(IMetaDataImport * pImport, IMetaDataEmit * pEmit);
	BOOL FindMscorlibReference(IMetaDataAssemblyImport * pAssemblyImport, mdAssemblyRef * rgAssemblyRefs, ULONG cAssemblyRefs, mdAssemblyRef * parMscorlib);

	// Pipe operations with the GUI
	void LaunchLogListener(LPCWSTR wszPath);
	std::vector<ShadowStackFrameInfo> * GetShadowStack();
	void GetClassAndFunctionNamesFromMethodDef(IMetaDataImport * pImport, ModuleID moduleID, mdMethodDef methodDef, LPWSTR wszTypeDefName, ULONG cchTypeDefName, LPWSTR wszMethodDefName, ULONG cchMethodDefName);

public:
	bool GetAllocationLoggingActive();
	void SetAllocationLoggingActive(bool active);
	bool GetCallLoggingActive();
	void SetCallLoggingActive(bool active);
	bool DumpHeap(DWORD timeOut);
	void LogComment(const wchar_t *commentString);
	void SendMessageToUI(const char *message);



	BOOL ReplaceClass(IDToInfoMap<ModuleID, ModuleInfo> * mMap, LPCWSTR moduleName, LPCWSTR sourceClassName, LPCWSTR replaceClassName);
	BOOL GetMethodsInfoFromNames(IDToInfoMap<ModuleID, ModuleInfo> * mMap, LPCWSTR wszModule, LPCWSTR wszClass, LPCWSTR wszFunction,
		mdMethodDef *methodDef, ModuleInfo *moduleInfo);


private:
	ICorProfilerInfo4 * m_pProfilerInfo;

	volatile long m_refCount;
	ModuleID m_modidMscorlib;
	BOOL m_fInstrumentationHooksInSeparateAssembly;
	DWORD m_dwThresholdMs;
	DWORD m_dwShadowStackTlsIndex;

	/* If the instrumented code must call into managed helpers that we pump into mscorlib (as
	* opposed to calling into managed helpers statically compiled into ProfilerHelper.dll), then
	* the tokens are used to refer to the helpers as they will be in modified mscorlib metadata. */
	mdMethodDef m_mdIntPtrExplicitCast;
	mdMethodDef m_mdEnterPInvoke;
	mdMethodDef m_mdExitPInvoke;
	mdMethodDef m_mdEnter;
	mdMethodDef m_mdExit;
};

// Note: Generally you should not have a single, global callback implementation, as that
// prevents your profiler from analyzing multiply loaded in-process side-by-side CLRs.
// However, this profiler implements the "profile-first" alternative of dealing with
// multiple in-process side-by-side CLR instances. First CLR to try to load us into this
// process wins; so there can only be one callback implementation created. (See
// ProfilerCallback::CreateObject.)
extern ProfilerCallback *g_pCallbackObject; // global reference to callback object

#endif