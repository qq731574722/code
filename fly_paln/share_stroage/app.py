import json
from flask import Flask
from flask import request
from db_sqlite import SQLiteDriver

app = Flask(__name__)


@app.route('/')
def index():
    return 'Hello World'


@app.route('/select',methods=['get'])
def select():
    driver = SQLiteDriver(driver_name='employees')
    #data = request.get_data()
    #data = json.load(data)
    return driver.select()


if __name__ == '__main__':
    app.debug = True  # 设置调试模式，生产模式的时候要关掉debug
    app.run()
