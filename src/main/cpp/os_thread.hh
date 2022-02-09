//
// Created by chunxiao ma on 2022/1/11.
//

#ifndef INNODB_OS_THREAD_HH
#define INNODB_OS_THREAD_HH
#include <memory>

namespace innodb {

using Task = void (*)();

class OSThread {
public:
  OSThread(Task task);
  ~OSThread();

  static OSThread *CurrentThread();

public:
  void Yield();
  void Sleep(long mills);
  void Start();
  void Await();

  int GetId() const;
  const char *GetName() const;
  int GetPriority() const;

  void SetName(const char *name);
  void SetPriority(int priority);

private:
  struct Impl;
  const std::shared_ptr<Impl> impl_{nullptr};
};
} // namespace innodb
#endif // INNODB_OS_THREAD_HH
