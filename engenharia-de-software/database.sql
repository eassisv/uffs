CREATE TABLE brands (
	id SERIAL NOT NULL, 
	name VARCHAR(128) NOT NULL, 
	description VARCHAR(256) NOT NULL, 
	cnpj VARCHAR(20) NOT NULL, 
	PRIMARY KEY (id)
)

CREATE TABLE clients (
	id SERIAL NOT NULL, 
	first_name VARCHAR(128) NOT NULL, 
	full_name VARCHAR(256) NOT NULL, 
	cnpj VARCHAR(32) NOT NULL, 
	address VARCHAR(256) NOT NULL, 
	email VARCHAR(128) NOT NULL, 
	phone VARCHAR(32) NOT NULL, 
	created_at DATE NOT NULL, 
	PRIMARY KEY (id)
)

CREATE TABLE products (
	id SERIAL NOT NULL, 
	name VARCHAR(128) NOT NULL, 
	description VARCHAR(256) NOT NULL, 
	sale_price FLOAT NOT NULL, 
	total_quantity INTEGER NOT NULL, 
	actived SMALLINT NOT NULL, 
	min_quantity INTEGER, 
	brand_id INTEGER NOT NULL, 
	PRIMARY KEY (id), 
	FOREIGN KEY(brand_id) REFERENCES brands (id)
)

CREATE TABLE orders (
	id SERIAL NOT NULL, 
	total_price FLOAT NOT NULL, 
	sale_date DATE NOT NULL, 
	number_of_items INTEGER NOT NULL, 
	status VARCHAR(64) NOT NULL, 
	delivery_date DATE NOT NULL, 
	client_id INTEGER NOT NULL, 
	PRIMARY KEY (id), 
	FOREIGN KEY(client_id) REFERENCES clients (id)
)

CREATE TABLE lots (
	id SERIAL NOT NULL, 
	product_id INTEGER NOT NULL, 
	purchase_price FLOAT NOT NULL, 
	validity_date DATE NOT NULL, 
	lot_quantity INTEGER NOT NULL, 
	PRIMARY KEY (id), 
	FOREIGN KEY(product_id) REFERENCES products (id)
)

CREATE TABLE order_items (
	id SERIAL NOT NULL, 
	quantity INTEGER NOT NULL, 
	order_price FLOAT NOT NULL, 
	product_id INTEGER NOT NULL, 
	order_id INTEGER NOT NULL, 
	PRIMARY KEY (id), 
	FOREIGN KEY(product_id) REFERENCES products (id), 
	FOREIGN KEY(order_id) REFERENCES orders (id)
)
