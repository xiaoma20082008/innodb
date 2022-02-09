//
// Created by chunxiao ma on 2021/12/9.
//

#ifndef INNODB_BUF_BUF_HH
#define INNODB_BUF_BUF_HH
namespace innodb {
class BufferPool {
public:
  static BufferPool *GetInstance();
  void Startup();
  void Destroy();

  int GetSize();
  int GetMaxSize();

  long GetOldestLsn();

  void *Alloc();

  void Free(void *frame);

  char *Copy(char *buf, void *frame);
};
} // namespace innodb
#endif // INNODB_BUF_BUF_HH
