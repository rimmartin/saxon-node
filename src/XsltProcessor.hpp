#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <cstring>
#include <memory>
#include <jni.h>

namespace saxon {

    using namespace v8;

    class SaxonProcessor;

    class XsltProcessor : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XsltProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceValue", setSourceValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFile", setSourceFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setOutputfile", setOutputfile);
            NODE_SET_PROTOTYPE_METHOD(t, "setParameter", setParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "getParameter", getParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "removeParameter", removeParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            NODE_SET_PROTOTYPE_METHOD(t, "xsltApplyStylesheet", xsltApplyStylesheet);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlString", parseXmlString);
            NODE_SET_PROTOTYPE_METHOD(t, "compile", compile);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XsltProcessor"), t->GetFunction());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        XsltProcessor() : XsltProcessor(false) {

        };

        XsltProcessor(bool l) {

        };

        ~XsltProcessor() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            XsltProcessor* sp;
            if (args.Length() < 1)
                sp = new XsltProcessor();
            else
                sp = new XsltProcessor(args[1]->ToBoolean()->BooleanValue());

            sp->procJS = args[0]->ToObject();
            // unwrap processor object
            sp->proc = ObjectWrap::Unwrap<SaxonProcessor>(args[0]->ToObject());
            /*
             * Look for class.
             */
            sp->cppClass = sp->proc->lookForClass(sp->proc->env, "net/sf/saxon/option/cpp/XsltProcessorForCpp");
            if ((sp->proc->proc) == NULL) {
                std::cerr << "Processor is NULL" << std::endl;
            }
            jmethodID debugMID = sp->proc->env->GetStaticMethodID(sp->cppClass, "setDebugMode", "(Z)V");
            //if(debugMID){
            sp->proc->env->CallStaticVoidMethod(sp->cppClass, debugMID, (jboolean) false);
            // }
            sp->cpp = sp->proc->createObject2(sp->proc->env, sp->cppClass, "(Lnet/sf/saxon/s9api/Processor;Z)V", sp->proc->proc, false);


