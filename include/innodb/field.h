//
// Created by chunxiao ma on 2021/11/24.
//

#ifndef INNODB_FIELD_H
#define INNODB_FIELD_H

namespace innodb {
class Field {};

class Field_num : public Field {
public:
  char *_ptr;
};

class Field_decimal : public Field_num {};
class Field_short : public Field_num {};
class Field_int : public Field_num {};
class Field_long : public Field_num {};
class Field_double : public Field_num {};

class Field_str : public Field {};

class Field_null : public Field_str {};

class Field_year : public Field_str {};
class Field_date : public Field_str {};
class Field_time : public Field_str {};
class Field_datetime : public Field_str {};
class Field_timestamp : public Field_str {};

} // namespace innodb

#endif // INNODB_FIELD_H
