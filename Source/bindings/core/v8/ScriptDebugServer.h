/*
 * Copyright (c) 2010, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ScriptDebugServer_h
#define ScriptDebugServer_h

#include "bindings/core/v8/ScopedPersistent.h"
#include "core/inspector/ScriptBreakpoint.h"
#include "core/inspector/ScriptCallStack.h"
#include "core/inspector/ScriptDebugListener.h"
#include "wtf/HashMap.h"
#include "wtf/PassOwnPtr.h"
#include <v8-debug.h>
#include <v8.h>

namespace blink {

class ScriptState;
class ScriptDebugListener;
class ScriptSourceCode;
class ScriptValue;
class JavaScriptCallFrame;

class ScriptDebugServer : public NoBaseWillBeGarbageCollectedFinalized<ScriptDebugServer> {
    WTF_MAKE_NONCOPYABLE(ScriptDebugServer);
public:
    virtual ~ScriptDebugServer();
    virtual void trace(Visitor*);

    String setBreakpoint(const String& sourceID, const ScriptBreakpoint&, int* actualLineNumber, int* actualColumnNumber, bool interstatementLocation);
    void removeBreakpoint(const String& breakpointId);
    void clearBreakpoints();
    void setBreakpointsActivated(bool activated);

    enum PauseOnExceptionsState {
        DontPauseOnExceptions,
        PauseOnAllExceptions,
        PauseOnUncaughtExceptions
    };
    PauseOnExceptionsState pauseOnExceptionsState();
    void setPauseOnExceptionsState(PauseOnExceptionsState pauseOnExceptionsState);

    void setPauseOnNextStatement(bool pause);
    bool pausingOnNextStatement();
    bool canBreakProgram();
    void breakProgram();
    void continueProgram();
    void stepIntoStatement();
    void stepOverStatement();
    void stepOutOfFunction();
    void clearStepping();

    bool setScriptSource(const String& sourceID, const String& newContent, bool preview, String* error, RefPtr<TypeBuilder::Debugger::SetScriptSourceError>&, ScriptValue* newCallFrames, RefPtr<JSONObject>* result);
    ScriptValue currentCallFrames();
    ScriptValue currentCallFramesForAsyncStack();
    PassRefPtrWillBeRawPtr<JavaScriptCallFrame> callFrameNoScopes(int index);
    int frameCount();

    static PassRefPtrWillBeRawPtr<JavaScriptCallFrame> toJavaScriptCallFrameUnsafe(const ScriptValue&);

    class Task {
    public:
        virtual ~Task() { }
        virtual void run() = 0;
    };
    static void interruptAndRun(v8::Isolate*, PassOwnPtr<Task>);
    void runPendingTasks();

    bool isPaused();

    v8::Local<v8::Value> functionScopes(v8::Handle<v8::Function>);
    v8::Local<v8::Value> generatorObjectDetails(v8::Handle<v8::Object>&);
    v8::Local<v8::Value> collectionEntries(v8::Handle<v8::Object>&);
    v8::Local<v8::Value> getInternalProperties(v8::Handle<v8::Object>&);
    v8::Handle<v8::Value> setFunctionVariableValue(v8::Handle<v8::Value> functionValue, int scopeNumber, const String& variableName, v8::Handle<v8::Value> newValue);
    v8::Local<v8::Value> callDebuggerMethod(const char* functionName, int argc, v8::Handle<v8::Value> argv[]);

    virtual void compileScript(ScriptState*, const String& expression, const String& sourceURL, bool persistScript, String* scriptId, String* exceptionDetailsText, int* lineNumber, int* columnNumber, RefPtrWillBeRawPtr<ScriptCallStack>* stackTrace);
    virtual void clearCompiledScripts();
    virtual void runScript(ScriptState*, const String& scriptId, ScriptValue* result, bool* wasThrown, String* exceptionDetailsText, int* lineNumber, int* columnNumber, RefPtrWillBeRawPtr<ScriptCallStack>* stackTrace);

    virtual void muteWarningsAndDeprecations() { }
    virtual void unmuteWarningsAndDeprecations() { }

    v8::Isolate* isolate() const { return m_isolate; }

protected:
    explicit ScriptDebugServer(v8::Isolate*);

    virtual ScriptDebugListener* getDebugListenerForContext(v8::Handle<v8::Context>) = 0;
    virtual void runMessageLoopOnPause(v8::Handle<v8::Context>) = 0;
    virtual void quitMessageLoopOnPause() = 0;

    static void breakProgramCallback(const v8::FunctionCallbackInfo<v8::Value>&);
    void handleProgramBreak(ScriptState* pausedScriptState, v8::Handle<v8::Object> executionState, v8::Handle<v8::Value> exception, v8::Handle<v8::Array> hitBreakpoints, bool isPromiseRejection = false);

    static void v8DebugEventCallback(const v8::Debug::EventDetails& eventDetails);
    void handleV8DebugEvent(const v8::Debug::EventDetails& eventDetails);

    void dispatchDidParseSource(ScriptDebugListener*, v8::Handle<v8::Object> sourceObject, CompileResult);

    void ensureDebuggerScriptCompiled();
    void discardDebuggerScript();

    PauseOnExceptionsState m_pauseOnExceptionsState;
    ScopedPersistent<v8::Object> m_debuggerScript;
    v8::Local<v8::Object> m_executionState;
    RefPtr<ScriptState> m_pausedScriptState;
    bool m_breakpointsActivated;
    ScopedPersistent<v8::FunctionTemplate> m_breakProgramCallbackTemplate;
    HashMap<String, OwnPtr<ScopedPersistent<v8::Script>>> m_compiledScripts;
    v8::Isolate* m_isolate;

private:
    enum ScopeInfoDetails {
        AllScopes,
        FastAsyncScopes,
        NoScopes // Should be the last option.
    };

    ScriptValue currentCallFramesInner(ScopeInfoDetails);

    PassRefPtrWillBeRawPtr<JavaScriptCallFrame> wrapCallFrames(int maximumLimit, ScopeInfoDetails);

    void handleV8AsyncTaskEvent(ScriptDebugListener*, ScriptState* pausedScriptState, v8::Handle<v8::Object> executionState, v8::Handle<v8::Object> eventData);

    void handleV8PromiseEvent(ScriptDebugListener*, ScriptState* pausedScriptState, v8::Handle<v8::Object> executionState, v8::Handle<v8::Object> eventData);

    bool m_runningNestedMessageLoop;
};

} // namespace blink


#endif // ScriptDebugServer_h