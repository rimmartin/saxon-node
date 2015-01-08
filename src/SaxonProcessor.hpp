#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <memory>

#include <jni.h>
#include "XdmValue.h"


#ifdef __linux__
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define HANDLE void*
#define LoadLibrary(x) dlopen(x, RTLD_LAZY)
#define GetProcAddress(x,y) dlsym(x,y)
#else
#include <windows.h>
#endif

extern "C" {
    HANDLE loadDll(char* name);
    void initJavaRT(HANDLE myDllHandle, JavaVM** pjvm, JNIEnv** penv);
}

namespace saxon {

    using namespace v8;
    //using namespace node;

    class XsltProcessor;

    class SaxonProcessor : public node::ObjectWrap {
        friend class XsltProcessor;
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            std::cout << "Initialize 1 " << std::endl;
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "newTransformer", newTransformer);
            NODE_SET_PROTOTYPE_METHOD(t, "newXQueryProcessor", newXQueryProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "parseFile", parseFile);
            NODE_SET_PROTOTYPE_METHOD(t, "parseURI", parseURI);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceValue", setSourceValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFile", setSourceFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperties", getProperties);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"), t->GetFunction());
        };

        static int jvmCreated;
        static JNIEnv *env;
        static JavaVM *jvm;

        /*
         * Look for class.
         */

        static jclass lookForClass(JNIEnv* env, const char* name) {
            jclass clazz = (jclass) env->FindClass(name);

            if (!clazz) {
                printf("Unable to find class %s\n", name);
                exit(1);
            }
#ifdef DEBUG
            std::cerr << "Class found" << name << std::endl;
#endif
            fflush(stdout);

            return clazz;
        }

        static jmethodID findConstructor(JNIEnv* env, jclass myClassInDll, std::string arguments) {
#ifdef DEBUG
            std::cerr << "Finding constructor" << std::endl;
#endif
            jmethodID MID_init;
            //jobject obj;

            MID_init = (jmethodID) env->GetMethodID(myClassInDll, "<init>", arguments.c_str());
            if (!MID_init) {
                std::cerr << "Error: MyClassInDll.<init>() not found\n" << std::endl;
                return NULL;
            }

            return MID_init;
        }

        static jobject createObject(JNIEnv* env, jclass myClassInDll, std::string arguments, bool l) {
            jmethodID MID_init;
            jobject obj;

            MID_init = (jmethodID) env->GetMethodID(myClassInDll, "<init>", arguments.c_str());
            if (!MID_init) {
                printf("Error: MyClassInDll.<init>() not found\n");
                return NULL;
            }

            obj = (jobject) env->NewObject(myClassInDll, MID_init, (jboolean) l);
            if (!obj) {
                std::cout << "Error: failed to allocate an object " + arguments + "\n";
                return NULL;
            }
            return obj;
        }

        static jobject createObject2(JNIEnv* env, jclass myClassInDll, std::string arguments, jobject obji, bool l) {
            jmethodID MID_init;
            jobject obj;

            MID_init = (jmethodID) env->GetMethodID(myClassInDll, "<init>", arguments.c_str());
            if (!MID_init) {
                printf("Error: MyClassInDll.<init>() not found\n");
                return NULL;
            }

            obj = (jobject) env->NewObject(myClassInDll, MID_init, obji, (jboolean) l);
            if (!obj || !obji) {
                std::cout << "Error: failed to allocate an object2 " + arguments + "\n";
                return NULL;
            }
            return obj;
        }

        bool exceptionOccurred() {
            return env->ExceptionCheck();
        }

        SaxonApiException * checkForException(JNIEnv* env, jclass callingClass, jobject callingObject) {

            if (env->ExceptionCheck()) {
                std::string result1 = "";
                std::string errorCode = "";
                jthrowable exc = env->ExceptionOccurred();
                env->ExceptionDescribe();
#ifdef DEBUG	
                env->ExceptionDescribe();
#endif
                jclass exccls(env->GetObjectClass(exc));
                jclass clscls(env->FindClass("java/lang/Class"));

                jmethodID getName(env->GetMethodID(clscls, "getName", "()Ljava/lang/String;"));
                jstring name(static_cast<jstring> (env->CallObjectMethod(exccls, getName)));
                char const* utfName(env->GetStringUTFChars(name, 0));
                result1 = (std::string(utfName));
                //env->ReleaseStringUTFChars(name, utfName);

                jmethodID getMessage(env->GetMethodID(exccls, "getMessage", "()Ljava/lang/String;"));
                if (getMessage) {

                    jstring message(static_cast<jstring> (env->CallObjectMethod(exc, getMessage)));
                    char const* utfMessage(env->GetStringUTFChars(message, 0));
                    if (utfMessage != NULL) {
                        result1 = (result1 + " : ") + utfMessage;
                    }
                    //cout<<result1<<endl;
                    //env->ReleaseStringUTFChars(message,utfMessage);
                    if (callingObject != NULL && result1.compare(0, 36, "net.sf.saxon.s9api.SaxonApiException", 36) == 0) {
                        jmethodID getErrorCodeID(env->GetMethodID(callingClass, "getExceptions", "()[Lnet/sf/saxon/option/cpp/SaxonExceptionForCpp;"));
                        jclass saxonExceptionClass(env->FindClass("net/sf/saxon/option/cpp/SaxonExceptionForCpp"));
                        if (getErrorCodeID) {
                            jobjectArray saxonExceptionObject((jobjectArray) (env->CallObjectMethod(callingObject, getErrorCodeID)));
                            if (saxonExceptionObject) {
                                jmethodID lineNumID = env->GetMethodID(saxonExceptionClass, "getLinenumber", "()I");
                                jmethodID ecID = env->GetMethodID(saxonExceptionClass, "getErrorCode", "()Ljava/lang/String;");
                                jmethodID emID = env->GetMethodID(saxonExceptionClass, "getErrorMessage", "()Ljava/lang/String;");
                                jmethodID typeID = env->GetMethodID(saxonExceptionClass, "isTypeError", "()Z");
                                jmethodID staticID = env->GetMethodID(saxonExceptionClass, "isStaticError", "()Z");
                                jmethodID globalID = env->GetMethodID(saxonExceptionClass, "isGlobalError", "()Z");


                                int exLength = (int) env->GetArrayLength(saxonExceptionObject);
                                SaxonApiException * saxonExceptions = new SaxonApiException();
                                for (int i = 0; i < exLength; i++) {
                                    jobject exObj = env->GetObjectArrayElement(saxonExceptionObject, i);

                                    jstring errCode = (jstring) (env->CallObjectMethod(exObj, ecID));
                                    jstring errMessage = (jstring) (env->CallObjectMethod(exObj, emID));
                                    jboolean isType = (env->CallBooleanMethod(exObj, typeID));
                                    jboolean isStatic = (env->CallBooleanMethod(exObj, staticID));
                                    jboolean isGlobal = (env->CallBooleanMethod(exObj, globalID));
                                    saxonExceptions->add((errCode ? env->GetStringUTFChars(errCode, 0) : NULL), (errMessage ? env->GetStringUTFChars(errMessage, 0) : NULL), (int) (env->CallIntMethod(exObj, lineNumID)), (bool)isType, (bool)isStatic, (bool)isGlobal);
                                    //env->ExceptionDescribe();
                                }
                                //env->ExceptionDescribe();
                                env->ExceptionClear();
                                return saxonExceptions;
                            }
                        }
                    }
                }
                SaxonApiException * saxonExceptions = new SaxonApiException(NULL, result1.c_str());
                //env->ExceptionDescribe();
                env->ExceptionClear();
                return saxonExceptions;
            }
            return NULL;

        }

    private:

        void createJVM() {
            /*
             * Initialize JET run-time.
             * The handle of loaded component is used to retrieve Invocation API.
             */
            initJavaRT(myDllHandle, &SaxonProcessor::jvm, &SaxonProcessor::env);
        }

        SaxonProcessor() : SaxonProcessor(false) {

        };

        SaxonProcessor(bool l) : cwd("") {
#ifdef __linux__
            if (getenv("SAXON_HOME") != NULL) {
                dllName = std::string(getenv("SAXON_HOME")) + "/libsaxon.so";
                resources_dir = std::string(getenv("SAXON_HOME")) + "/saxon-data";
            } else {
                dllName = "/usr/lib/libsaxon.so";
                resources_dir = "/usr/lib/saxon-data";
            }
#else
            resources_dir = "C:\\Program Files\\Saxonica\\SaxonHEC0.3";
#endif
            std::cout << "dllName " << dllName << std::endl;
            license = l;
            HANDLE myDllHandle = loadDll((char*) dllName.c_str());
            initJavaRT(myDllHandle, &SaxonProcessor::jvm, &env);

            versionClass = lookForClass(env, "net/sf/saxon/Version");
            procClass = lookForClass(env, "net/sf/saxon/s9api/Processor");
            saxonCAPIClass = lookForClass(env, "net/sf/saxon/option/cpp/SaxonCAPI");
            proc = createObject(env, procClass, "(Z)V", false);
            std::cout << "SaxonP " << l << std::endl;
        };
        SaxonProcessor(const SaxonProcessor& orig) = delete;

        SaxonProcessor& operator=(const SaxonProcessor& other) {
            versionClass = other.versionClass;
            procClass = other.procClass;
            saxonCAPIClass = other.saxonCAPIClass;
            cwd = other.cwd;
            proc = other.proc;
            env = other.env;
            jvm = other.jvm;
            parameters = other.parameters;
            properties = other.properties;
            license = other.license;
            exception = other.exception;
            return *this;
        }

        ~SaxonProcessor() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            SaxonProcessor* sp;
            std::cout << "New " << args.Length() << std::endl;
            if (args.Length() < 1)
                sp = new SaxonProcessor();
            else
                sp = new SaxonProcessor(args[0]->ToBoolean()->BooleanValue());

            // extend target object with file
            sp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "path"), String::NewFromUtf8(v8::Isolate::GetCurrent(), f->m_file->getFileName().c_str()));
        };
        static void newTransformer(const v8::FunctionCallbackInfo<Value>& args);

        static void newXQueryProcessor(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void parseFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void parseURI(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setSourceValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setSourceFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

    protected:

        std::map<std::string, XdmValue*>& getParameters() {
            std::map<std::string, XdmValue*>& ptr = parameters;
            return ptr;
        }

        std::map<std::string, std::string>& getProperties() {
            std::map<std::string, std::string> &ptr = properties;
            return ptr;
        }

        jclass versionClass;
        jclass procClass;
        jclass saxonCAPIClass;
        std::string cwd; /*!< current working directory */
        std::string dllName;
        std::string resources_dir; /*!< current Saxon resources directory */
        jobject proc; /*!< Java Processor object */
        HANDLE myDllHandle;
        std::map<std::string, XdmValue*> parameters; /*!< map of parameters used for the transformation as (string, value) pairs */
        std::map<std::string, std::string> properties; /*!< map of properties used for the transformation as (string, string) pairs */
        bool license; /*!< indicates whether the Processor requires a Saxon that needs a license file (i.e. Saxon-EE) other a Saxon-HE Processor is created  */
        bool closed;
        SaxonApiException* exception; /*!< Pointer to any potential exception thrown */
    };

};
