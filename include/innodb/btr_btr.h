//
// Created by chunxiao ma on 2021/11/30.
//

#ifndef INNODB_BTR_BTR_H
#define INNODB_BTR_BTR_H
#include "innodb/mtr_mtr.h"

namespace innodb {

class BTreePage {
public:
  /**
   * Gets a buffer page and declares its latching order level.
   * @param space_no
   * @param page_no
   * @param mode
   * @param mtr
   * @return
   */
  char *get(int space_no, int page_no, int mode, MiniTrx *mtr);
  /**
   * Gets the index id field of a page.
   * @param page
   * @return index id
   */
  int get_index_id(char *page);
};

class BTree {};
} // namespace innodb
#endif // INNODB_BTR_BTR_H
