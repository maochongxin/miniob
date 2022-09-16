/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"

// UPDATE table_name SET column1 = value1, column2 = value2, ... WHERE condition;
UpdateStmt::UpdateStmt(Table* table, Value* values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount) {
}

RC UpdateStmt::create(Db* db, const Updates& update, Stmt*& stmt) {
  const char* table_name = update.relation_name;
  if (db == nullptr || table_name == nullptr || update.condition_num <= 0) {
    LOG_WARNING("invalid argument. db=%p, table_name=%p, condition_num=%d", db, table_name, update.condition_name);
    return RC::INVALID_ARGUMENT;
  }

  Table* table = db->find(table_name);
  if (!table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }


  const TableMeta& table_meta = table->table_meta();
  const FieldMeta* field_meta = table_meta->field(update.attribute_name);
  if (!field_meta) {
    LOG_WARN("field not found. table=%s, field=%s", table_name, field_meta->name());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  const Value& value = update.value;
  stmt = new UpdateStmt(table, &value, 1);
  return RC::SUCCESS;
}
