import os
import unittest
from db_sqlite import SQLiteDriver


class SQLiteDriverTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        if os.path.exists(SQLiteDriver.driver_name):
            os.remove(SQLiteDriver.driver_name)
            pass

    def setUp(self):
        self.driver = SQLiteDriver(driver_name='employees')

    def test_create(self):
        sql = '''
        create table employees
        (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            JOBNUMBER  TEXT  NOT NULL UNIQUE,
            FIRSTNAME  TEXT  NOT NULL,
            SALARY     INT   NOT NULL
        )
        '''
        res = self.driver._execute(sql)
        self.assertEqual(res, 0)

    def test_insert_sql(self):
        # self.test_create()
        sql = '''
        insert into employees
        (jobnumber, firstname, salary) values
        ('16297','xp','100')
        '''
        self.assertEqual(self.driver._execute(sql), 1)

    def test_insert_sql2(self):
        sql = 'insert into employees (jobnumber,firstname,salary) values (?,?,?);'
        param = ('78213', 'lt', 200)
        self.assertEqual(self.driver._execute(sql, param), 1)

    def test_insert(self):
        obj = {
            'jobnumber': '21842',
            'firstname': 'lzl',
            'salary': '300'
        }
        self.assertEqual(self.driver.insert(obj), 1)

    def test_select(self):
        cond = {
            'firstname': 'xp',
            'salary': 100
        }
        res = self.driver.select(cond)
        self.assertEqual(len(res), 1)

    def test_update_sql(self):
        sql = 'UPDATE employees SET SALARY=1000 WHERE ID=3'
        self.assertEqual(self.driver._execute(sql), 1)

    def test_update(self):
        obj = {
            'id': 2,
            'salary': 2000
        }
        res = self.driver.update(obj)
        self.assertEqual(res, 1)

    def test_query(self):
        sql = '''
        select * from employees
        '''
        res = self.driver._execute(sql)
        print(res)
        self.assertIsNotNone(res)

    def test_delete(self):
        obj = {
            'jobnumber': '41242',
            'firstname': 'zjj',
            'salary': '800'
        }
        self.driver.insert(obj)
        res = self.driver.delete(1)
        self.assertEqual(res, 1)


if __name__ == '__main__':
    unittest.main()
    '''
    sql = 'select * from employees'
    driver = SQLiteDriver(driver_name='employees')
    res = driver.query(sql)
    print(res)
    '''