            sp->nodeCreated = false;
            sp->proc->exception = NULL;
            sp->outputfile1 = "";
            if (sp->proc->cwd.empty()) {
                sp->proc->cwd = "";
            }
            // extend target object with processor
            sp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "path"), String::NewFromUtf8(v8::Isolate::GetCurrent(), f->m_file->getFileName().c_str()));
        };

        static void setSourceValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setSourceFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setOutputfile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void removeParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void clearParameters(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void clearProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void xsltSaveResultToFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void xsltApplyStylesheet(const v8::FunctionCallbackInfo<Value>& args) {
            // unwrap xsltProcessor object
            XsltProcessor* sp = ObjectWrap::Unwrap<XsltProcessor>(args.This());
            //setProperty("resources", sp->proc->getResourcesDirectory());
            jmethodID mID = (jmethodID) sp->proc->env->GetMethodID(sp->cppClass, "xsltApplyStylesheet", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;");
            if (!mID) {
                std::cerr << "Error: MyClassInDll." << "xsltApplyStylesheet" << " not found\n" << std::endl;

            } else {
                std::map<std::string, XdmValue*> parameters = sp->proc->getParameters();
                std::map<std::string, std::string> properties = sp->proc->getProperties();
                jobjectArray stringArray = NULL;
                jobjectArray objectArray = NULL;
                jclass objectClass = sp->proc->lookForClass(sp->proc->env, "java/lang/Object");
                jclass stringClass = sp->proc->lookForClass(sp->proc->env, "java/lang/String");

                int size = parameters.size() + properties.size();
#ifdef DEBUG
                std::cerr << "Properties size: " << properties.size() << std::endl;
                std::cerr << "Parameter size: " << parameters.size() << std::endl;
                std::cerr << "size:" << size << std::endl;
#endif
                if (size > 0) {
                    objectArray = sp->proc->env->NewObjectArray((jint) size, objectClass, 0);
                    stringArray = sp->proc->env->NewObjectArray((jint) size, stringClass, 0);
                    if (objectArray == NULL) {
                        std::cerr << "objectArray is NULL" << std::endl;
                    }
                    if (stringArray == NULL) {
                        std::cerr << "stringArray is NULL" << std::endl;
                    }
                    int i = 0;
                    for (std::map<std::string, XdmValue* >::iterator iter = parameters.begin(); iter != parameters.end(); ++iter, i++) {

#ifdef DEBUG
                        std::cerr << "map 1" << std::endl;
                        std::cerr << "iter->first" << (iter->first).c_str() << std::endl;
#endif
                        sp->proc->env->SetObjectArrayElement(stringArray, i, sp->proc->env->NewStringUTF((iter->first).c_str()));
#ifdef DEBUG
                        //std::string s1 = typeid(iter->second).name();
                        //std::cerr<<"Type of itr:"<<s1<<std::endl;
                        //jobject xx = (iter->second)->getUnderlyingValue(sp->proc); 
                        //if(NULL == xx) {
                        //	std::cerr<<"xx failed"<<std::endl;
                        //} else {
                        //std::cerr<<"Type of xx:"<<(typeid(xx).name())<<std::endl;
                        //}
#endif
                        sp->proc->env->SetObjectArrayElement(objectArray, i, (iter->second)->getUnderlyingValue(sp->proc));


                    }

                    for (std::map<std::string, std::string >::iterator iter = properties.begin(); iter != properties.end(); ++iter, i++) {
                        sp->proc->env->SetObjectArrayElement(stringArray, i, sp->proc->env->NewStringUTF((iter->first).c_str()));
                        sp->proc->env->SetObjectArrayElement(objectArray, i, sp->proc->env->NewStringUTF((iter->second).c_str()));
                    }
                }
                char* source = NULL;
                char* stylesheet = NULL;
                jstring result = (jstring) (sp->proc->env->CallObjectMethod(sp->cpp, mID, sp->proc->env->NewStringUTF(sp->proc->cwd.c_str()), (source != NULL ? sp->proc->env->NewStringUTF(source) : NULL), sp->proc->env->NewStringUTF(stylesheet), stringArray, objectArray));
                if (size > 0) {
                    sp->proc->env->DeleteLocalRef(stringArray);
                    sp->proc->env->DeleteLocalRef(objectArray);
                }
                if (result) {
                    const char * str = sp->proc->env->GetStringUTFChars(result, NULL);
                    //return "result should be ok";            
                    args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), str, String::kNormalString, std::strlen(str)));
                    return;
                }
            }
            args.GetReturnValue().SetUndefined();

        };

        static void parseXmlFile(const v8::FunctionCallbackInfo<Value>& args) {

        };

        static void parseXmlString(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value source(args[0]->ToString());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessor* sp = ObjectWrap::Unwrap<XsltProcessor>(args.This());
            jmethodID mID = (jmethodID) sp->proc->env->GetMethodID(sp->cppClass, "xmlParseString", "(Ljava/lang/String;)Lnet/sf/saxon/s9api/XdmNode;");
            if (!mID) {
                std::cerr << "\nError: MyClassInDll " << "xmlParseString()" << " not found" << std::endl;
                args.GetReturnValue().SetUndefined();
            }
            jobject xdmNodei = (jobject) (sp->proc->env->CallObjectMethod(sp->cpp, mID, sp->proc->env->NewStringUTF(*source)));
            if (!xdmNodei) {
                //check for error
                std::cout << "parse of xml doc failed" << std::endl;
            } else {
                XdmValue * value = new XdmValue(xdmNodei);
                value->setProcessor(sp->proc);
                args.GetReturnValue().SetUndefined();
            }
            args.GetReturnValue().SetUndefined();
        };

        static void compile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected stylesheet as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value stylesheet(args[0]->ToString());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessor* sp = ObjectWrap::Unwrap<XsltProcessor>(args.This());
            // unwrap processor object
            //        sp->proc = ObjectWrap::Unwrap<SaxonProcessor>(sp->procJS);
            jmethodID mID = (jmethodID) sp->proc->env->GetMethodID(sp->cppClass, "xsltParseStylesheetFile", "(Ljava/lang/String;Ljava/lang/String;)Lnet/sf/saxon/s9api/XsltExecutable;");
            if (!mID) {
                std::cerr << "Error: MyClassInDll." << "createStylesheetFromString" << " not found\n" << std::endl;

            } else {
                if (sp->stylesheetObject) {
                    sp->proc->env->DeleteLocalRef(sp->stylesheetObject);
                }
                sp->stylesheetObject = (jobject) (sp->proc->env->CallObjectMethod(sp->cpp, mID, sp->proc->env->NewStringUTF(sp->proc->cwd.c_str()), sp->proc->env->NewStringUTF(*stylesheet)));
                if (!sp->stylesheetObject) {
                    sp->checkException();
                    std::cout << "Error in compile" << std::endl;
                    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Error in compile")));
                    args.GetReturnValue().SetUndefined();
                    return;
                }
            }

        };

        static void compileString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        SaxonApiException* checkException() {
            if (proc->exception == NULL) {
                proc->exception = proc->checkForException(proc->env, cppClass, cpp);
            }
            return proc->exception;
        }
        //    void exceptionClear();
        //    int exceptionCount();
        //    const char * getErrorMessage(int i);
        //    const char * getErrorCode(int i);

    private:
        Local<Object> procJS;
        SaxonProcessor* proc;
        jclass cppClass;
        jobject cpp, stylesheetObject, xdmValuei;
        std::string outputfile1; /*!< output file where result will be saved */
        std::string failure; //for testing
        bool nodeCreated;

    };

};