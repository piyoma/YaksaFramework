﻿
// Copyright (c) 2020 The YaksaFramework Authors piyoma. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef __yaksa_framework_h___
#define __yaksa_framework_h___

////--꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༺TONOSHIKI PIYOMA༻༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂
////           
////          ꧁༒༒༒༒༒༒༒༒༒༒༒༒༺☼☽☪☭----✞----☭☪☽☼༻༒༒༒༒༒༒༒༒༒༒༒༒꧂          
////
////                  A cross-platform GUI Framework Wrapped Chromium that Can embedded All Systems and Platforms.
////                  eg. Windows, linux, macOS, Android, iOS, Unity, UnrealEngine4, Qt, and etc.
////                  2020/04/29 piyoma
////                  break;
////                  ༺GitHub https://github.com/piyoma/YaksaFramework༻    
////       
////                                           
////--꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂


#if defined(OS_WIN)
#include <windows.h>
#else 
#if defined(OS_LINUX)
#include <stdio.h>  
#include <stdlib.h>   
#include <dlfcn.h>   
#endif 
#endif

#include <string>

namespace Yaksa{

	namespace Api {

#if defined(_M_IX86) || defined (_M_AMD64)

#pragma pack(push,4)

	template<typename type> struct struct_type {
		using  type_t = type;
	};
	template <typename WrapperType = void*>
		using voidType =
			typename struct_type<WrapperType>::type_t;

#pragma pack(pop)

#else
	//NOIMPLEMENT
#endif  // _M_IX86 || _M_AMD64

	template<typename type> struct template_type {
		using  type_t = type;
	};
	template<typename ClassType,
		typename Type> struct TemplateType {

		using _ClassType = typename template_type<ClassType>::type_t;
		using _ClassPtr = typename template_type<_ClassType *>::type_t;
		using _Type = typename template_type<Type>::type_t;
		using _TypePtr = typename template_type<Type*>::type_t;

	};
#if defined(OS_WIN)
	template <typename WrapperType, typename Type = HWND>
	using ViewTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
#else
	template <typename WrapperType, typename Type = void*>
	using ViewTypeDefine =
		typename TemplateType<WrapperType, Type>::_Type;
#endif

#if defined(OS_WIN)
	template <typename WrapperType, typename Type = HMODULE>
	using ModuleHandleDefine =
		typename TemplateType<WrapperType, Type>::_Type;
#else
	template <typename WrapperType, typename Type = void*>
	using ModuleHandleType =
		typename TemplateType<WrapperType, Type>::_Type;
#endif

#ifndef YAKSA_DEFINE_TYPE

//-------------------------꧁༒༒༒DEFINE TYPES༻༒༒༒-------------------------꧂

#define YAKSA_DEFINE_TYPE(NAME, obj, type_def, type, ptr_det, ptr);\
				template <typename WrapperType, typename Type = obj>\
						using NAME = typename TemplateType<WrapperType, Type>::_Type;\
				template <typename WrapperType, typename Type = type>\
						using type_def = typename TemplateType<WrapperType, Type>::_Type;\
				template <typename WrapperType, typename Type = sub>\
						using ptr_det = typename TemplateType<WrapperType, Type>::_Type*;

#endif // !YAKSA_DEFINE_TYPE

	YAKSA_DEFINE_TYPE(WideStringTypeDefine, std::wstring, WCharTypeDefine, wchar_t, WCharTypePtrDefine, wchar_t*)
	YAKSA_DEFINE_TYPE(StringTypeDefine, std::string, CharTypeDefine, char, CharTypePtrDefine, char*)

	template <typename Type,
		typename WrapperType =
		TemplateType<Type, void>,
		//define NativeView
		typename NativeViewType = ViewTypeDefine<Type>,
		typename NativeViewType_ = NativeViewType,
		//define NativeHandle
		typename NativeModuleHandle = ModuleHandleDefine<Type>,
		typename NativeModuleHandle_ = NativeModuleHandle,
		//define wchar_t
		typename WCharStrType = WideStringTypeDefine<Type>,
		typename WCharStrType_ = WCharStrType,
		//define std::string
		typename CharStrType = StringTypeDefine<Type>,
		typename CharStrType_  = CharStrType,
		//define char
		typename CharType = CharTypeDefine<Type>,
		typename CharType_ = CharType> struct WrapperTypes {

		using _Myt = WrapperType;
		using _NativeViewType = NativeViewType;
		using _NativeModuleHandle = NativeModuleHandle_;
		using _CharStrType = CharStrType_;
		using _WCharStrType = WCharStrType_;
		using _CharType = CharType_;
	};
	template<typename L>
	struct TypeLambdaTraits : TypeLambdaTraits<decltype(&L::operator())> {};
	template<typename C, typename R, typename... A>
	struct TypeLambdaTraits<R(C::*)(A...) const> {
	};
	template<typename C, typename R, typename A>
	struct TypeLambdaTraits<R(C::*)(A) const> {
		static const bool valid = true;
		using TypeArg = typename std::remove_const<typename std::remove_reference<A>::type>::type;
		using TypeR = R;
	};

