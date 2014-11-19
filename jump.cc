#include <v8.h>
#include <node.h>
#include <setjmp.h>

using namespace v8;
using namespace node;

jmp_buf buffer;
uv_work_t jump_req;

struct Baton {
  Persistent<Function> callback;
};

static void JumpWork(uv_work_t *req) {
  if (!setjmp(buffer)) {
    longjmp(buffer, 1);
  }
}

static void AfterJump(uv_work_t *req, int status) {
  HandleScope scope;

  Baton* baton = static_cast<Baton*>(req->data);
  baton->callback->Call(Context::GetCurrent()->Global(), 0, NULL);
}

static Handle<Value> Jump(const Arguments& args) {
  HandleScope scope;

  Baton* baton = new Baton();
  jump_req.data = baton;
  baton->callback = Persistent<Function>::New(Local<Function>::Cast(args[0]));
  uv_queue_work(uv_default_loop(), &jump_req, JumpWork, AfterJump);

  return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("jump"),
   FunctionTemplate::New(Jump)->GetFunction());
}

NODE_MODULE(jump, init)
