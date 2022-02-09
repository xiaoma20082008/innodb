//
// Created by chunxiao ma on 2022/1/11.
//

#include "os_thread.hh"
#include <atomic>
#include <thread>

namespace innodb {

static int CreateId() {
  static std::atomic<int> THREAD_NUMBER{1};
  return THREAD_NUMBER++;
}
static const char *CreateName(int id) { return "Thread-"; }

struct OSThread::Impl {
  const int id_{};
  const char *name_{};
  int priority_{};
  Task task_{};
  std::thread thd_;
  volatile int state_{};
  Impl(Task task) : id_(CreateId()), name_(CreateName(id_)), priority_(5), task_(task), state_(0) {}
};

OSThread::OSThread(Task task) : impl_(std::make_shared<Impl>(task)) {}
OSThread::~OSThread() {}

OSThread *OSThread::CurrentThread() { return nullptr; }

void OSThread::Yield() {}
void OSThread::Sleep(long mills) {}
void OSThread::Start() {
  if (impl_->state_ != 0) {
    return;
  }
  impl_->thd_ = std::thread(impl_->task_);
  impl_->state_ = 1;
}
void OSThread::Await() {
  if (impl_->state_ == 0) {
    return;
  }
  impl_->thd_.join();
}

int OSThread::GetId() const { return impl_->id_; }
const char *OSThread::GetName() const { return impl_->name_; }
int OSThread::GetPriority() const { return impl_->priority_; }
void OSThread::SetName(const char *name) { impl_->name_ = name; }
void OSThread::SetPriority(int priority) { impl_->priority_ = priority; }

} // namespace innodb