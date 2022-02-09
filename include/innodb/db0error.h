//
// Created by chunxiao ma on 2022/1/10.
//

#ifndef INNODB_DB0ERROR_H
#define INNODB_DB0ERROR_H
namespace innodb {
class DbError {
public:
  static constexpr int DB_SUCCESS = 10;
  static constexpr int DB_ERROR = 11;
  static constexpr int DB_OUT_OF_MEMORY = 12;
  static constexpr int DB_OUT_OF_FILE_SPACE = 13;
  static constexpr int DB_LOCK_WAIT = 14;
  static constexpr int DB_DEADLOCK = 15;
  static constexpr int DB_ROLLBACK = 16;
  static constexpr int DB_DUPLICATE_KEY = 17;
  static constexpr int DB_QUE_THR_SUSPENDED = 18;
  /** required history data has been deleted due to lack of space in rollback segment */
  static constexpr int DB_MISSING_HISTORY = 19;
  static constexpr int DB_CLUSTER_NOT_FOUND = 30;
  static constexpr int DB_TABLE_NOT_FOUND = 31;
  /** the database has to be stopped and restarted with more file space */
  static constexpr int DB_MUST_GET_MORE_FILE_SPACE = 32;
  static constexpr int DB_TABLE_IS_BEING_USED = 33;
  /** a record in an index would become bigger than 1/2 free space in a page frame */
  static constexpr int DB_TOO_BIG_RECORD = 34;
  /** lock wait lasted too long */
  static constexpr int DB_LOCK_WAIT_TIMEOUT = 35;
  /** referenced key value not found for a foreign key in an insert or update of a row */
  static constexpr int DB_NO_REFERENCED_ROW = 36;
  /** cannot delete or update a row because it contains a key value which is referenced */
  static constexpr int DB_ROW_IS_REFERENCED = 37;
  /** adding a foreign key constraint to a table failed */
  static constexpr int DB_CANNOT_ADD_CONSTRAINT = 38;

  static constexpr int DB_FAIL = 1000;
  static constexpr int DB_OVERFLOW = 1001;
  static constexpr int DB_UNDERFLOW = 1002;
  static constexpr int DB_STRONG_FAIL = 1003;
  static constexpr int DB_RECORD_NOT_FOUND = 1500;
  static constexpr int DB_END_OF_INDEX = 1501;
};
} // namespace innodb
#endif // INNODB_DB0ERROR_H
