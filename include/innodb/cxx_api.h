//
// Created by chunxiao ma on 2021/11/23.
//

#ifndef INNODB_CXX_API_H
#define INNODB_CXX_API_H
namespace innodb {

using uchar = unsigned char;
using byte = unsigned char;
using uint = unsigned int;
using ulong = unsigned long;

class InnoDB {
public:
  InnoDB() {}
  virtual ~InnoDB() {}

public:
  // region ddl

  /**
   * Create an InnoDB database.
   *
   * @param path database path
   * @return error number.
   * @retval 0 if success
   */
  virtual int CreateDatabase(const char *path) = 0;

  /**
   * Removes all tables in the named database inside InnoDB.
   *
   * @param path database path
   * @return error number.
   * @retval 0 if success
   */
  virtual int DropDatabase(const char *path) = 0;
  /**
   * Create an InnoDB table.
   *
   * @param name table name in filename-safe encoding
   * @param desc table structure
   * @return error number.
   * @retval 0 if success
   */
  virtual int CreateTable(const char *name, void *desc) = 0;

  /**
   * Drop an InnoDB table.
   *
   * @param name table name in filename-safe encoding
   * @param desc table structure
   * @return error number.
   * @retval 0 if success
   */
  virtual int DeleteTable(const char *name, void *desc) = 0;

  /**
   * Truncate an InnoDB table.
   *
   * @param name table name in filename-safe encoding
   * @param desc table structure
   * @return error number.
   * @retval 0 if success
   */
  virtual int TruncateTable(const char *name, void *desc) = 0;

  /**
   * Rename an InnoDB table.
   *
   * @param from source table name in filename-safe encoding
   * @param to target table name in filename-safe encoding
   * @return error number.
   * @retval 0 if success
   */
  virtual int RenameTable(const char *from, const char *to) = 0;

  // endregion ddl

  // region dml

  /**
   * Insert a row from the table.
   *
   * @param buf record
   * @return error number.
   * @retval 0 if success
   */
  virtual int InsertRow(uchar *buf) = 0;

  /**
   * Update a row from the table.
   *
   * @param old_data old row
   * @param new_data new row
   * @return error number.
   * @retval 0 if success
   */
  virtual int UpdateRow(const uchar *old_data, uchar *new_data) = 0;

  /**
   * Delete a row from the table.
   *
   * @param buf record
   * @return error number.
   * @retval 0 if success
   */
  virtual int DeleteRow(const uchar *buf) = 0;

  /**
   * Delete all rows from the table.
   *
   * @return error number.
   * @retval 0 on success
   */
  virtual int DeleteAllRows() = 0;

  // endregion dml

  // region lifecycle

  virtual int Init() = 0;

  virtual int Open(const char *name, int mode) = 0;

  virtual int Close() = 0;

  // endregion lifecycle

  virtual double ScanTime() = 0;

protected:
private:
  const char* _database;
};

} // namespace innodb

#endif // INNODB_CXX_API_H
