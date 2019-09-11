# -*- coding: utf-8 -*-
import sqlite3
import json
from db import DBDriver


class SQLiteDriver(DBDriver):
    driver_name = 'storage.db'

    def __init__(self, driver_name):
        self.table = driver_name
        self.conn = None
        self.cx = None

    def _connect(self):
        self.conn = sqlite3.connect(self.driver_name)
        self.cx = self.conn.cursor()

    def _close(self):
        self.cx.close()
        self.conn.close()

    def _execute(self, sql, param=None):
        self._connect()
        try:
            if param is None:
                self.cx.execute(sql)
            else:
                if type(param) is list:
                    self.cx.executemany(sql, param)
                else:
                    self.cx.execute(sql, param)
            count = self.conn.total_changes
            self.conn.commit()
        except Exception as ex:
            print(ex)
            self._close()
            return False
        self._close()
        return count

    def _query(self, sql, param=None):
        self._connect()
        if param is None:
            self.cx.execute(sql)
        else:
            self.cx.execute(sql, param)
        col_name_list = [tuple[0] for tuple in self.cx.description]
        res = self.cx.fetchall()
        objs_json = {self.table: []}
        for obj in res:
            obj_json = {}
            for idx, col in enumerate(obj):
                obj_json[col_name_list[idx]] = col
            objs_json[self.table].append(obj_json)
        self._close()
        return objs_json

    def insert(self, obj):
        keys = ''
        _ = ''
        values = []
        first_time = True
        for k, v in obj.items():
            if first_time:
                keys += '('
                _ += '('
                first_time = False
            else:
                keys += ','
                _ += ','
            keys += k
            _ += '?'
            values.append(v)
        keys += ')'
        _ += ')'
        values = tuple(values)
        sql = 'insert into {table_name} {keys} values {_}'.format(
            table_name=self.table, keys=keys, _=_)
        return self._execute(sql, param=values)

    def select(self, condition=None):
        sql = 'select * from {table_name} '.format(table_name=self.table)
        values = []
        if condition:
            sql += 'where '
            first_time = True
            for k, v in condition.items():
                if first_time:
                    first_time = False
                else:
                    sql += 'and '
                sql += k + '=? '
                values.append(v)
        values = tuple(values)
        return self._query(sql, param=values)

    def update(self, obj):
        '''
        update <table_name> set xx=xx and yy==yy where id=<id>
        '''
        sql = 'update {table_name} set '.format(table_name=self.table)
        _id = obj['id']
        obj.pop('id')
        values = []
        first_time = True
        for k, v in obj.items():
            if first_time:
                first_time = False
            else:
                sql += 'and '
            sql += k + '=? '
            values.append(v)
        values = tuple(values)
        sql += 'where id={id}'.format(id=_id)
        return self._execute(sql, values)

    def delete(self, _id):
        sql = 'delete from {table_name} where id={id}'.format(
            table_name=self.table, id=_id)
        return self._execute(sql)


if __name__ == '__main__':
    driver = SQLiteDriver('employees')
    #res = driver.query('select * from employees')
    res = driver.delete(3)
    print(res)
