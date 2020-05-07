from flaskr.models import db
from flaskr.models.products import Product
from flaskr.models.clients import Client


class Order(db.Model):
    __tablename__ = "orders"

    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    total_price = db.Column(db.Float, nullable=False)
    sale_date = db.Column(db.Date, nullable=False)
    number_of_items = db.Column(db.Integer, nullable=False)
    status = db.Column(db.String(64), nullable=False)
    delivery_date = db.Column(db.Date, nullable=False)
    client_id = db.Column(db.Integer, db.ForeignKey("clients.id"), nullable=False)
    order_items = db.relationship("Order_Item", backref="orders", lazy=True)

    def __init__(
        self, total_price, sale_date, number_of_items, status, delivery_date, client_id
    ):
        self.total_price = total_price
        self.sale_date = sale_date
        self.number_of_items = number_of_items
        self.status = status
        self.delivery_date = delivery_date
        self.client_id = client_id

    def __repr__(self):
        return "Order(id: {})".format(self.id)


class Order_Item(db.Model):
    __tablename__ = "order_items"

    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    quantity = db.Column(db.Integer, nullable=False)
    order_price = db.Column(db.Float, nullable=False)
    product_id = db.Column(db.Integer, db.ForeignKey("products.id"), nullable=False)
    order_id = db.Column(db.Integer, db.ForeignKey("orders.id"), nullable=False)

    def __init__(self, order_id, product_id, quantity, order_price):
        self.order_id = order_id
        self.product_id = product_id
        self.quantity = quantity
        self.order_price = order_price

    def __repr__(self):
        return "Order_Item(id: {})".format(self.id)
