{ pkgs, libs }:
let
	package =
	pkgs.stdenv.mkDerivation {
		name = "pony";
		version = "0.0.1";

		nativeBuildInputs = libs.nativeBuildInputs;
		buildInputs = libs.buildInputs;

		src = ./..;

		patchPhase =
		''
		substituteInPlace src/db/scheme.cpp \
		--replace-fail 'sql/make_scheme.sql' ${../sql/make_scheme.sql}
		'';
	};
in
{
	type = "app";
	program = "${package}/bin/pony";
}
