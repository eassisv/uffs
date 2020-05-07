from flaskr.models import db
from datetime import date


class Client(db.Model):
    __tablename__ = "clients"

    id = db.Column(db.Integer, primary_key=True)
    first_name = db.Column(db.String(128), nullable=False)
    full_name = db.Column(db.String(256), nullable=False)
    cnpj = db.Column(db.String(32), nullable=False)
    address = db.Column(db.String(256), nullable=False)
    email = db.Column(db.String(128), nullable=False)
    phone = db.Column(db.String(32), nullable=False)
    created_at = db.Column(db.Date, nullable=False)
    orders = db.relationship("Order", backref="clients", lazy=True)

    def __init__(self, first_name, full_name, cnpj, address, email, phone):
        self.first_name = first_name
        self.full_name = full_name
        self.cnpj = cnpj
        self.address = address
        self.email = email
        self.phone = phone
        self.created_at = date.today()

    def __repr__(self):
        return "Client({})".format(self.first_name)
