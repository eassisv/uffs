from flaskr.models import db


class Product(db.Model):
    __tablename__ = "products"

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(128), nullable=False)
    description = db.Column(db.String(256), nullable=False)
    sale_price = db.Column(db.Float, nullable=False)
    total_quantity = db.Column(db.Integer, nullable=False)
    actived = db.Column(db.SmallInteger, nullable=False)
    min_quantity = db.Column(db.Integer)
    brand_id = db.Column(db.Integer, db.ForeignKey("brands.id"), nullable=False)
    orders = db.relationship("Order_Item", backref="products", lazy=True)
    lots = db.relationship("Lot", backref="products", lazy=True)

    def __init__(
        self,
        name,
        description,
        sale_price,
        total_quantity,
        actived,
        brand_id,
        min_quantity,
    ):
        self.name = name
        self.description = description
        self.sale_price = sale_price
        self.total_quantity = total_quantity
        self.actived = actived
        self.brand_id = brand_id
        self.min_quantity = min_quantity

    def __repr__(self):
        return "Product({})".format(self.name)


class Brand(db.Model):
    __tablename__ = "brands"

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(128), nullable=False)
    description = db.Column(db.String(256), nullable=False)
    cnpj = db.Column(db.String(20), nullable=False)
    products = db.relationship("Product", backref="brands", lazy=True)

    def __init__(self, name, description, cnpj):
        self.name = name
        self.description = description
        self.cnpj = cnpj

    def __repr__(self):
        return "Brand({})".format(self.id)


class Lot(db.Model):
    __tablename__ = "lots"

    id = db.Column(db.Integer, primary_key=True)
    product_id = db.Column(db.Integer, db.ForeignKey("products.id"), nullable=False)
    purchase_price = db.Column(db.Float, nullable=False)
    validity_date = db.Column(db.Date, nullable=False)
    lot_quantity = db.Column(db.Integer, nullable=False)

    def __init__(self, product_id, purchase_price, validity_date, lot_quantity):
        self.product_id = product_id
        self.purchase_price = purchase_price
        self.validity_date = validity_date
        self.lot_quantity = lot_quantity

    def __repr__(self):
        return "Lot({})".format(self.id)
