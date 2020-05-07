from flask import current_app
from flaskr.routes import products, orders, clients


def init_routes():
    current_app.register_blueprint(products.bp)
    current_app.register_blueprint(orders.bp)
    current_app.register_blueprint(clients.bp)
