// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME libdIClassDictionaries

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/VBFTaggerEvent.h"
#include "include/VBFTaggerHists.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *VBFTaggerEvent_Dictionary();
   static void VBFTaggerEvent_TClassManip(TClass*);
   static void *new_VBFTaggerEvent(void *p = 0);
   static void *newArray_VBFTaggerEvent(Long_t size, void *p);
   static void delete_VBFTaggerEvent(void *p);
   static void deleteArray_VBFTaggerEvent(void *p);
   static void destruct_VBFTaggerEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::VBFTaggerEvent*)
   {
      ::VBFTaggerEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::VBFTaggerEvent));
      static ::ROOT::TGenericClassInfo 
         instance("VBFTaggerEvent", "include/VBFTaggerEvent.h", 14,
                  typeid(::VBFTaggerEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &VBFTaggerEvent_Dictionary, isa_proxy, 4,
                  sizeof(::VBFTaggerEvent) );
      instance.SetNew(&new_VBFTaggerEvent);
      instance.SetNewArray(&newArray_VBFTaggerEvent);
      instance.SetDelete(&delete_VBFTaggerEvent);
      instance.SetDeleteArray(&deleteArray_VBFTaggerEvent);
      instance.SetDestructor(&destruct_VBFTaggerEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::VBFTaggerEvent*)
   {
      return GenerateInitInstanceLocal((::VBFTaggerEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::VBFTaggerEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *VBFTaggerEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::VBFTaggerEvent*)0x0)->GetClass();
      VBFTaggerEvent_TClassManip(theClass);
   return theClass;
   }

   static void VBFTaggerEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_VBFTaggerEvent(void *p) {
      return  p ? new(p) ::VBFTaggerEvent : new ::VBFTaggerEvent;
   }
   static void *newArray_VBFTaggerEvent(Long_t nElements, void *p) {
      return p ? new(p) ::VBFTaggerEvent[nElements] : new ::VBFTaggerEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_VBFTaggerEvent(void *p) {
      delete ((::VBFTaggerEvent*)p);
   }
   static void deleteArray_VBFTaggerEvent(void *p) {
      delete [] ((::VBFTaggerEvent*)p);
   }
   static void destruct_VBFTaggerEvent(void *p) {
      typedef ::VBFTaggerEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::VBFTaggerEvent

namespace ROOT {
   static TClass *vectorlEVBFTaggerEventgR_Dictionary();
   static void vectorlEVBFTaggerEventgR_TClassManip(TClass*);
   static void *new_vectorlEVBFTaggerEventgR(void *p = 0);
   static void *newArray_vectorlEVBFTaggerEventgR(Long_t size, void *p);
   static void delete_vectorlEVBFTaggerEventgR(void *p);
   static void deleteArray_vectorlEVBFTaggerEventgR(void *p);
   static void destruct_vectorlEVBFTaggerEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<VBFTaggerEvent>*)
   {
      vector<VBFTaggerEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<VBFTaggerEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<VBFTaggerEvent>", -2, "vector", 216,
                  typeid(vector<VBFTaggerEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEVBFTaggerEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<VBFTaggerEvent>) );
      instance.SetNew(&new_vectorlEVBFTaggerEventgR);
      instance.SetNewArray(&newArray_vectorlEVBFTaggerEventgR);
      instance.SetDelete(&delete_vectorlEVBFTaggerEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEVBFTaggerEventgR);
      instance.SetDestructor(&destruct_vectorlEVBFTaggerEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<VBFTaggerEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<VBFTaggerEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEVBFTaggerEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<VBFTaggerEvent>*)0x0)->GetClass();
      vectorlEVBFTaggerEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEVBFTaggerEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEVBFTaggerEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<VBFTaggerEvent> : new vector<VBFTaggerEvent>;
   }
   static void *newArray_vectorlEVBFTaggerEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<VBFTaggerEvent>[nElements] : new vector<VBFTaggerEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEVBFTaggerEventgR(void *p) {
      delete ((vector<VBFTaggerEvent>*)p);
   }
   static void deleteArray_vectorlEVBFTaggerEventgR(void *p) {
      delete [] ((vector<VBFTaggerEvent>*)p);
   }
   static void destruct_vectorlEVBFTaggerEventgR(void *p) {
      typedef vector<VBFTaggerEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<VBFTaggerEvent>

namespace {
  void TriggerDictionaryInitialization_ClassDictionaries_Impl() {
    static const char* headers[] = {
"include/VBFTaggerEvent.h",
"include/VBFTaggerHists.h",
0
    };
    static const char* includePaths[] = {
"/user/anmalara/WorkingArea/CMSSW_10_6_28/src/LEAF",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc700/lcg/root/6.14.09-pafccj6/include",
"/storage_mnt/storage/user/anmalara/WorkingArea/CMSSW_10_6_28/src/LEAF/VBFTagger/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ClassDictionaries dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/VBFTaggerEvent.h")))  VBFTaggerEvent;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ClassDictionaries dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/VBFTaggerEvent.h"
#include "include/VBFTaggerHists.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"VBFTaggerEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ClassDictionaries",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ClassDictionaries_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ClassDictionaries_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ClassDictionaries() {
  TriggerDictionaryInitialization_ClassDictionaries_Impl();
}
