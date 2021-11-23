//
// Created by chunxiao ma on 2021/11/30.
//

#ifndef INNODB_MTR_MTR_H
#define INNODB_MTR_MTR_H
namespace innodb {

/* Logging modes for a mini-transaction */

#define MTR_LOG_ALL 21           /* default mode: log all operations  modifying disk-based data */
#define MTR_LOG_NONE 22          /* log no operations */
#define MTR_LOG_SPACE 23         /* log only operations modifying file space page allocation data */
#define MTR_LOG_SHORT_INSERTS 24 /* inserts are logged in a shorter form */

/* Types for the mlock objects to store in the mtr memo;
 * NOTE that the first 3 values must be RW_S_LATCH, RW_X_LATCH,RW_NO_LATCH */
#define MTR_MEMO_PAGE_S_FIX RW_S_LATCH
#define MTR_MEMO_PAGE_X_FIX RW_X_LATCH
#define MTR_MEMO_BUF_FIX RW_NO_LATCH
#define MTR_MEMO_MODIFY 54
#define MTR_MEMO_S_LOCK 55
#define MTR_MEMO_X_LOCK 56

/* Log item types: we have made them to be of the type 'byte' for the compiler to warn if val and type parameters are
 * switched in a call to mlog_write_ulint. NOTE! For 1 - 8 bytes, the flag value must give the length also! */
#define MLOG_SINGLE_REC_FLAG                                                                                           \
  128 /* if the mtr contains only one log record for one page, i.e., write_initial_log_record has been called only     \
once, this flag is ORed to the type of that first log record */
#define MLOG_1BYTE ((byte)1)                  /* 1 byte is written */
#define MLOG_2BYTES ((byte)2)                 /* 2 bytes ... */
#define MLOG_4BYTES ((byte)4)                 /* 4 bytes ... */
#define MLOG_8BYTES ((byte)8)                 /* 8 bytes ... */
#define MLOG_REC_INSERT ((byte)9)             /* record insert */
#define MLOG_REC_CLUST_DELETE_MARK ((byte)10) /* mark clustered index record  deleted */
#define MLOG_REC_SEC_DELETE_MARK ((byte)11)   /* mark secondary index record  deleted */
#define MLOG_REC_UPDATE_IN_PLACE ((byte)13)   /* update of a record, preserves record field sizes */
#define MLOG_REC_DELETE ((byte)14)            /* delete a record from a page */
#define MLOG_LIST_END_DELETE ((byte)15)       /* delete record list end on index page */
#define MLOG_LIST_START_DELETE ((byte)16)     /* delete record list start on index page */
#define MLOG_LIST_END_COPY_CREATED ((byte)17) /* copy record list end to a new created index page */
#define MLOG_PAGE_REORGANIZE ((byte)18)       /* reorganize an index page */
#define MLOG_PAGE_CREATE ((byte)19)           /* create an index page */
#define MLOG_UNDO_INSERT ((byte)20)           /* insert entry in an undo log */
#define MLOG_UNDO_ERASE_END ((byte)21)        /* erase an undo log page end */
#define MLOG_UNDO_INIT ((byte)22)             /* initialize a page in an undo log */
#define MLOG_UNDO_HDR_DISCARD ((byte)23)      /* discard an update undo log header */
#define MLOG_UNDO_HDR_REUSE ((byte)24)        /* reuse an insert undo log header */
#define MLOG_UNDO_HDR_CREATE ((byte)25)       /* create an undo log header */
#define MLOG_REC_MIN_MARK ((byte)26)          /* mark an index record as the predefined minimum record */
#define MLOG_IBUF_BITMAP_INIT ((byte)27)      /* initialize an ibuf bitmap page */
#define MLOG_FULL_PAGE ((byte)28)             /* full contents of a page */
#define MLOG_INIT_FILE_PAGE                                                                                            \
  ((byte)29) /* this means that a file page  is taken into use and the prior contents of the page should be ignored:   \
                in recovery we must not trust the lsn values stored  to the file page */
#define MLOG_WRITE_STRING ((byte)30) /* write a string to a page */
#define MLOG_MULTI_REC_END                                                                                             \
  ((byte)31) /* if a single mtr writes log records for several pages,this log record ends the sequence of these        \
                records */
#define MLOG_DUMMY_RECORD ((byte)32) /* dummy log record used to pad a log block full */
#define MLOG_BIGGEST_TYPE ((byte)32) /* biggest value (used in asserts) */

#define MTR_MAGIC_N 54551

#define MTR_ACTIVE 12231
#define MTR_COMMITTING 56456
#define MTR_COMMITTED 34676

class MiniTrx {
public:
  void start();
  void commit();
  void write_backup_entries(long lsn);
  long create_savepoint();
  void rollback();
  void rollback_to_savepoint(long sp);
  void release_s_latch_at_savepoint(long sp,int lock);
  int get_log_mode();
  /**
   * Checks if memo contains the given item.
   * @param obj[in] object to search
   * @param type[in] type of object
   * @return true if contains
   */
  bool contains(void *obj, int type);
  /**
   * Returns the log object of a mini-transaction buffer.
   * @return
   */
  void *get_log() { return _log; }

  void print();

private:
  int _state{0};        /* MTR_ACTIVE, MTR_COMMITTING, MTR_COMMITTED */
  void *_memo{nullptr}; /* memo stack for locks etc. */
  void *_log{nullptr};  /* mini-transaction log */
  bool _updated{false}; /* TRUE if the mtr made updates to buffer pool pages */
  int _n_log_recs{0};   /* count of how many page initial log records have been written to the mtr log */
  long _log_mode{0L};   /* specifies which operations should be  logged; default value MTR_LOG_ALL */
  long _start_lsn{0L};  /* start lsn of the possible log entry for this mtr */
  long _end_lsn{0L};    /* end lsn of the possible log entry for  this mtr */
  constexpr long _magic_n{MTR_MAGIC_N};
};
} // namespace innodb
#endif // INNODB_MTR_MTR_H
