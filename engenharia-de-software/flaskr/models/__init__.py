from flask import current_app
from flask_sqlalchemy import SQLAlchemy


db = SQLAlchemy()

def db_add(item):
    db.session.add(item)
    db.session.commit()


def init_db():
    db.init_app(current_app)
    from flaskr.models.products import Product, Brand
    from flaskr.models.orders import Order, Order_Item

    db.create_all(app=current_app)

