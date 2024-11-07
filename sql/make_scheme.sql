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
	"health"      NUMERIC NOT NULL,
	"max_health" 	NUMERIC NOT NULL,
	"min_damage" 	NUMERIC NOT NULL,
	"max_damage"  NUMERIC NOT NULL,
	"attack_speed" 	NUMERIC NOT NULL,
	"armor" 		NUMERIC NOT NULL,
	"health_regeneration" NUMERIC NOT NULL,
	PRIMARY KEY("id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "ponies_genes" (
	"pony_id"	INTEGER NOT NULL,
	"gene_id"	INTEGER NOT NULL,
	UNIQUE("gene_id","pony_id"),
	FOREIGN KEY("gene_id") REFERENCES "genes"("id"),
	FOREIGN KEY("pony_id") REFERENCES "ponies"("id")
);
CREATE TRIGGER IF NOT EXISTS unique_gene_category_per_pony
BEFORE INSERT ON "ponies_genes"
BEGIN
    SELECT
        RAISE(ABORT, 'This pony already has a gene from this category')
    FROM
        "ponies_genes" AS pg
    JOIN
        "genes" AS g1 ON pg.gene_id = g1.id
    JOIN
        "genes" AS g2 ON NEW.gene_id = g2.id
    WHERE
        pg.pony_id = NEW.pony_id
        AND g1.category_id = g2.category_id;
END;
CREATE INDEX IF NOT EXISTS "pony_name_index" ON "ponies" (
	"name"	ASC
);
COMMIT;
