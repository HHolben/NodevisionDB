// src/binding.cpp
#include <napi.h>
#include "GraphDB.hpp"  // Ensure the header file name is correct

// Wrap your functions/classes here; for example:
Napi::Value CreateGraphDB(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // Your wrapping logic; here we simply return a string as a placeholder
    return Napi::String::New(env, "GraphDB instance created!");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "createGraphDB"),
                Napi::Function::New(env, CreateGraphDB));
    return exports;
}

NODE_API_MODULE(nodevision_db, Init)
