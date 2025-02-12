#include <napi.h>
#include "GraphDB.hpp"  // Your custom database header

// Wrapper function to create a database instance
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("createGraphDB", Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        return Napi::External<GraphDB>::New(info.Env(), new GraphDB());
    }));
    return exports;
}

// Register module
NODE_API_MODULE(nodevision_db, Init)
