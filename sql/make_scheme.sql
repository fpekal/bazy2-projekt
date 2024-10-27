BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "gene_categories" (
	"id"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL UNIQUE,
	PRIMARY KEY("id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "genes" (
	"id"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL UNIQUE,
	"category_id"	INTEGER NOT NULL,
	PRIMARY KEY("id" AUTOINCREMENT),
	CONSTRAINT "genes_gene_categories_fk" FOREIGN KEY("category_id") REFERENCES "gene_categories"("id")
);
CREATE TABLE IF NOT EXISTS "ponies" (
	"id"	INTEGER NOT NULL UNIQUE,
	"name"	TEXT NOT NULL UNIQUE,
	PRIMARY KEY("id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "ponies_genes" (
	"pony_id"	INTEGER NOT NULL,
	"gene_id"	INTEGER NOT NULL,
	"gene_category_id"	INTEGER NOT NULL,
	UNIQUE("gene_category_id","pony_id"),
	FOREIGN KEY("gene_category_id") REFERENCES "gene_categories"("id"),
	FOREIGN KEY("gene_id") REFERENCES "genes"("id"),
	FOREIGN KEY("pony_id") REFERENCES "ponies"("id")
);
CREATE INDEX "pony_name_index" ON "ponies" (
	"name"	ASC
);
COMMIT;
