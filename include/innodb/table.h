//
// Created by chunxiao ma on 2021/11/24.
//

#ifndef INNODB_TABLE_H
#define INNODB_TABLE_H
#include "field.h"
namespace innodb {
class Table {
public:
  Field *_fields;
  int _field_count;
};
} // namespace innodb
#endif // INNODB_TABLE_H