	using NativeView =
		WrapperTypes<void>::_NativeViewType;
	using NativeModuleHandle = 
		WrapperTypes<void>::_NativeModuleHandle;
	using type_str = 
		WrapperTypes<void>::_CharStrType;
	using type_wstr = 
		WrapperTypes<void>::_WCharStrType;
	using type_char = 
		WrapperTypes<void>::_CharType;

#if defined(OS_WIN)
#if defined(YAKSA_BUILD)
	extern "C" int __declspec(dllexport)
		cdecl YaksaExec(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid);
#else
	extern "C" int __declspec(dllimport)
		cdecl YaksaExec(void* obj, void* cmd, void* arg,
			void* callback, void* obj_invoke, int msgid);
#endif
#endif //OS_WIN

//////////MACRO PIYOMA DEFINE//////////

#ifndef _STRING_Const_Ptr_
#define _STRING_Const_Ptr_(val)  val.c_str()
#endif

//////////MACRO FIN//////////

	typedef int(*InitPackageModule)(void* callback);

	typedef  int(*execPackageObjectFunc)(void* obj, void* cmd, void* arg,
		void* callback, void* obj_invoke, int msgid);

	typedef int(*onPackageCallback) (type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid);

	typedef int(*typeCallback) (type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid);


	template <typename type = type_char * , typename value_type = const char*>
	type cast_type(value_type v)
	{
		return reinterpret_cast<type>(const_cast<char*>(v));
	}
#ifndef value_param

#define  value_param(v) cast_type<>(v)

#endif

	template <typename type> class defineTemplate
	{
	public:
		typedef  type* defineType;
		typedef  typeCallback callbackType;

		static type* GetInstance()
		{

			static type* instance = nullptr;

			if (instance == nullptr)
			{

				instance = new (std::nothrow) type();

			}
			return instance;
		}

		static callbackType GetObject()
		{
			defineType obj = type::GetInstance();

			if (obj)
			{
				return obj->Get();
			}
			return nullptr;
		}
		static int message_id()
		{
			defineType obj = type::GetInstance();

			if (obj)
			{
				return obj->msg_id();
			}
			return 0;
		}
	};
	class getPackageCallback :
		public defineTemplate<getPackageCallback>
	{
	public:

		getPackageCallback() :message_id_(0), other_module(nullptr) {};

		virtual ~getPackageCallback() {};


		typeCallback Get() { return other_module; };
		void Set(typeCallback v) { other_module = v; };

		int msg_id()
		{
			message_id_ += 1;
			return message_id_;
		}

	private:

		int message_id_;
		typeCallback other_module;
	};

#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#define DATA_DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)
#define  DATA_CONNECTOR_OBJ_NAME(NAME) virtual const char* obj_id() \
	override {return NAME;}
#ifndef DATA_DECL
#define  DATA_DECL(name) void name(type_char* obj, type_char* cmd, type_char* data_type,\
type_char* data, int len, int msgid);
#endif

#ifndef EXPORT_DECL
#define  EXPORT_DECL(name, ret, ...) void name(type_char* obj, type_char* cmd, type_char* data_type,\
type_char* data, int len, int msgid);
#endif

#ifndef dataPackageExec
#define  dataPackageExec(func, obj, cmd, arg, callback, handler, msgid, type) \
	func(obj, cmd, arg, callback, dataBind<type>(callback, this), msgid)
#endif

#ifndef CallExec //local 
#define CallExec(obj, cmd, arg, handler)\
	dataPackageExec(YaksaCall, obj, cmd, arg, nullptr, handler, -1, nullptr, -1)
#endif 

#ifndef DispatchEvent
#define DispatchEvent(obj, event_name, arg)\
	dataPackageExec(YaksaCall, obj, event_name, arg, nullptr, nullptr, -1, nullptr, -1)
#endif 

#ifndef CallRPC //remote
#define RpcExec(obj, cmd, arg, handler)\
	dataPackageExec(YaksaCall, obj, cmd, arg, nullptr, handler, -1, nullptr, -1)
#endif 

#ifndef dataExecNULL
#define  dataExecNULL(YaksaCall, obj, cmd, arg) \
	func(obj, cmd, arg, 0, 0, 0);
#endif

#ifndef YaksaCallee
#define YaksaCallee(type, callback, callee)\
	dataBind<type>(callback, callee)
