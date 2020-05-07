from flask import Blueprint, render_template, url_for, request, redirect, g
from sqlalchemy import desc
from flaskr.models.products import Product, Brand, Lot
from flaskr.models import db_add
from datetime import date
from random import randint

bp = Blueprint("products", __name__, url_prefix="/produtos")


@bp.route("/")
def index():
    products = Product.query.all()

    return render_template(
        "products/index.html", breadcrumbs=[("Produtos", "#")], products=products
    )


@bp.route("/adicionar", methods=["GET", "POST"])
def product_add():
    if request.method == "POST":
        form = request.form
        if form["type"] == "product":
            product = Product(
                form["name"],
                form["description"],
                float(form["price"]),
                int(form["stock"]) + int(form["lot_quantity"]),
                1 if form["actived"] == "on" else 0,
                int(form["brand"]),
                int(form["min_quantity"]),
            )

            lot = Lot(
                Product.query.order_by(desc(Product.id)).first().id + 1,
                float(form["purchase_price"]),
                form["validaty"],
                int(form["lot_quantity"]),
            )

            db_add(product)
            db_add(lot)

        return redirect(url_for("products.index"))

    brands = Brand.query.filter().all()

    prod = Product.query.order_by(desc(Product.id)).first()
    code = 1 if prod == None else prod.id + 1

    lot = Lot.query.order_by(desc(Lot.id)).first()
    lot_id = 1 if lot == None else lot.id + 1

    return render_template(
        "products/add.html",
        breadcrumbs=[("Produtos", url_for("products.index")), ("Adicionar", "#")],
        brands=brands,
        code=code,
        lot=lot_id,
        min_date=date.today(),
    )

