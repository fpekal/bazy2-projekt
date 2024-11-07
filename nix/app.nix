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
		substituteInPlace src/tui/ponysay.cpp --replace-fail 'ponysay -o' '${pkgs.ponysay}/bin/ponysay -o'
		'';
	};
in
{
	type = "app";
	program = "${package}/bin/pony";
}
