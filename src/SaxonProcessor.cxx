#include <v8.h>
#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <jni.h>
extern "C" {
    jint(JNICALL * JNI_GetDefaultJavaVMInitArgs_func) (void *args);
    jint(JNICALL * JNI_CreateJavaVM_func) (JavaVM **pvm, void **penv, void *args);
}
#include "SaxonApiException.hpp"
#include "SaxonProcessor.hpp"
#include "XsltProcessor.hpp"

/*
 * Load dll.
 */
HANDLE loadDll(char* name) {
#ifndef __linux__
    HANDLE hDll = LoadLibrary(_T("C:\\Program Files\\Saxonica\\SaxonHEC0.3\\libsaxon.dll")); // Used for windows only
#else
    HANDLE hDll = LoadLibrary(name);
#endif

    if (!hDll) {
        printf("Unable to load %s\n", name);
        //  exit(1);
    }
#ifdef DEBUG
    printf("%s loaded\n", name);
#endif

    return hDll;
}

int saxon::SaxonProcessor::jvmCreated = 0;
JNIEnv *saxon::SaxonProcessor::env;
JavaVM *saxon::SaxonProcessor::jvm;

v8::Persistent<v8::FunctionTemplate> saxon::SaxonProcessor::Constructor;

void saxon::SaxonProcessor::newTransformer(const v8::FunctionCallbackInfo<Value>& args) {
    Local<Object> instance = saxon::XsltProcessor::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};
v8::Persistent<v8::FunctionTemplate> saxon::XsltProcessor::Constructor;

/*
 * Initialize JET run-time.
 */
void initJavaRT(HANDLE myDllHandle, JavaVM** pjvm, JNIEnv** penv) {
    if (saxon::SaxonProcessor::jvmCreated != 0) {
        return;
    }

    int result;
    JavaVMInitArgs args;
    JNI_GetDefaultJavaVMInitArgs_func =
            (jint(JNICALL *) (void *args))
#ifndef __linux__
            GetProcAddress((HMODULE) myDllHandle, "JNI_GetDefaultJavaVMInitArgs");
#else
            GetProcAddress(myDllHandle, "JNI_GetDefaultJavaVMInitArgs");
#endif

    JNI_CreateJavaVM_func =
            (jint(JNICALL *) (JavaVM **pvm, void **penv, void *args))

#ifndef __linux__
            GetProcAddress((HMODULE) myDllHandle, "JNI_CreateJavaVM");
#else
            GetProcAddress(myDllHandle, "JNI_CreateJavaVM");

#endif

    if (!JNI_GetDefaultJavaVMInitArgs_func) {
        char dllname[] =
#ifdef __linux__
                "/usr/lib/libsaxon.so";
#else
                "C:\\Program Files\\Saxonica\\SaxonHEC0.3\\libsaxon.dll";
#endif
        printf("%s doesn't contain public JNI_GetDefaultJavaVMInitArgs\n", dllname);
        exit(1);
    }

    if (!JNI_CreateJavaVM_func) {
        char dllname[] =
#ifdef __linux__
                "/usr/lib/libsaxon.so";
#else
                "C:\\Program Files\\Saxonica\\SaxonHEC0.3\\libsaxon.dll";
#endif
        printf("%s doesn't contain public JNI_CreateJavaVM\n", dllname);
        exit(1);
    }

    memset(&args, 0, sizeof (args));

    args.version = JNI_VERSION_1_2;
    result = JNI_GetDefaultJavaVMInitArgs_func(&args);
    if (result != JNI_OK) {
        std::cerr << "JNI_GetDefaultJavaVMInitArgs() failed with result" << result << std::endl;
        exit(1);
    }

    /*
     * NOTE: no JVM is actually created
     * this call to JNI_CreateJavaVM is intended for JET RT initialization
     */
    result = JNI_CreateJavaVM_func(pjvm, (void **) penv, &args);
    if (result != JNI_OK) {
        std::cerr << "JNI_CreateJavaVM() failed with result" << result << std::endl;
        exit(1);
    }
#ifdef DEBUG
    printf("JET RT initialized\n");
#endif
    fflush(stdout);
    saxon::SaxonProcessor::jvmCreated++;
}