#endif // !YaksaCallback

	/*
		꧁༒༒༒༒༒༒༒༒༒༒༒༒༺TONOSHIKI PIYOMA༻༒༒༒༒༒༒༒༒༒༒༒༒꧂
          
					

			class Foo
			{
					public:
					Foo() {}
					~Foo(){}
					void asnyc_work()
					{
						//////////Load and CallModule//////////

						component.Load(L"LocalPath", L"Yaksa.Module.Bar");

						component.exec(value_param("FooObj"), 
						value_param("bar"), 0,
						&Foo::Callee, this, 0);
	

					}
					void Callee(type_char* obj, type_char* cmd, type_char* data_type,
							type_char* data, int len, int msgid)
					{
							//////////Do Some Asnyc Works//////////
					}

					private:
					SingleComponent<Foo>  component;
			};

	*/
	class dataObjEventHandler;

	class dataRefBase
	{
	public:
		bool HasOneRef() const { return ref_count_ == 1; }
		unsigned int GetRefCounted() { return ref_count_; }
	protected:
		dataRefBase() : ref_count_(0) {};
		virtual ~dataRefBase() {};

		virtual void add_ref() const
		{
			++ref_count_;
		}

		virtual bool release() const
		{

			if (--ref_count_ == 0)
			{
				return true;
			}
			return false;
		}

	private:
		mutable int ref_count_;
		DATA_DISALLOW_COPY_AND_ASSIGN(dataRefBase);
	};
	template<typename T>
	class dataRefCounter : public dataRefBase
	{
	public:
		dataRefCounter() {}
		~dataRefCounter() {}

		void AddRef() const
		{
			dataRefBase::add_ref();
		}

		void Release() const
		{
			if (dataRefBase::release())
			{
				delete static_cast<const T*>(this);
			}
		}

	private:
		DATA_DISALLOW_COPY_AND_ASSIGN(dataRefCounter<T>);
	};
	template<typename type>
	class dataObj
		: public dataRefCounter<type>
	{
	public:

		dataObj() {}
		~dataObj() {}
		virtual void AddEventHandler(dataObjEventHandler* handler) {}
		virtual const char* obj_id() { return ""; }

	};

	class  dataObjEventHandler
		: public  dataObj<dataObjEventHandler>
	{
	public:

		dataObjEventHandler()
		{
			AddRef();
		};

		virtual ~dataObjEventHandler() {};

		virtual void invoke(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid) = 0;

	};
	template<typename P, typename T>
	class objEventHandlerImpl : public dataObjEventHandler
	{
	public:
		typedef void (T::* Sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid);


		objEventHandlerImpl(P* obj, Sig sig) : obj_(obj), func_(sig) {};

		virtual void invoke(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid)
		{
			(obj_->*func_)(obj, cmd, data_type, data, len, msgid);

			Release();
		};

	private:
		Sig func_;
		T*  obj_;
	};

	template <typename P, typename T = P>
	objEventHandlerImpl<P, T>* dataBind(void (T::* sig)(type_char* obj, type_char* cmd, type_char* data_type,
		type_char* data, int len, int msgid), P* o)
	{
		return new objEventHandlerImpl<P, T>(o, sig);
	};
	
	template<typename type = dataObjEventHandler>
	class dataPackageTemplate {
	public:
		typedef dataObjEventHandler objType;
		typedef objType* poiter_type;
		typedef poiter_type objCallbackType_;
	};
	typedef dataPackageTemplate<> dataPackage;

	typedef dataPackage::objCallbackType_ objCallbackType;
	template <typename T>
	class TypeCast {
		typedef void (T::* sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid); 
	};
	template<typename Obj> class SingleComponent{
	public:
		typedef void (Obj::* Sig)(type_char* obj, type_char* cmd, type_char* data_type,
			type_char* data, int len, int msgid);

		SingleComponent() {};
		~SingleComponent() {};

#if defined(OS_WIN)
		bool Load(type_wstr path, type_wstr module_name){

			NativeModuleHandle module
				= nullptr;
			type_wstr dllPath =
				path + module_name; 
			dllPath += L".dll";
			module = LoadLibraryW(
				_STRING_Const_Ptr_(dllPath)
			);
			if (module)
			{
				execPackageObjectFunc execPackageObj 
					= (execPackageObjectFunc)
				GetProcAddress(module, "YaksaExec");

				return true;
			}
			return false;
		 }
#else
		bool Load(type_char* path, type_char*module_name) {

			NativeModuleHandle module
				= nullptr;
			type_str dllPath = path;
			path += module_name;
			dllPath += L".so";
			module = dlopen(_STRING_Const_Ptr_(dllPath), RTLD_LAZY);

			);
			if (module)
			{
				execPackageObjectFunc execPackageObj
					= (execPackageObjectFunc)
					dlsym(module, "YaksaExec");

				return true;
			}
			return false;
		}
#endif
		
		void exec(void* obj, void* cmd, void* arg,
			Sig callback, Obj* caller, int msgid)
		{
			if (execPackageObj) {

					execPackageObj(obj, cmd, arg, YaksaCallee(Obj, callback, caller), 0, msgid);
			}
		}
	private:
		execPackageObjectFunc execPackageObj = nullptr;
	};




	}//dataConnectApi

}//Yaksa

#endif
